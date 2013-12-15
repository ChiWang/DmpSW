/*=====================================================================
 *   File:   DmpFileManager.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:09:47
=====================================================================*/

#include <iostream>

#include "TSystem.h"

#include "DmpFileManager.hh"

ClassImp(DmpFileManager)

//------------------------------------------------------------------------------
DmpFileManager::DmpFileManager()
 :fInDataPath("./"),
  fOutDataPath("./"),
  fDataName("")
{}

//------------------------------------------------------------------------------
DmpFileManager::~DmpFileManager()
{}

//------------------------------------------------------------------------------
void DmpFileManager::SetInDataPath(TString path){
  if (path.EndsWith("/")) {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
}

//------------------------------------------------------------------------------
void DmpFileManager::SetOutDataPath(TString path){
  if (path.EndsWith("/")) {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  gSystem->MakeDirectory(fOutDataPath);
}

