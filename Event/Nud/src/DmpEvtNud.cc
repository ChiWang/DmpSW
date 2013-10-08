
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtNud.hh"

DmpEvtNudRaw::DmpEvtNudRaw()
{}

DmpEvtNudRaw::~DmpEvtNudRaw(){
}

TTree* DmpEvtNudRaw::GetTree(TString treeName){
  BookTree(treeName);
  BookBranchSubDet();
  fTree->Branch("ACD",&fADC,"fADC/F");
  return fTree;
}

TTree* DmpEvtNudRaw::GetTree(TString treeName,TFile* rootFile){
  BookTree(treeName,rootFile);
  BookBranchSubDet();
  fTree->SetBranchAddress("ACD",&fADC);
  return fTree;
}

void DmpEvtNudRaw::Reset(){
  fNSignal = 0;
  fADC = 0;
}

void DmpEvtNudRaw::SetSignal(Float_t ADC){
  fADC = ADC;
  ++fNSignal;
}


