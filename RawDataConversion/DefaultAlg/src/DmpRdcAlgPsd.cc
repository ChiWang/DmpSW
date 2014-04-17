/*
 *  $Id: DmpRdcAlgPsd.cc, 2014-04-17 10:57:20 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpDetectorPsd.h"
#include "DmpEvtPsdMSD.h"
#include "DmpEvtHeader.h"
#include "DmpRdcAlgPsd.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpRdcSvcLog.h"
#include "DmpServiceManager.h"

DmpRdcAlgPsd::DmpRdcAlgPsd()
 :DmpRdcVAlgSubDet("Rdc/Psd/DefaultAlg")
{
}

//-------------------------------------------------------------------
DmpRdcAlgPsd::~DmpRdcAlgPsd(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgPsd::ProcessThisEvent(){
  if(not fConnectorDone){
    std::cout<<"Error:  Connector not set\t"<<__PRETTY_FUNCTION__<<std::endl;
    return true;
  }
  fLog->Type(0);
//-------------------------------------------------------------------
// *
// *  TODO: conversion Psd
// *
  static short tmp=0, tmp2 = 0, nBytes = 0;
  for (short counts=0;counts<DmpDetector::Psd::kFEENo;++counts) {
    fFile->read((char*)(&tmp),1);
    if (tmp!=0xeb) {
      fLog->Type(-1);
      return false;
    }
    fFile->read((char*)(&tmp),1);
    if (tmp!=0x90) {
      fLog->Type(-2);
      return false;
    }
    fFile->read((char*)(&tmp),1);       // trigger
    if(counts == 0){
      fEvtHeader->SetTrigger(DmpDetector::kPsd,tmp);
    }else{
      if(fEvtHeader->GetTrigger(DmpDetector::kPsd) != tmp){
        fLog->Type(-3);
        return false;
      }
    }
    fFile->read((char*)(&tmp),1);       // run mode and FEE ID
    static short feeID = 0;
    feeID = tmp%16;
    if(counts == 0){
      fEvtHeader->SetRunMode(DmpDetector::kPsd,tmp/16-DmpDetector::Psd::kFEEType);
    }else{
      if(fEvtHeader->GetRunMode(DmpDetector::kPsd) != tmp/16-DmpDetector::Psd::kFEEType){
        fLog->Type(-4);
        return false;
      }
    }
    fFile->read((char*)(&tmp),1);       // data length, 2 bytes
    fFile->read((char*)(&tmp2),1);
    nBytes = tmp*256+tmp2-2-2-2;        // 2 bytes for data length, 2 bytes for 0x0000, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
    if(fEvtHeader->GetRunMode(DmpDetector::kPsd) == DmpDetector::k0Compress){
      for(short i=0;i<nBytes;i+=2){     // k0Compress
        fFile->read((char*)(&tmp),1);
        fFile->read((char*)(&tmp2),1);
        AppendThisSignal(fConnector[feeID*1000+i],tmp*256+tmp2);
      }
    }else{
      for(short i=0;i<nBytes;i+=3){     // kCompress
        fFile->read((char*)(&tmp),1);
        fFile->read((char*)(&tmp),1);
        fFile->read((char*)(&tmp2),1);
// *
// *  TODO: open me
// *
        //AppendThisSignal(fConnector[feeID*1000+i],tmp*256+tmp2);
      }
    }
    fFile->read((char*)(&tmp),1);       // 2 bytes for 0x0000
    fFile->read((char*)(&tmp),1);       // must split them, 2 bytes for 0x0000
    fFile->read((char*)(&tmp),1);       // 2 bytes for CRC
    fFile->read((char*)(&tmp),1);       // must spplit them, 2 bytes for CRC
  }
//-------------------------------------------------------------------

  fLog->Type(nBytes);
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgPsd::InitializeSubDet(){
  // get TCloneArray of your subDet
  fMSDSet = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->GetOutCollection(DmpDetector::kPsd);
  // setup connector
  if(fConnectorPath == "no"){
    std::cout<<"\n\tNo set connector:\tPsd"<<std::endl;
    return false;
  }else{
    std::cout<<"\n\tSetting connector:\tPsd";
  }
// *
// *  TODO:  check connector right?
// *
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgPsd::AppendThisSignal(const int &id,const float &v){
// *
// *  TODO: example bgo
// *
}

