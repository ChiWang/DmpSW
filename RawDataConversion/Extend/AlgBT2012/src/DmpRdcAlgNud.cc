/*
 *  $Id: DmpRdcAlgNud.cc, 2014-05-19 13:00:00 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "Rdc/DmpRdcSvcDataMgr.h"
#include "DmpCore.h"
#include "DmpLog.h"
#include "DmpRdcAlgNud.h"

DmpRdcAlgNud::DmpRdcAlgNud()
 :DmpRdcVAlgSubDet("Nud/Rdc/BT2012"),
  fFEEType(2)
{
}

//-------------------------------------------------------------------
DmpRdcAlgNud::~DmpRdcAlgNud(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgNud::ProcessThisEvent(){
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
  fEvtHeader->Detector(DmpDetector::kNud)->SetErrorLog(0,DmpRdcHeaderSubDet::Good);       // the first element for whole subDet
//-------------------------------------------------------------------
// *
// *  TODO: check conversion Nud
// *
  static short feeID=0, nBytes=0, nSignal=0, data=0, data2=0;
  fFile->read((char*)(&data),1);
  if(data!=0xeb){
    fEvtHeader->Detector(DmpDetector::kNud)->SetErrorLog(0,DmpRdcHeaderSubDet::NotFind_0xeb);
    return false;
  }
  fFile->read((char*)(&data),1);
  if (data!=0x90) {
    fEvtHeader->Detector(DmpDetector::kNud)->SetErrorLog(0,DmpRdcHeaderSubDet::NotFind_0x90);
    return false;
  }
  fFile->read((char*)(&data),1);     // trigger
  fEvtHeader->Detector(DmpDetector::kNud)->SetTrigger(data);
  fFile->read((char*)(&data),1);     // run mode and FEE ID
  feeID = data%16;
  fEvtHeader->Detector(DmpDetector::kNud)->SetRunMode(data/16-fFEEType);
  fFile->read((char*)(&data),1);     // data length, 2 Bytes
  fFile->read((char*)(&data2),1);
  nBytes = data*256+data2-2-2;            // 2 bytes for data length, 2 bytes for CRC
// *
// *  TODO: mode == k0Compress && data length == xxx
// *
  //if (fEvtHeader->GetRunMode(DmpDetector::kNud) == DmpDetector::k0Compress) 
  if(fEvtHeader->Detector(DmpDetector::kNud)->RunMode() == DmpDetector::k0Compress){
    nSignal = nBytes/2;
    for(short i=0;i<nSignal;++i){     // k0Compress
      fFile->read((char*)(&data),1);
      fFile->read((char*)(&data2),1);
// *
// *  TODO: store impfore into hits
// *
    //fMSDSet->
    }
  }else{
    nSignal = nBytes/3;
    for(short i=0;i<nSignal;++i){     // kCompress
    }
  }
  fFile->read((char*)(&data),1);     // 2 bytes for CRC
  fFile->read((char*)(&data),1);     // 2 bytes for CRC, MUST split them
//-------------------------------------------------------------------
  if(not firstIn){
    LogDebug<<" to "<<fFile->tellg()<<"\t---> signalNo = "<<nSignal<<std::endl;
    firstIn = true;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgNud::InitializeSubDet(){
  // get TCloneArray of your subDet
  fMSDSet = ((DmpRdcSvcDataMgr*)gCore->ServiceManager()->Get("Rdc/DataMgr"))->GetOutCollection(DmpDetector::kNud);
  // setup connector
  if(fConnectorPath == "no"){
    std::cout<<"\n\tNo set connector:\tNud"<<std::endl;
    return false;
  }else{
    std::cout<<"\n\tSetting connector:\tNud"<<std::endl;
  }
// *
// *  TODO: set method?
// *
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgNud::AppendThisSignal(const int &id,const int &v){
// *
// *  TODO: example bgo
// *
}

