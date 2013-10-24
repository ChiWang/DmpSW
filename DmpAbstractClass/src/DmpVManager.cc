/*=============================================================================
#       FileName :          DmpVManager.cc
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
#                                          Update:  2013-10-17   17:27:58
=============================================================================*/

#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "DmpVManager.hh"

using namespace std;


DmpVManager::DmpVManager()
 :fInDataPath("./"),
  fOutDataPath("./"),
  fDataName(""),
  fInRootFile(0),
  fOutRootFile(0),
  fTree(0)
{
}

DmpVManager::~DmpVManager(){
  if (fOutRootFile) {
    delete fOutRootFile;
    fOutRootFile = 0;
  }
}

void DmpVManager::SetInDataPath(TString path){
  if (path.EndsWith("/")) {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
}
#include <sys/stat.h>
void DmpVManager::SetOutDataPath(TString path){
  if (path.EndsWith("/")) {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  mkdir(fOutDataPath,0755);
}

void DmpVManager::ResetRootFile(){
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

Bool_t DmpVManager::BookTree(){
  TString treeName = "dampe";
  if (fDataName.Contains(".root")) {
    fInRootFile = new TFile(fInDataPath+fDataName,"READ");
    if (fInRootFile->IsZombie()) {
      cout<<"\nOpen "<<fInDataPath+fDataName<<"failed..."<<endl;
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

void DmpVManager::SaveRootFile(){
}

