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

void DmpEvtVBasicSubDet::BookBranchSubDet(TString dec){
  if (fRootFile) {
    fTree->SetBranchAddress(dec+"_NSignal",&fNSignal);
  } else {
    fTree->Branch(dec+"_NSignal",&fNSignal,"fNSignal/S");
  }
}

