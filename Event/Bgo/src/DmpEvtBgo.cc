/*=============================================================================
#       FileName :          DmpEvtBgo.cc
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-16   11:00:27
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-03   20:04:22
=============================================================================*/

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "DmpEvtBgo.hh"


DmpEvtBgoRaw::DmpEvtBgoRaw(){
  fLayerID = new std::vector<int>();
  fBarID = new std::vector<int>();
  fSideID = new std::vector<int>();
  fDyID = new std::vector<int>();
  fADC = new std::vector<double>();
}

DmpEvtBgoRaw::~DmpEvtBgoRaw(){
}

Bool_t DmpEvtBgoRaw::BookBranch(){
  if (!fTree)   return false;
  BookBranchBasic("Bgo");
  BookBranchSubDet("Bgo");
  BookBranchBgoRaw();
  return true;
}

void DmpEvtBgoRaw::Reset(){
  fMode = kMixed;
  fNSignal = 0;
  fLayerID->clear();
  fBarID->clear();
  fSideID->clear();
  fDyID->clear();
  fADC->clear();
}

void DmpEvtBgoRaw::SetSignal(Short_t LID,Short_t BID,Short_t SID,Short_t DID,Float_t ADC){
  fLayerID->push_back(LID);
  fBarID->push_back(BID);
  fSideID->push_back(SID);
  fDyID->push_back(DID);
  fADC->push_back(ADC);
  ++fNSignal;
}

void DmpEvtBgoRaw::BookBranchBgoRaw(){
  if (fRootFile) {
    fTree->SetBranchAddress("Bgo_LayerID",&fLayerID);
    fTree->SetBranchAddress("Bgo_BarID",  &fBarID);
    fTree->SetBranchAddress("Bgo_SideID", &fSideID);
    fTree->SetBranchAddress("Bgo_DyID",   &fDyID);
    fTree->SetBranchAddress("Bgo_ADC",    &fADC);
  } else {
    fTree->Branch("Bgo_LayerID",  &fLayerID);
    fTree->Branch("Bgo_BarID",    &fBarID);
    fTree->Branch("Bgo_SideID",   &fSideID);
    fTree->Branch("Bgo_DyID",     &fDyID);
    fTree->Branch("Bgo_ADC",      &fADC);
  }
}

