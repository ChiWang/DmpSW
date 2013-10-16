
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtNud.hh"

DmpEvtNudRaw::DmpEvtNudRaw()
{}

DmpEvtNudRaw::~DmpEvtNudRaw(){
}

Bool_t DmpEvtNudRaw::BookBranch(){
  if (!fTree)   return false;
  BookBranchBasic("Nud");
  BookBranchSubDet("Nud");
  BookBranchNudRaw();
  return true;
}


void DmpEvtNudRaw::Reset(){
  fMode = kMixed;
  fNSignal = 0;
  fADC = 0;
}

void DmpEvtNudRaw::SetSignal(Float_t ADC){
  fADC = ADC;
  ++fNSignal;
}

void DmpEvtNudRaw::BookBranchNudRaw(){
  if (fRootFile) {
    fTree->SetBranchAddress("Nud_ACD",&fADC);
  } else {
    fTree->Branch("Nud_ACD",&fADC,"fADC/F");
  }
}


