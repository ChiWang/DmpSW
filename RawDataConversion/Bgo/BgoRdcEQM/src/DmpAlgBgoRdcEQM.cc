/*
 *  $Id: DmpAlgBgoRdcEQM.cc, 2014-06-17 17:16:32 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/06/2014
*/

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "DmpAlgBgoRdcEQM.h"
#include "DmpRootIOSvc.h"

//-------------------------------------------------------------------
DmpAlgBgoRdcEQM::DmpAlgBgoRdcEQM()
 :DmpVAlg("Rdc/Bgo/EQM"),
  fInDataName("NO"),
  fInFilePtr(0),
  fEvtHeader(0),
  fBgoBarSet(0),
  fCNCTPathBgo("NO"),
  fCNCTDoneBgo(false)
{
  OptMap.insert(std::make_pair("BinaryFile",    0));    // input file name
  OptMap.insert(std::make_pair("Connector",     1));    // connector path
}

//-------------------------------------------------------------------
DmpAlgBgoRdcEQM::~DmpAlgBgoRdcEQM(){
}

//-------------------------------------------------------------------
void DmpAlgBgoRdcEQM::Set(const std::string &type,const std::string &value){
  if(OptMap.find(type) == OptMap.end()){
    DmpLogError<<"No argument type: "<<type<<DmpLogEndl;
  }
  switch (OptMap[type]){
    case 0:
    {// BinaryFile
      fInDataName = value;
      //DmpRootIOSvc::GetInstance()->InFileTag(value);
      break;
    }
    case 1:
    {// Connector
      fCNCTPathBgo = value;
      break;
    }
  }
}

//-------------------------------------------------------------------
bool DmpAlgBgoRdcEQM::Initialize(){
  fInFilePtr.open(fInDataName.c_str(),std::ios::in|std::ios::binary);
  if(not fInFilePtr.good()){
    DmpLogError<<"Open "<<fInDataName<<" failed"<<DmpLogEndl;
    fInFilePtr.close();
    fIniStatus = false;
    return fIniStatus;
  }
  if(fCNCTPathBgo == "NO"){
    DmpLogWarning<<"No set connector:\tBgo"<<DmpLogEndl;
    return true;
  }else{
    DmpLogInfo<<"Setting connector:\tBgo"<<DmpLogEndl;
    // setup connector
    if(not SetConnector()) return false;
  }
  fEvtHeader = new DmpEvtRdcHeader();
  if(not DmpRootIOSvc::GetInstance()->RegisterObject("Event/Rdc/EventHeader","DmpEvtRdcHeader",fEvtHeader)){
    fIniStatus = false;
    return fIniStatus;
  }
  fBgoBarSet = new TClonesArray("DmpEvtRdcMSD",300);
  if(not DmpRootIOSvc::GetInstance()->RegisterObject("Event/Rdc/Bgo",fBgoBarSet)){
    fIniStatus = false;
    return fIniStatus;
  }
  return fIniStatus;
}

