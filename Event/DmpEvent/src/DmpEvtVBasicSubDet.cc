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
#ifdef DEBUG
#include <iostream>
#endif
#include "TTree.h"

#include "DmpEvtVBasicSubDet.hh"

DmpEvtVBasicSubDet::DmpEvtVBasicSubDet(DmpEvtVBasicHeader* header)
 :fNHit(0),
  fEvtHeader(header)
{}

DmpEvtVBasicSubDet::~DmpEvtVBasicSubDet()
{}

void DmpEvtVBasicSubDet::PrintEvent() const{
}

void DmpEvtVBasicSubDet::BookBranchSubDet(TTree* tree, Bool_t read,TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_Mode",&fMode);
    tree->SetBranchAddress(pre+"_NHit",&fNHit);
  } else {
    tree->Branch(pre+"_Mode",&fMode,"fMode/S");
    tree->Branch(pre+"_NHit",&fNHit,"fNHit/I");
  }
}

