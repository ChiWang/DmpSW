/*
 *  $Id: DmpRdcAlgPsd.cc, 2014-05-02 14:31:32 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "Rdc/DmpRdcSvcDataMgr.h"
#include "DmpCore.h"
#include "DmpRdcAlgPsd.h"

DmpRdcAlgPsd::DmpRdcAlgPsd()
 :DmpRdcVAlgSubDet("Psd/Rdc/BT2012"),
  fFEEType(1),
  fFEENo(1)
{
}

//-------------------------------------------------------------------
DmpRdcAlgPsd::~DmpRdcAlgPsd(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgPsd::ProcessThisEvent(){
  static bool firstIn = true;
  if(firstIn){
    LogDebug<<"\tfrom "<<fFile->tellg();
    firstIn = false;
  }
  if(not fConnectorDone){
    LogError<<"Connector not set\t"<<std::endl;
    return true;
  }
// *
// *  TODO: SetErrorLog wrong
// *
  fEvtHeader->Detector(DmpDetector::kPsd)->SetErrorLog(0,DmpRdcHeaderSubDet::Good);       // the first element for whole subDet
//-------------------------------------------------------------------
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0, data=0, data2=0;
  for (feeCounts=0;feeCounts<fFEENo;++feeCounts) {
    fFile->read((char*)(&data),1);
    if (data!=0xeb) {
      fEvtHeader->Detector(DmpDetector::kPsd)->SetErrorLog(feeCounts+1,DmpRdcHeaderSubDet::NotFind_0xeb);
      return false;
    }
    fFile->read((char*)(&data),1);
    if (data!=0x90) {
      fEvtHeader->Detector(DmpDetector::kPsd)->SetErrorLog(feeCounts+1,DmpRdcHeaderSubDet::NotFind_0x90);
      return false;
    }
    fFile->read((char*)(&data),1);       // trigger
    if(feeCounts == 0){
      fEvtHeader->Detector(DmpDetector::kPsd)->SetTrigger(data);
    }else{
      if(fEvtHeader->Detector(DmpDetector::kPsd)->Trigger() != data){
        fEvtHeader->Detector(DmpDetector::kPsd)->SetErrorLog(feeCounts+1,DmpRdcHeaderSubDet::NotMatch_Trigger);
        return false;
      }
    }
    fFile->read((char*)(&data),1);       // run mode and FEE ID
    feeID = data%16;
    if(feeCounts == 0){
      fEvtHeader->Detector(DmpDetector::kPsd)->SetRunMode(data/16-fFEEType);
    }else{
      if(fEvtHeader->Detector(DmpDetector::kPsd)->RunMode() != data/16-fFEEType){
        fEvtHeader->Detector(DmpDetector::kPsd)->SetErrorLog(feeID,DmpRdcHeaderSubDet::NotMatch_RunMode);
        return false;
      }
    }
    fFile->read((char*)(&data),1);       // data length, 2 bytes
    fFile->read((char*)(&data2),1);
    nBytes = data*256+data2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(fEvtHeader->Detector(DmpDetector::kPsd)->RunMode() == DmpDetector::k0Compress){
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
        AppendThisSignal(fConnector[feeID*1000+channelID],data*256+data2);
      }
    }
    fFile->read((char*)(&data),1);       // 2 bytes for 0x0000
    fFile->read((char*)(&data),1);       // must split them, 2 bytes for 0x0000
    fFile->read((char*)(&data),1);       // 2 bytes for CRC
    fFile->read((char*)(&data),1);       // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------
  if(not firstIn){
    LogDebug<<" to "<<fFile->tellg()<<"\t---> signalNo = "<<nSignal<<std::endl;
    firstIn = true;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgPsd::InitializeSubDet(){
  // get TCloneArray of your subDet
  fMSDSet = ((DmpRdcSvcDataMgr*)gCore->ServiceManager()->Get("Rdc/DataMgr"))->GetOutCollection(DmpDetector::kPsd);
  // setup connector
  if(fConnectorPath == "no"){
    std::cout<<"\n\tNo set connector:\tPsd"<<std::endl;
    return false;
  }else{
    std::cout<<"\n\tSetting connector:\tPsd"<<std::endl;
  }
// *
// *  TODO:  check connector right?
// *
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgPsd::AppendThisSignal(const int &id,const int &v){
// *
// *  TODO: example bgo
// *
}


