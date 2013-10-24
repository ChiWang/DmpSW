/*=============================================================================
#       FileName :          DmpCalL0Manager.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-18   14:36:08
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-18   14:36:20
=============================================================================*/

#include <iostream>

#include "TFile.h"
//#include "TTree.h"
#include "TH1F.h"

#include "DmpCalL0Manager.hh"

#include "DmpEvtHeader.hh"
#include "DmpEvtPsd.hh"
#include "DmpEvtStk.hh"
#include "DmpDcdParameterBgo.hh"
#include "DmpEvtBgo.hh"
#include "DmpEvtNud.hh"

using namespace DmpDcdParameter;

DmpCalL0Manager*  DmpCalL0Manager::fInstance=0;

DmpCalL0Manager*  DmpCalL0Manager::GetInstance(){
  if (fInstance == 0) {
    fInstance = new DmpCalL0Manager();
  }
  return fInstance;
}

void DmpCalL0Manager::Clear(){
  if (fInstance == 0) {
    return;
  } else {
    delete fInstance;
    fInstance = 0;
  }
  std::cout<<"\n\tdelete DmpCalL0 Manager"<<std::endl;
}

Bool_t DmpCalL0Manager::BookBranch(){
  Bool_t read = false;
  if (fInRootFile)  read = true;
  if ( ! fEvtHeader->BookBranch(fTree, read, "Header") ) return false;
  if ( ! fEvtPsd->BookBranch(fTree, read, "Psd") )    return false;
  if ( ! fEvtStk->BookBranch(fTree, read, "Stk") )    return false;
  if ( ! fEvtBgo->BookBranch(fTree, read, "Bgo") )    return false;
  if ( ! fEvtNud->BookBranch(fTree, read, "Nud") )    return false;
  return true;
}

void DmpCalL0Manager::SavePedestal(TString subDet){
  if (subDet == "Psd") {
  } else if (subDet == "Stk") {
  } else if (subDet == "Bgo") {
    SavePedestalBgo();
  } else if (subDet == "Nud") {
  } else {
    std::cout<<"Error: In DmpCalL0Manager::SavePedestal(TString subDet). subDet = {Psd | Stk | Bgo | Nud}"<<std::endl;
  }
}

DmpCalL0Manager::DmpCalL0Manager()
 :DmpVManager()
{
  fEvtHeader= new DmpEvtHeaderRaw();
  fEvtPsd   = new DmpEvtPsdRaw(fEvtHeader);
  fEvtStk   = new DmpEvtStkRaw(fEvtHeader);
  fEvtBgo   = new DmpEvtBgoRaw(fEvtHeader);
  fEvtNud   = new DmpEvtNudRaw(fEvtHeader);
  fHistBgo = new std::vector<TH1F*>();
  BookHistBgo();

  fHitOrder = new Short_t*** [Bgo::kPlaneNb];        // create 4 dimenstion array
  for(Short_t p=0;p<Bgo::kPlaneNb;++p){
    fHitOrder[p] = new Short_t** [Bgo::kSideNb*2];
    for(Short_t q=0;q<Bgo::kSideNb*2;++q){
      fHitOrder[p][q] = new Short_t* [Bgo::kDyNb];
      for(Short_t d=0;d<Bgo::kDyNb;++d){
        fHitOrder[p][q][d] = new Short_t [Bgo::kBarNb+Bgo::kRefBarNb];
      }
    }
  }
}

DmpCalL0Manager::~DmpCalL0Manager(){
  delete fEvtHeader;
  delete fEvtPsd;
  delete fEvtStk;
  delete fEvtBgo;
  delete fEvtNud;
  for (Int_t i=0;i<fHistBgo->size();++i) {
    delete fHistBgo->at(i);
  }
  delete fHistBgo;
  for(Short_t p=0;p<Bgo::kPlaneNb;++p){
    for(Short_t q=0;q<Bgo::kSideNb*2;++q){
      for(Short_t d=0;d<Bgo::kDyNb;++d){
        delete[] fHitOrder[p][q][d];
      }
      delete[] fHitOrder[p][q];
    }
    delete[] fHitOrder[p];
  }
  delete[] fHitOrder;
}

void DmpCalL0Manager::FillPedestal(TString subDet){
  if (subDet == "Psd") {
  } else if (subDet == "Stk") {
  } else if (subDet == "Bgo") {
    FillPedestalBgo();
  } else if (subDet == "Nud") {
  } else {
    std::cout<<"Error: In DmpCalL0Manager::FillPedestal(TString subDet). subDet = {Psd | Stk | Bgo | Nud}"<<std::endl;
  }
}

