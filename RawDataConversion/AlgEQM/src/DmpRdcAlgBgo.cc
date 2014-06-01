/*
 *  $Id: DmpRdcAlgBgo.cc, 2014-05-20 19:03:22 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
 *    Yifeng WEI (weiyf@mail.ustc.edu.cn) 24/04/2014
*/

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "DmpCore.h"
#include "DmpRdcAlgBgo.h"

DmpRdcAlgBgo::DmpRdcAlgBgo()
 :DmpVAlg("Bgo/Rdc/2014"),
  fFile(0),
  fConnectorPath("NO"),
  fConnectorDone(false),
  fFEEType(0),
  fFEENo(16),
  fBgoSet(0),
  fEvtHeader(0)
{
  OptMap.insert(std::make_pair("Connector/Path",0));
  OptMap.insert(std::make_pair("FEE/Number",1));
  fBgoSet = new TClonesArray("DmpEvtRdcMSD",300);
}

//-------------------------------------------------------------------
DmpRdcAlgBgo::~DmpRdcAlgBgo(){
  fBgoSet->Delete();
  fBgoSet->Clear();
  delete fBgoSet;
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
bool DmpRdcAlgBgo::Initialize(){
  fFile = DmpIOSvc::GetInstance()->GetRdcInFile();
  if(0 == fFile){
    return false;
  }
// *
// *  TODO: how to get event header
// *
  //fEvtHeader = ((DmpRdcSvcDataMgr*)gCore->ServiceManager()->Get("Rdc/DataMgr"))->GetEventHeader();
  DmpIOSvc::GetInstance()->AddBranch("Rdc/Bgo",fBgoSet);
  // setup connector
  LogInfor<<"Setting connector:\tBgo"<<std::endl;
  if(fConnectorPath == "NO"){
    LogError<<"Path is empty"<<std::endl;
    return false;
  }
  short feeID=0, channelNo=0, channelID=0, layerID=0, barID=0, sideID=0, dyID=0;
  boost::filesystem::directory_iterator end_iter;
  for(boost::filesystem::directory_iterator iter(fConnectorPath);iter!=end_iter;++iter){
    if(iter->path().extension() != ".cnct") continue;
    ifstream cnctFile(iter->path().string().c_str());
    if (not cnctFile.good()){
      LogError<<"Reading cnct file ("<<iter->path().string()<<") failed"<<std::endl;
      cnctFile.close();
      return false;
    }
    cnctFile>>feeID;
    cnctFile>>channelNo;
    for(short s=0;s<channelNo;++s){
      cnctFile>>channelID;
      cnctFile>>layerID;
      cnctFile>>barID;
      cnctFile>>sideID;
      cnctFile>>dyID;
      fConnector.insert(std::make_pair(feeID*1000+channelID,layerID*10000+barID*100+sideID*10+dyID));
    }
    cnctFile.close();
    LogInfor<<"Read cnct file: "<<iter->path().string()<<"succeed. ID = "<<feeID<<"\tN_channel = "<<channelNo<<std::endl;
  }
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgBgo::ProcessThisEvent(){
  static bool firstIn = true;
  if(firstIn){
    LogDebug<<"\tfrom "<<fFile->tellg();
    firstIn = false;
  }
  if(not fConnectorDone){
    LogError<<"Connector not set\t"<<std::endl;
    return true;
  }
//-------------------------------------------------------------------
// reset before processing the next event
  fBgoSet->Delete();    fBgoSet->Clear();
// *
// *  TODO: SetErrorLog wrong
// *
  fEvtHeader->Detector(DmpDetector::kBgo)->SetErrorLog(0,DmpRdcHeaderSubDet::Good);       // the first element for whole subDet
//-------------------------------------------------------------------
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0;
  static short data=0;
  static unsigned short data2=0;
  for(feeCounts=0;feeCounts<fFEENo;++feeCounts){
    fFile->read((char*)(&data),1);
    if(data != 0xeb){
      fEvtHeader->Detector(DmpDetector::kBgo)->SetErrorLog(feeCounts+1,DmpRdcHeaderSubDet::NotFind_0xeb);
      return false;
    }
    fFile->read((char*)(&data),1);
    if(data != 0x90){
      fEvtHeader->Detector(DmpDetector::kBgo)->SetErrorLog(feeCounts+1,DmpRdcHeaderSubDet::NotFind_0x90);
      return false;
    }
    fFile->read((char*)(&data),1);      // reserved 1 byte
    fFile->read((char*)(&data),1);      // run mode and FEE ID
    feeID = data%16;
    if(feeCounts == 0){
      fEvtHeader->Detector(DmpDetector::kBgo)->SetRunMode(data/16-fFEEType);
    }else{
      if(fEvtHeader->Detector(DmpDetector::kBgo)->RunMode() != data/16-fFEEType){
        fEvtHeader->Detector(DmpDetector::kBgo)->SetErrorLog(feeID,DmpRdcHeaderSubDet::NotMatch_RunMode);
        return false;
      }
    }
    fFile->read((char*)(&data),1);      // data length, 2 bytes
    fFile->read((char*)(&data2),1);
    nBytes = data*256+data2-2-2-2;      // 2 bytes for data length, 2 bytes for trigger, 2 bytes for CRC
// *
// *  TODO: check data length
// *
    if(fEvtHeader->Detector(DmpDetector::kBgo)->RunMode() == DmpDetector::k0Compress){
      nSignal = nBytes/2;
      for(short i=0;i<nSignal;++i){     // k0Compress
        fFile->read((char*)(&data),1);
        fFile->read((char*)(&data2),1);
        AppendThisSignal(fConnector[feeID*1000+i],data*256+data2);
      }
    }else{
      nSignal = nBytes/3;
      for(short i=0;i<nSignal;++i){     // kCompress
        fFile->read((char*)(&channelID),1);
        fFile->read((char*)(&data),1);
        fFile->read((char*)(&data2),1);
        if(fConnector[feeID*1000+channelID] != 0){
          AppendThisSignal(fConnector[feeID*1000+channelID],data*256+data2);
        }else{
          LogError<<"Connector Key Wrong. FeeID("<<feeID<<") Channel("<<channelID<<") ADC("<<data*256+data2<<")"<<std::endl;
        }
      }
      if(nBytes%3){     // nBytes%3 == 1
        fFile->read((char*)(&data),1);
      }
    }
    fFile->read((char*)(&data),1);      // trigger status
    fFile->read((char*)(&data),1);      // trigger
    if(feeCounts == 0){
      fEvtHeader->Detector(DmpDetector::kBgo)->SetTrigger(data);
    }else{
      if(fEvtHeader->Detector(DmpDetector::kBgo)->Trigger() != data){
        fEvtHeader->Detector(DmpDetector::kBgo)->SetErrorLog(feeCounts+1,DmpRdcHeaderSubDet::NotMatch_Trigger);
        return false;
      }
    }
    fFile->read((char*)(&data),1);      // 2 bytes for CRC
    fFile->read((char*)(&data),1);      // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------
  if(not firstIn){
    LogDebug<<" to "<<fFile->tellg()<<"\t---> signalNo = "<<nSignal<<std::endl;
    firstIn = true;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgBgo::Finalize(){
  return true;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
void DmpRdcAlgBgo::Set(const std::string &type,const std::string &argv){
  switch (OptMap[type]){
    case 0:
      { // Connector/Path
        fConnectorPath = argv;
        break;
      }
    case 1:
      { // FEE/Number
        fFEENo = lexical_cast<short>(argv);
        break;
      }
  }
}

//-------------------------------------------------------------------
void DmpRdcAlgBgo::AppendThisSignal(const int &id, const int &v){
  static DmpEvtRdcMSD *aMSD = 0;
  static short i=0, barID=0;
  int index = -1;
  barID = id/100;
  for(i=0;i<fBgoSet->GetEntriesFast();++i){
    if(((DmpEvtRdcMSD*)fBgoSet->At(i))->GetSDID() == barID){
      index = i;
    }
  }
  if(index < 0){
    index = fBgoSet->GetEntriesFast();
    aMSD = (DmpEvtRdcMSD*)fBgoSet->ConstructedAt(index);
    aMSD->SetSDID(barID);
  }else{
    aMSD = (DmpEvtRdcMSD*)fBgoSet->At(index);
  }
  aMSD->SetSignal(id%100,v);
}


