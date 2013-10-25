
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtPsd.hh"

DmpEvtPsdRaw::DmpEvtPsdRaw(DmpEvtVHeader* header)
 :DmpEvtVSubDet(header)
{}

DmpEvtPsdRaw::~DmpEvtPsdRaw(){
}

Bool_t DmpEvtPsdRaw::BookBranch(TTree *tree, Bool_t read, TString pre){
  BookBranchVSubDet(tree, read,pre);
  BookBranchPsdRaw(tree, read, pre);
  return true;
}

void DmpEvtPsdRaw::Reset(){
  fMode = kMixed;
  fNHit = 0;
  fADC = 0;
}

void DmpEvtPsdRaw::SetSignal(Float_t ADC){
  fADC = ADC;
  ++fNHit;
}

void DmpEvtPsdRaw::BookBranchPsdRaw(TTree *tree, Bool_t read, TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_ACD",&fADC);
  } else {
    tree->Branch(pre+"_ACD",&fADC,"fADC/F");
  }
}


