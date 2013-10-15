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

DmpEvtVBasic::DmpEvtVBasic()
 :fNewTree(true),
  fTree(0),
  fMode(kCompress)
{}

DmpEvtVBasic::~DmpEvtVBasic()
{}

TTree* DmpEvtVBasic::GetTree(TString treeName){
  return fTree;
}

TTree* DmpEvtVBasic::GetTree(TString treeName,TFile* rootFile){
  return fTree;
}

void DmpEvtVBasic::Reset(){
}

void DmpEvtVBasic::BookTree(TString treeName){
  fNewTree = true;
  fTree = new TTree(treeName,treeName);
  fTree->Branch("Mode",&fMode,"fMode/S");
}

void DmpEvtVBasic::BookTree(TString treeName, TFile* rootFile){
  fNewTree = false;
  TTree* fTree = (TTree*)rootFile->Get(treeName);
  fTree->SetBranchAddress("Mode",&fMode);
}


