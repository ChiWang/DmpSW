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
    DmpLogWarning<<"No set connector:\tStk"<<DmpLogEndl;
    return true;
  }else{
    DmpLogInfo<<"Setting connector:\tStk"<<DmpLogEndl;
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
//-------------------------------------------------------------------
  static short feeCounts=0, feeID=0, nBytes=0, nSignal=0, channelID=0, data=0;
  static unsigned short data2=0;
//-------------------------------------------------------------------
// *
// *  TODO: conversion bgo
// *
//-------------------------------------------------------------------
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

