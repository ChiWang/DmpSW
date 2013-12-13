/*=====================================================================
 *   File:   DmpEvtManager.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:08:19
=====================================================================*/

#include "TString.h"

#include "DmpEvtManager.hh"
#include "DmpEvtHeader.hh"
#include "DmpEvtSubDet.hh"

ClassImp(DmpEvtManager)

//------------------------------------------------------------------------------
DmpEvtManager::DmpEvtManager(){
  fHeader = new DmpEvtHeader();
  DmpEvtSubDet::SetEventHeader(fHeader);
}

//------------------------------------------------------------------------------
DmpEvtManager::~DmpEvtManager(){
  delete fHeader;
}

//------------------------------------------------------------------------------
DmpEvtSubDet*  DmpEvtManager::GetEventPointer(TString subDet){
  return 0;
}

