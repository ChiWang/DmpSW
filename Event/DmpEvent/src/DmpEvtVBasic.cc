/*=============================================================================
#       FileName :          DmpEvtVBasic.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-03   21:29:20
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-03   21:29:20
=============================================================================*/


#ifdef DEBUG
#include <iostream>
using namespace std;
#endif
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtVBasic.hh"


TTree*  DmpEvtVBasic::fTree = 0;
TFile*  DmpEvtVBasic::fRootFile = 0;

DmpEvtVBasic::DmpEvtVBasic()
 :fMode(kMixed)
{}

DmpEvtVBasic::~DmpEvtVBasic()
{}

Bool_t  DmpEvtVBasic::BookTree(TString treeName, TFile* rootFile){
  fRootFile = rootFile;         // defualt rootFile = 0
  if (fRootFile) {
    fTree = (TTree*)fRootFile->Get(treeName);
  } else {
    fTree = new TTree(treeName,treeName);
  }
  return true;
}

void DmpEvtVBasic::BookBranchBasic(TString pre){
  if (fRootFile) {
    fTree->SetBranchAddress(pre+"_Mode",&fMode);
  } else {
    fTree->Branch(pre+"_Mode",&fMode,"fMode/S");
  }
}



