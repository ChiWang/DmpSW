/*=============================================================================
#       FileName :          DmpAbsManager.cc
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
#include "TFile.h"
#include "TTree.h"

#include "DmpAbsManager.hh"

//ClassImp(DmpAbsManager);      // adding class in root

DmpAbsManager::DmpAbsManager()
 :fInDataPath("./"),
  fOutDataPath("./"),
  fDataName(""),
  fInRootFile(0),
  fOutRootFile(0),
  fTree(0)
{
}

DmpAbsManager::~DmpAbsManager(){
  if (fOutRootFile) {
    delete fOutRootFile;
    fOutRootFile = 0;
  }
}

void DmpAbsManager::SetInDataPath(TString path){
  if (path.EndsWith("/")) {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
}

void DmpAbsManager::SetOutDataPath(TString path){
  if (path.EndsWith("/")) {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  gSystem->MakeDirectory(fOutDataPath);
}

void DmpAbsManager::ResetRootFile(){
  if (fInRootFile) {
    fInRootFile->Close();
    delete fInRootFile;
    fInRootFile = 0;
  }
  if (fOutRootFile) {
    fOutRootFile->Close();
    delete fOutRootFile;
    fOutRootFile = 0;
  }
}

Bool_t DmpAbsManager::BookTree(){
  TString treeName = "dampe";
  if (fDataName.Contains(".root")) {
    fInRootFile = new TFile(fInDataPath+fDataName,"READ");
    if (fInRootFile->IsZombie()) {
      std::cerr<<"\nOpen "<<fInDataPath+fDataName<<"failed..."<<std::endl;
      return false;
    } else {
      fTree = (TTree*)fInRootFile->Get(treeName);
    }
  } else {
    fInRootFile = 0;
    fTree = new TTree(treeName,treeName);
  }
  return true;
}

void DmpAbsManager::SaveRootFile(){
}


