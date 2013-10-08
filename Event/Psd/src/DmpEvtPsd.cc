
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtPsd.hh"

DmpEvtPsdRaw::DmpEvtPsdRaw()
{}

DmpEvtPsdRaw::~DmpEvtPsdRaw(){
}

void DmpEvtPsdRaw::SetSignal(Float_t ADC){
  fADC = ADC;
  ++fNSignal;
}

TTree* DmpEvtPsdRaw::GetTree(TString treeName){
  BookTree(treeName);
  BookBranchSubDet();
  fTree->Branch("ACD",&fADC,"fADC/F");
  return fTree;
}

TTree* DmpEvtPsdRaw::GetTree(TString treeName,TFile* rootFile){
  BookTree(treeName,rootFile);
  BookBranchSubDet();
  fTree->SetBranchAddress("ACD",&fADC);
  return fTree;
}


