
#include "TTree.h"
#include "TString.h"

#include "DmpEvtNud.hh"

DmpEvtNudRaw::DmpEvtNudRaw(DmpEvtVBasicHeader* header)
 :DmpEvtVBasicSubDet(header)
{}

DmpEvtNudRaw::~DmpEvtNudRaw(){
}

Bool_t DmpEvtNudRaw::BookBranch(TTree* tree, Bool_t read, TString pre){
  BookBranchSubDet(tree, read, pre);
  BookBranchNudRaw(tree, read, pre);
  return true;
}


void DmpEvtNudRaw::Reset(){
  fMode = kMixed;
  fNHit = 0;
  fADC = 0;
}

void DmpEvtNudRaw::SetSignal(Float_t ADC){
  fADC = ADC;
  ++fNHit;
}

void DmpEvtNudRaw::BookBranchNudRaw(TTree* tree, Bool_t read, TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_ACD",&fADC);
  } else {
    tree->Branch(pre+"_ACD",&fADC,"fADC/F");
  }
}


