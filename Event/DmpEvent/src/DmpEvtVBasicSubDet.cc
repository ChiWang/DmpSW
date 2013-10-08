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

void DmpEvtVBasicSubDet::BookBranchSubDet(){
  if (fNewTree) {
    fTree->Branch("NSignal",&fNSignal,"fNSignal/S");
  } else {
    fTree->SetBranchAddress("NSignal",&fNSignal);
  }
}

