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

#include <iostream>

#include "TTree.h"
#include "TString.h"

#include "DmpEvtHeader.hh"
#include "DmpEvtBgo.hh"

DmpEvtBgoRaw::DmpEvtBgoRaw(DmpEvtVBasicHeader* header)
 :DmpEvtVBasicSubDet(header)
{
  fPlaneID  = new std::vector<int>;
  fQuadrantID = new std::vector<int>;
  fBarID= new std::vector<int>;
  fDyID = new std::vector<int>;
  fADC  = new std::vector<double>;
}

DmpEvtBgoRaw::~DmpEvtBgoRaw(){
  delete fPlaneID;
  delete fQuadrantID;
  delete fBarID;
  delete fDyID;
  delete fADC;
}

void DmpEvtBgoRaw::Reset(){
  fMode = kMixed;
  fNHit = 0;
  fPlaneID->clear();
  fQuadrantID->clear();
  fBarID->clear();
  fDyID->clear();
  fADC->clear();
}

Bool_t DmpEvtBgoRaw::BookBranch(TTree* tree, Bool_t read, TString detector){
  BookBranchSubDet(tree,read,detector);
  BookBranchBgoRaw(tree,read,detector);
  return true;
}

void DmpEvtBgoRaw::PrintEvent() const{
  std::cout<<"--->  Bgo:\tEvent ID = "<<fEvtHeader->GetEventID()<<std::endl;
  std::cout<<"Plane | Quadrant | Bar | Dy | ADC"<<std::endl;
  for (Int_t i=0;i<fNHit;++i) {
    std::cout<<(*fPlaneID)[i]<<"\t"<<fQuadrantID->at(i)<<"\t"<<fBarID->at(i)<<"\t"<<fDyID->at(i)<<"\t"<<fADC->at(i)<<std::endl;
  }
}

void DmpEvtBgoRaw::SetSignal(Short_t LID,Short_t SID,Short_t BID,Short_t DID,Float_t ADC){
  fPlaneID->push_back(LID);
  fQuadrantID->push_back(SID);
  fBarID->push_back(BID);
  fDyID->push_back(DID);
  fADC->push_back(ADC);
  ++fNHit;
}

std::vector<int>* DmpEvtBgoRaw::GetEvent(TString name){
  if (name == "PlaneID") {
    return fPlaneID;
  } else if (name == "QuadrantID") {
    return fQuadrantID;
  } else if (name == "BarID") {
    return fBarID;
  } else if (name == "DyID") {
    return fDyID;
  } else {
    std::cout<<"Error:\tIn DmpEvtBgoRaw::GetEvent(TString ID), ID = {PlaneID | QuadrantID | BarID | DyID}"<<std::endl;
  }
}

std::vector<double>* DmpEvtBgoRaw::GetEventADC(){
  return fADC;
}

void DmpEvtBgoRaw::BookBranchBgoRaw(TTree* tree, Bool_t read, TString pre){
  if (read) {
    tree->SetBranchAddress(pre+"_PlaneID",   &fPlaneID);
    tree->SetBranchAddress(pre+"_QuadrantID",&fQuadrantID);
    tree->SetBranchAddress(pre+"_BarID",     &fBarID);
    tree->SetBranchAddress(pre+"_DyID",      &fDyID);
    tree->SetBranchAddress(pre+"_ADC",       &fADC);
  } else {
    tree->Branch(pre+"_PlaneID",    &fPlaneID);
    tree->Branch(pre+"_QuadrantID", &fQuadrantID);
    tree->Branch(pre+"_BarID",      &fBarID);
    tree->Branch(pre+"_DyID",       &fDyID);
    tree->Branch(pre+"_ADC",        &fADC);
  }
}

