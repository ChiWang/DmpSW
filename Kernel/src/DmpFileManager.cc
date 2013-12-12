/*=============================================================================
#       FileName :          DmpFileManager.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-17   17:27:58
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-11-11   09:08:42
=============================================================================*/

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
DmpFileManager::~DmpFileManager(){
}

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

