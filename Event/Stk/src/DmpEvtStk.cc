
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtStk.hh"

DmpEvtStkRaw::DmpEvtStkRaw()
{}

DmpEvtStkRaw::~DmpEvtStkRaw(){
}

Bool_t DmpEvtStkRaw::BookBranch(){
  if (!fTree)   return false;
  BookBranchBasic("Stk");
  BookBranchSubDet("Stk");
  BookBranchStkRaw();
  return true;
}

void DmpEvtStkRaw::Reset(){
  fMode = kMixed;
  fNSignal = 0;
  fADC = 0;
}

void DmpEvtStkRaw::SetSignal(Float_t ADC){
  fMode = kCalPed;
  fADC = ADC;
  ++fNSignal;
}

void DmpEvtStkRaw::BookBranchStkRaw(){
  if (fRootFile) {
    fTree->SetBranchAddress("Stk_ACD",&fADC);
  } else {
    fTree->Branch("Stk_ACD",&fADC,"fADC/F");
  }
}


