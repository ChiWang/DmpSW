/*
 *  $Id: DmpRdcAlgStk.cc, 2014-04-17 11:12:59 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "TClonesArray.h"

#include "DmpDetectorStk.h"
#include "DmpEvtStkMSD.h"
#include "DmpEvtHeader.h"
#include "DmpRdcAlgStk.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpRdcSvcLog.h"
#include "DmpServiceManager.h"

DmpRdcAlgStk::DmpRdcAlgStk()
 :DmpRdcVAlgSubDet("Rdc/Stk/DefaultAlg")
{
}

//-------------------------------------------------------------------
DmpRdcAlgStk::~DmpRdcAlgStk(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgStk::ProcessThisEvent(){
  if(not fConnectorDone){
    std::cout<<"Error:  Connector not set\t"<<__PRETTY_FUNCTION__<<std::endl;
    return true;
  }
  fLog->Type(0);
//-------------------------------------------------------------------
// *
// *  TODO: conversion bgo
// *
//-------------------------------------------------------------------

  fLog->Type(1);
  fConnectorDone = true;
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgStk::InitializeSubDet(){
  // get TCloneArray of your subDet
  fMSDSet = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->GetOutCollection(DmpDetector::kStk);
  if(fConnectorPath == "no"){
    std::cout<<"\n\tNo set connector:\tStk"<<std::endl;
    return true;
  }else{
    std::cout<<"\n\tSetting connector:\tStk";
  }
// *
// *  TODO: set method?
// *
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgStk::AppendThisSignal(const int &id,const float &v){
// *
// *  TODO: example bgo
// *

}

