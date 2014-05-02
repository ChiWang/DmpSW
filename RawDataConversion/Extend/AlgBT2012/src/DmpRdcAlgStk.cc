/*
 *  $Id: DmpRdcAlgStk.cc, 2014-05-02 14:31:22 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "Rdc/DmpRdcSvcDataMgr.h"
#include "DmpKernel.h"
#include "DmpRdcAlgStk.h"

DmpRdcAlgStk::DmpRdcAlgStk()
 :DmpRdcVAlgSubDet("Stk/Rdc/BT2012"),
  fFEEType(3),
  fFEENo(1)
{
}

//-------------------------------------------------------------------
DmpRdcAlgStk::~DmpRdcAlgStk(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgStk::ProcessThisEvent(){
  static bool firstIn = true;
  if(gKernel->PrintDebug() && firstIn){
    std::cout<<"DEBUG: "<<__PRETTY_FUNCTION__<<"\tfrom "<<fFile->tellg();
    firstIn = false;
  }
  if(not fConnectorDone){
    if(gKernel->PrintError()){
      std::cout<<"Error:  Connector not set\t"<<__PRETTY_FUNCTION__<<std::endl;
    }
    return true;
  }
// *
// *  TODO: SetErrorLog wrong
// *
  fEvtHeader->Detector(DmpDetector::kPsd)->SetErrorLog(0,DmpRdcHeaderSubDet::Good);       // the first element for whole subDet
//-------------------------------------------------------------------
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0, data=0, data2=0;
//-------------------------------------------------------------------
// *
// *  TODO: conversion bgo
// *
//-------------------------------------------------------------------
  if(gKernel->PrintDebug()){
    std::cout<<" to "<<fFile->tellg()<<"\t---> signalNo = "<<nSignal<<std::endl;
    firstIn = true;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgStk::InitializeSubDet(){
  // get TCloneArray of your subDet
  fMSDSet = ((DmpRdcSvcDataMgr*)gKernel->ServiceManager()->Get("Rdc/DataMgr"))->GetOutCollection(DmpDetector::kPsd);
  // setup connector
  if(fConnectorPath == "no"){
    std::cout<<"\n\tNo set connector:\tStk"<<std::endl;
    return false;
  }else{
    std::cout<<"\n\tSetting connector:\tStk"<<std::endl;
  }
// *
// *  TODO: set method?
// *
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgStk::AppendThisSignal(const int &id,const int &v){
// *
// *  TODO: example bgo
// *
}

