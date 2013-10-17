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
#include "TTree.h"
#include "TString.h"

#include "DmpEvtVBasic.hh"

DmpEvtVBasic::DmpEvtVBasic()
 :fMode(kMixed)
{}

DmpEvtVBasic::~DmpEvtVBasic()
{}

Bool_t  DmpEvtVBasic::BookBranch(TTree* tree, Bool_t read, TString detector){
}

void DmpEvtVBasic::BookBranchBasic(TTree* tree,Bool_t read,TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_Mode",&fMode);
  } else {
    tree->Branch(pre+"_Mode",&fMode,"fMode/S");
  }
}