//-------------------------------------------------------------------
bool DmpAlgBgoRdcEQM::Finalize(){
  if(fEvtHeader){
    delete fEvtHeader;
  }
  if(fBgoBarSet){
    fBgoBarSet->Delete();
    delete fBgoBarSet;
  }
  return true;
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
bool DmpAlgBgoRdcEQM::SetConnector(){
  short feeID=0, channelNo=0, channelID=0, layerID=0, barID=0, sideID=0, dyID=0;
  boost::filesystem::directory_iterator end_iter;
  for(boost::filesystem::directory_iterator iter(fCNCTPathBgo);iter!=end_iter;++iter){
    if(iter->path().extension() != ".cnct") continue;
    ifstream cnctFile(iter->path().string().c_str());
    if (not cnctFile.good()){
      DmpLogError<<"\t\treading cnct file ("<<iter->path().string()<<") failed"<<DmpLogEndl;
      cnctFile.close();
      fIniStatus = false;
      return fIniStatus;
    }
    cnctFile>>feeID;
    cnctFile>>channelNo;
    for(short s=0;s<channelNo;++s){
      cnctFile>>channelID;
      cnctFile>>layerID;
      cnctFile>>barID;
      cnctFile>>sideID;
      cnctFile>>dyID;
      fCNCTMapBgo.insert(std::make_pair(feeID*1000+channelID,layerID*10000+barID*100+sideID*10+dyID));
    }
    cnctFile.close();
    DmpLogInfo<<"\treading cnct file: "<<iter->path().string()<<"\t  Done. ID = "<<feeID<<"\tN_channel = "<<channelNo<<DmpLogEndl;
  }
  fCNCTDoneBgo = true;
  return true;
}

//-------------------------------------------------------------------
#include "DmpCore.h"
bool DmpAlgBgoRdcEQM::ProcessThisEvent(){
  bool oneEvtDone = false;
  while(not oneEvtDone){
    if(fInFilePtr.tellg() < 0){
      gCore->TerminateRun();
      return false;
    }
    if(ProcessThisEventHeader()){
      DmpLogDebug<<"to "<<fInFilePtr.tellg()<<DmpLogEndl;
    }else{
      DmpLogDebug<<"to "<<fInFilePtr.tellg()<<DmpLogEndl;
      continue;
    }
    if(fCNCTDoneBgo){
      if(ProcessThisEventBgo()){
        DmpLogDebug<<"to "<<fInFilePtr.tellg()<<DmpLogEndl;
      }else{
        DmpLogDebug<<"to "<<fInFilePtr.tellg()<<DmpLogEndl;
        continue;
      }
    }
    if(fInFilePtr.tellg() < 0){
      DmpLogDebug<<"not fill the last event"<<DmpLogEndl;
      gCore->TerminateRun();
      return false;
    }
    oneEvtDone = true;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpAlgBgoRdcEQM::ProcessThisEventHeader(){
  static short tmp=0;
  fEvtHeader->Reset();
//-------------------------------------------------------------------
  DmpLogDebug<<"[Header] from "<<fInFilePtr.tellg();
  fInFilePtr.read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  fInFilePtr.read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  fInFilePtr.read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  fInFilePtr.read((char*)(&tmp),1);
  if (tmp!=0x13)    return false;
// *
// *  TODO: trigger first byte means??
// *
  fInFilePtr.read((char*)(&tmp),1);      // this needed
  fInFilePtr.read((char*)(&tmp),1);      // trigger
  fEvtHeader->SetTrigger(DmpDetectorID::kWhole,tmp);
  fInFilePtr.read((char*)(&tmp),1);      // Datalength
  fInFilePtr.read((char*)(&tmp),1);      // Datalength
  for (std::size_t index=0;index<8;++index) {     // size = 8
    fInFilePtr.read((char*)(&tmp),1);
    fEvtHeader->SetTime(index,tmp);
  }
//-------------------------------------------------------------------
  return true;
}

//-------------------------------------------------------------------
bool DmpAlgBgoRdcEQM::ProcessThisEventBgo(){
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0;
  static short feeTypeBgo = 0;
  static short data=0;
  static unsigned short data2=0;
//-------------------------------------------------------------------
  fBgoBarSet->Delete();
  DmpLogDebug<<"[Bgo] from "<<fInFilePtr.tellg();
//-------------------------------------------------------------------
  for(feeCounts=0;feeCounts<16;++feeCounts){
    fInFilePtr.read((char*)(&data),1);
    if(data != 0xeb){
      fEvtHeader->SetErrorLog(DmpDetectorID::kBgo,feeCounts+1,DmpEvtRdcHeader::NotFind_0xeb);
      return false;
    }
    fInFilePtr.read((char*)(&data),1);
    if(data != 0x90){
      fEvtHeader->SetErrorLog(DmpDetectorID::kBgo,feeCounts+1,DmpEvtRdcHeader::NotFind_0x90);
      return false;
    }
    fInFilePtr.read((char*)(&data),1);      // reserved 1 byte
    fInFilePtr.read((char*)(&data),1);      // run mode and FEE ID
    feeID = data%16;
    if(feeCounts == 0){
      fEvtHeader->SetRunMode(DmpDetectorID::kBgo,data/16-feeTypeBgo);
    }else{
      if(fEvtHeader->GetRunMode(DmpDetectorID::kBgo) != data/16-feeTypeBgo){
        fEvtHeader->SetErrorLog(DmpDetectorID::kBgo,feeID,DmpEvtRdcHeader::NotMatch_RunMode);
        return false;
      }
    }
    fInFilePtr.read((char*)(&data),1);      // data length, 2 bytes
    fInFilePtr.read((char*)(&data2),1);
    nBytes = data*256+data2-2-2-2;      // 2 bytes for data length, 2 bytes for trigger, 2 bytes for CRC
// *
// *  TODO: check data length
// *
    if(fEvtHeader->GetRunMode(DmpDetectorID::kBgo) == DmpRunMode::kCompress){
      nSignal = nBytes/3;
      DmpLogDebug<<"\tFEE ID "<<feeID<<" signalNo = "<<nSignal<<DmpLogEndl;
      for(short i=0;i<nSignal;++i){     // kCompress
        fInFilePtr.read((char*)(&channelID),1);
        fInFilePtr.read((char*)(&data),1);
        fInFilePtr.read((char*)(&data2),1);
        if(fCNCTMapBgo[feeID*1000+channelID] != 0){
          AppendThisSignal(fCNCTMapBgo[feeID*1000+channelID],data*256+data2);
        }else{
          DmpLogError<<"Connector Key Wrong. FeeID("<<feeID<<") Channel("<<channelID<<") ADC("<<data*256+data2<<")"<<DmpLogEndl;
        }
      }
      if(nBytes%3){     // nBytes%3 == 1
        fInFilePtr.read((char*)(&data),1);
      }
    }else{
      nSignal = nBytes/2;
      DmpLogDebug<<"\tFEE ID "<<feeID<<" signalNo = "<<nSignal<<DmpLogEndl;
      for(short i=0;i<nSignal;++i){     // k0Compress
        fInFilePtr.read((char*)(&data),1);
        fInFilePtr.read((char*)(&data2),1);
        AppendThisSignal(fCNCTMapBgo[feeID*1000+i],data*256+data2);
      }
    }
    fInFilePtr.read((char*)(&data),1);      // trigger status
    fInFilePtr.read((char*)(&data),1);      // trigger
    if(feeCounts == 0){
      fEvtHeader->SetTrigger(DmpDetectorID::kBgo,data);
    }else{
      if(fEvtHeader->GetTrigger(DmpDetectorID::kBgo) != data){
        fEvtHeader->SetErrorLog(DmpDetectorID::kBgo,feeCounts+1,DmpEvtRdcHeader::NotMatch_Trigger);
        return false;
      }
    }
    fInFilePtr.read((char*)(&data),1);      // 2 bytes for CRC
    fInFilePtr.read((char*)(&data),1);      // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------
  return true;
}

//-------------------------------------------------------------------
void DmpAlgBgoRdcEQM::AppendThisSignal(const int &id, const int &v){
  static DmpEvtRdcMSD *aMSD = 0;
  static short i=0, barID=0;
  int index = -1;
  barID = id/100;
  for(i=0;i<fBgoBarSet->GetEntriesFast();++i){
    if(((DmpEvtRdcMSD*)fBgoBarSet->At(i))->GetSDID() == barID){
      index = i;
    }
  }
  if(index < 0){
    index = fBgoBarSet->GetEntriesFast();
    aMSD = (DmpEvtRdcMSD*)fBgoBarSet->ConstructedAt(index);
    aMSD->SetSDID(barID);
  }else{
    aMSD = (DmpEvtRdcMSD*)fBgoBarSet->At(index);
  }
  aMSD->SetSignal(id%100,v);
}

