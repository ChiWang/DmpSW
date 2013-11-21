/*=============================================================================
#       FileName :          DmpEvtAbsSubDetSubDet.cc
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

#include "DmpEvtAbsSubDet.hh"

ClassImp(DmpEvtAbsSubDet)

//______________________________________________________________________________
DmpEvtAbsSubDet::DmpEvtAbsSubDet()
 :fEvtHeader(0),
  fMode(kMixed),
  fNHit(0)
{}

//______________________________________________________________________________
DmpEvtAbsSubDet::DmpEvtAbsSubDet(DmpEvtAbsHeader *header)
 :fEvtHeader(header),
  fMode(kMixed),
  fNHit(0)
{}

//______________________________________________________________________________
DmpEvtAbsSubDet::~DmpEvtAbsSubDet()
{}

//______________________________________________________________________________
void DmpEvtAbsSubDet::BookBranchAbsSubDet(TTree *tree, Bool_t read,TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_Mode",&fMode);
    tree->SetBranchAddress(pre+"_NHit",&fNHit);
  } else {
    tree->Branch(pre+"_Mode",&fMode,"fMode/S");
    tree->Branch(pre+"_NHit",&fNHit,"fNHit/I");
  }
}

