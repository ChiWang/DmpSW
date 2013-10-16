
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtPsd.hh"

DmpEvtPsdRaw::DmpEvtPsdRaw()
{}

DmpEvtPsdRaw::~DmpEvtPsdRaw(){
}

Bool_t DmpEvtPsdRaw::BookBranch(){
  if (!fTree)   return false;
  BookBranchBasic("Psd");
  BookBranchSubDet("Psd");
  BookBranchPsdRaw();
  return true;
}

void DmpEvtPsdRaw::Reset(){
  fMode = kMixed;
  fNSignal = 0;
  fADC = 0;
}

void DmpEvtPsdRaw::SetSignal(Float_t ADC){
  fADC = ADC;
  ++fNSignal;
}

void DmpEvtPsdRaw::BookBranchPsdRaw(){
  if (fRootFile) {
    fTree->SetBranchAddress("Psd_ACD",&fADC);
  } else {
    fTree->Branch("Psd_ACD",&fADC,"fADC/F");
  }
}


