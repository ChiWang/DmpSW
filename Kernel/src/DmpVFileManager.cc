/*=====================================================================
 *   File:   DmpVFileManager.cc
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

#include "DmpVFileManager.hh"

ClassImp(DmpVFileManager)

//------------------------------------------------------------------------------
DmpVFileManager::DmpVFileManager()
 :fInDataPath("./"),
  fOutDataPath("./"),
  fDataName("")
{}

//------------------------------------------------------------------------------
DmpVFileManager::~DmpVFileManager()
{}

//------------------------------------------------------------------------------
void DmpVFileManager::SetInDataPath(TString path){
  if (path.EndsWith("/")) {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
}

//------------------------------------------------------------------------------
void DmpVFileManager::SetOutDataPath(TString path){
  if (path.EndsWith("/")) {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  gSystem->MakeDirectory(fOutDataPath);
}

