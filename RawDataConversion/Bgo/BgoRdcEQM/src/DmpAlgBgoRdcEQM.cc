/*
 *  $Id: DmpAlgBgoRdcEQM.cc, 2014-06-17 17:16:32 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/06/2014
*/

#include "TClonesArray.h"

#include "DmpEvtHeader.h"
#include "DmpEvtRdcBgoBar.h"
#include "DmpAlgBgoRdcEQM.h"
#include "DmpDataBuffer.h"

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
  //if(fEvtHeader){
  //  delete fEvtHeader;
  //}
  //if(fBgoBarSet){
  //  delete fBgoBarSet;
  //}
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
  fEvtHeader = new DmpEvtHeader();
  if(not gDataBuffer->RegisterObject("Event/Rdc/EventHeader",fEvtHeader,"DmpEvtHeader")){
    fIniStatus = false;
    return fIniStatus;
  }
  fBgoBarSet = new TClonesArray("DmpEvtRdcBgoBar",300);
  if(not gDataBuffer->RegisterObject("Event/Rdc/Bgo",fBgoBarSet)){
    fIniStatus = false;
    return fIniStatus;
  }
  return fIniStatus;
}

//-------------------------------------------------------------------
bool DmpAlgBgoRdcEQM::Finalize(){
  fBgoBarSet->Delete();
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
  fEvtHeader->SetTrigger(tmp);
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
  static short feeCounts=0, trigger=0, feeID=0, nBytes=0, nSignal=0, channelID=0;
  static short runMode = 0;
  static short feeTypeBgo = 0;
  static char data=0;
  static unsigned char data2=0;
//-------------------------------------------------------------------
  fBgoBarSet->Delete();
  DmpLogDebug<<"[Bgo] from "<<fInFilePtr.tellg();
//-------------------------------------------------------------------
  for(feeCounts=0;feeCounts<16;++feeCounts){
    fInFilePtr.read((char*)(&data2),1);
    if(data2 != 0xeb){
      fEvtHeader->SetFeeErrorTag(DmpDetectorID::kBgo,feeCounts+1,DmpDataError::NotFind_0xeb);
      return false;
    }
    fInFilePtr.read((char*)(&data2),1);
    if(data2 != 0x90){
      fEvtHeader->SetFeeErrorTag(DmpDetectorID::kBgo,feeCounts+1,DmpDataError::NotFind_0x90);
      return false;
    }
    fInFilePtr.read((char*)(&data2),1);      // reserved 1 byte
    fInFilePtr.read((char*)(&data2),1);      // run mode and FEE ID
    feeID = data2%16;
    runMode = data2/16-feeTypeBgo;
    fInFilePtr.read((char*)(&data),1);      // data length, 2 bytes
    fInFilePtr.read((char*)(&data2),1);
    nBytes = data*256+data2-2-2-2;      // 2 bytes for data length, 2 bytes for trigger, 2 bytes for CRC
// *
// *  TODO: check data length
// *
    if(runMode == DmpRunMode::kCompress){
      nSignal = nBytes/3;
      DmpLogDebug<<"\tFEE ID "<<feeID<<" signalNo = "<<nSignal<<DmpLogEndl;
      for(short i=0;i<nSignal;++i){     // kCompress
        fInFilePtr.read((char*)(&channelID),1);
        fInFilePtr.read((char*)(&data),1);
        fInFilePtr.read((char*)(&data2),1);
        AppendThisSignal(feeID*1000+channelID,data*256+data2);
      }
      if(nBytes%3){     // nBytes%3 == 1
        fInFilePtr.read((char*)(&data2),1);
      }
    }else{
      nSignal = nBytes/2;
      DmpLogDebug<<"\tFEE ID "<<feeID<<" signalNo = "<<nSignal<<DmpLogEndl;
      for(short i=0;i<nSignal;++i){     // k0Compress
        fInFilePtr.read((char*)(&data),1);
        fInFilePtr.read((char*)(&data2),1);
        AppendThisSignal(feeID*1000+i,data*256+data2);
      }
    }
    fInFilePtr.read((char*)(&data2),1);      // trigger status
    fInFilePtr.read((char*)(&data2),1);      // trigger
    trigger = data2;
    fEvtHeader->SetFeeStatus(DmpDetectorID::kBgo,feeID,trigger,runMode);
    fInFilePtr.read((char*)(&data2),1);      // 2 bytes for CRC
    fInFilePtr.read((char*)(&data2),1);      // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------
  return true;
}

//-------------------------------------------------------------------
void DmpAlgBgoRdcEQM::AppendThisSignal(const int &globalFeeChannelID, const int &v){
  static DmpEvtRdcBgoBar *aBgoBar = 0;
  static short i=0, globalBarID=0;
  if(fCNCTMapBgo.find(globalFeeChannelID) == fCNCTMapBgo.end()){
    DmpLogError<<"Connector Key Wrong. Global Fee Channel ID: "<<globalFeeChannelID<<". ADC = "<<v<<DmpLogEndl;
    return;
  }else{
    globalBarID = fCNCTMapBgo[globalFeeChannelID]/100;
  }
  int index = -1;
  for(i=0;i<fBgoBarSet->GetEntriesFast();++i){
    if(((DmpEvtRdcBgoBar*)fBgoBarSet->At(i))->GetGlobalBarID() == globalBarID){
      index = i;
    }
  }
  if(index < 0){
    index = fBgoBarSet->GetEntriesFast();
    aBgoBar = (DmpEvtRdcBgoBar*)fBgoBarSet->ConstructedAt(index);
    aBgoBar->SetGlobalBarID(globalBarID);
  }else{
    aBgoBar = (DmpEvtRdcBgoBar*)fBgoBarSet->At(index);
  }
  aBgoBar->SetSignal(globalFeeChannelID,fCNCTMapBgo[globalFeeChannelID]%100,v);
}

