
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtStk.hh"

DmpEvtStkRaw::DmpEvtStkRaw()
{}

DmpEvtStkRaw::~DmpEvtStkRaw(){
}

void DmpEvtStkRaw::SetSignal(Float_t ADC){
  fADC = ADC;
  ++fNSignal;
}

TTree* DmpEvtStkRaw::GetTree(TString treeName){
  BookTree(treeName);
  BookBranchSubDet();
  fTree->Branch("ACD",&fADC,"fADC/F");
  return fTree;
}

TTree* DmpEvtStkRaw::GetTree(TString treeName,TFile* rootFile){
  BookTree(treeName,rootFile);
  BookBranchSubDet();
  fTree->SetBranchAddress("ACD",&fADC);
  return fTree;
}


