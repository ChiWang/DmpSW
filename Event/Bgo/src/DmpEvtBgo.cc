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

void DmpEvtBgoRaw::Reset(){
  fMode = kMixed;
  fNSignal = 0;
  fLayerID->clear();
  fBarID->clear();
  fSideID->clear();
  fDyID->clear();
  fADC->clear();
}

Bool_t DmpEvtBgoRaw::BookBranch(TTree* tree, Bool_t read, TString detector){
  BookBranchSubDet(tree,read,detector);
  BookBranchBgoRaw(tree,read,detector);
  return true;
}

void DmpEvtBgoRaw::SetSignal(Short_t LID,Short_t BID,Short_t SID,Short_t DID,Float_t ADC){
  fLayerID->push_back(LID);
  fBarID->push_back(BID);
  fSideID->push_back(SID);
  fDyID->push_back(DID);
  fADC->push_back(ADC);
  ++fNSignal;
}

void DmpEvtBgoRaw::BookBranchBgoRaw(TTree* tree, Bool_t read, TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_LayerID",&fLayerID);
    tree->SetBranchAddress(pre+"_BarID",  &fBarID);
    tree->SetBranchAddress(pre+"_SideID", &fSideID);
    tree->SetBranchAddress(pre+"_DyID",   &fDyID);
    tree->SetBranchAddress(pre+"_ADC",    &fADC);
  } else {
    tree->Branch(pre+"_LayerID",  &fLayerID);
    tree->Branch(pre+"_BarID",    &fBarID);
    tree->Branch(pre+"_SideID",   &fSideID);
    tree->Branch(pre+"_DyID",     &fDyID);
    tree->Branch(pre+"_ADC",      &fADC);
  }
}

