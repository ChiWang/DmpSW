/*=============================================================================
#       FileName :          DmpEvtVBasicSubDetSubDet.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-03   22:01:24
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-04   09:08:49
=============================================================================*/

#include "TTree.h"

#include "DmpEvtVBasicSubDet.hh"

DmpEvtVBasicSubDet::DmpEvtVBasicSubDet()
 :fNSignal(0)
{}

DmpEvtVBasicSubDet::~DmpEvtVBasicSubDet()
{}

void DmpEvtVBasicSubDet::Reset(){
}

Bool_t  DmpEvtVBasicSubDet::BookBranch(TTree* tree, Bool_t read, TString detector){
}

void DmpEvtVBasicSubDet::BookBranchSubDet(TTree* tree, Bool_t read,TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_Mode",&fMode);
    tree->SetBranchAddress(pre+"_NSignal",&fNSignal);
  } else {
    tree->Branch(pre+"_Mode",&fMode,"fMode/S");
    tree->Branch(pre+"_NSignal",&fNSignal,"fNSignal/S");
  }
}

