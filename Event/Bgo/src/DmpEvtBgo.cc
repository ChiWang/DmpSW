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
  fADC = new std::vector<int>();
}

DmpEvtBgoRaw::~DmpEvtBgoRaw(){
}

TTree* DmpEvtBgoRaw::GetTree(TString treeName){
  BookTree(treeName);
  BookBranchSubDet();
  fTree->Branch("LayerID",  &fLayerID);
  fTree->Branch("BarID",    &fBarID);
  fTree->Branch("SideID",   &fSideID);
  fTree->Branch("DyID",     &fDyID);
  fTree->Branch("ADC",      &fADC);
  return fTree;
}

TTree* DmpEvtBgoRaw::GetTree(TString treeName, TFile* rootFile){
  BookTree(treeName,rootFile);
  BookBranchSubDet();
  fTree->SetBranchAddress("LayerID",&fLayerID);
  fTree->SetBranchAddress("BarID",  &fBarID);
  fTree->SetBranchAddress("SideID", &fSideID);
  fTree->SetBranchAddress("DyID",   &fDyID);
  fTree->SetBranchAddress("ADC",    &fADC);
  return fTree;
}

void DmpEvtBgoRaw::Reset(){
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


