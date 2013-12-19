/*=====================================================================
 *   File:   DmpVEvtManager.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:08:19
=====================================================================*/

#include "TString.h"

#include "DmpVEvtManager.hh"
#include "DmpEvtHeader.hh"
#include "DmpVEvtSubDet.hh"

ClassImp(DmpVEvtManager)

//------------------------------------------------------------------------------
DmpVEvtManager::DmpVEvtManager(){
  fHeader = new DmpEvtHeader();
  DmpVEvtSubDet::SetEventHeader(fHeader);
}

//------------------------------------------------------------------------------
DmpVEvtManager::~DmpVEvtManager(){
  delete fHeader;
}

