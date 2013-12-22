/*=====================================================================
 *   File:   DmpVManager.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:08:19
=====================================================================*/

#include <iostream>
#include "TSystem.h"

#include "DmpVManager.hh"
#include "DmpEvtHeader.hh"
#include "DmpVEvtSubDet.hh"

ClassImp(DmpVManager)

//------------------------------------------------------------------------------
DmpVManager::DmpVManager()
 :fInDataPath("./"),
  fOutDataPath("./"),
  fDataName("")
{
  fHeader = new DmpEvtHeader();
  DmpVEvtSubDet::SetEventHeader(fHeader);
}

//------------------------------------------------------------------------------
DmpVManager::~DmpVManager(){
  delete fHeader;
}

//------------------------------------------------------------------------------
void DmpVManager::SetInDataPath(TString path){
  if (path.EndsWith("/")) {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
}

//------------------------------------------------------------------------------
void DmpVManager::SetOutDataPath(TString path){
  if (path.EndsWith("/")) {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  gSystem->MakeDirectory(fOutDataPath);
}

