/*
 *  $Id: DmpRdcAlgStk.cc, 2014-05-28 13:15:04 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "DmpRdcAlgBT2012.h"
#include "DmpIOSvc.h"

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::InitialiseStk(){
  if(fCNCTPathStk == "NO"){
    LogWarning<<"No set connector:\tStk"<<std::endl;
    return true;
  }else{
    LogInfor<<"Setting connector:\tStk"<<std::endl;
  }
  // setup connector
// *
// *  TODO: set method?
// *
  fCNCTDoneStk = true;
  fStkLadderSet = new TClonesArray("DmpEvtRdcMSD",90); // TODO ,size ??
  DmpIOSvc::GetInstance()->AddBranch("Rdc/Stk",fStkLadderSet);
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::ProcessThisEventStk(){
  fStkLadderSet->Delete();
  fStkLadderSet->Clear();
  static int inPos = 0, outPos = 0;
  inPos = fFile.tellg();
//-------------------------------------------------------------------
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0, data=0;
  static unsigned short data2=0;
//-------------------------------------------------------------------
// *
// *  TODO: conversion bgo
// *
//-------------------------------------------------------------------
  outPos = fFile.tellg();
  LogDebug<<"from "<<inPos<<" to "<<outPos<<"\t---> signalNo = "<<nSignal<<std::endl;
  return true;
}

//-------------------------------------------------------------------
void DmpRdcAlgBT2012::AppendSignalStk(const int &id,const int &v){
// *
// *  TODO: example bgo
// *
}

//-------------------------------------------------------------------
bool DmpRdcAlgBT2012::FinalizeStk(){
  if(fCNCTDoneStk){
    delete fStkLadderSet;
  }
  return true;
}

