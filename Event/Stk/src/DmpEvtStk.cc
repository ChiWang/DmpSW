
#include "TTree.h"
#include "TString.h"

#include "DmpEvtStk.hh"

DmpEvtStkRaw::DmpEvtStkRaw(DmpEvtVHeader* header)
 :DmpEvtVSubDet(header)
{}

DmpEvtStkRaw::~DmpEvtStkRaw(){
}

Bool_t DmpEvtStkRaw::BookBranch(TTree *tree, Bool_t read, TString pre){
  BookBranchVSubDet(tree, read, pre);
  BookBranchStkRaw(tree, read, pre);
  return true;
}

void DmpEvtStkRaw::Reset(){
  fMode = kMixed;
  fNHit = 0;
  fADC = 0;
}

void DmpEvtStkRaw::SetSignal(Float_t ADC){
  fMode = kCalPed;
  fADC = ADC;
  ++fNHit;
}

void DmpEvtStkRaw::BookBranchStkRaw(TTree *tree, Bool_t read, TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_ACD",&fADC);
  } else {
    tree->Branch(pre+"_ACD",&fADC,"fADC/F");
  }
}


