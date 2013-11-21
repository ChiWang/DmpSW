/*=============================================================================
#       FileName :          DmpEvtAbsHeader.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-03   10:01:28
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-25   19:00:08
=============================================================================*/

#include <iostream>

#include "TTree.h"
#include "TMath.h"

#include "DmpEvtAbsHeader.hh"

using namespace TMath;

ClassImp(DmpEvtAbsHeader)

//______________________________________________________________________________
DmpEvtAbsHeader::DmpEvtAbsHeader()
 :fEvtID(-1),
  fSec(0),
  fmSec(0),
  fTimeGap(0),
  fPID(kUnknown)
{}

//______________________________________________________________________________
DmpEvtAbsHeader::~DmpEvtAbsHeader()
{}

//______________________________________________________________________________
void DmpEvtAbsHeader::ShowTime() const{
  std::cout<<"Normal time:"<<std::endl;
  std::cout<<"Hex time:"<<std::endl;
}

//______________________________________________________________________________
void DmpEvtAbsHeader::BookBranchAbsHeader(TTree *tree, Bool_t read, TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_EventID",  &fEvtID);
    tree->SetBranchAddress(pre+"_Second",   &fSec);
    tree->SetBranchAddress(pre+"_mSecond",  &fmSec);
    tree->SetBranchAddress(pre+"_TimeGap",  &fTimeGap);
    tree->SetBranchAddress(pre+"_ParticleID",&fPID);
  } else {
    tree->Branch(pre+"_EventID",&fEvtID,"fEvtID/L");
    tree->Branch(pre+"_Second", &fSec,"fSec/L");
    tree->Branch(pre+"_mSecond",&fmSec,"fSec/S");
    tree->Branch(pre+"_TimeGap",&fTimeGap,"fTimeGap/L");
    tree->Branch(pre+"_ParticleID",&fPID,"fPID/S");
  }
}


