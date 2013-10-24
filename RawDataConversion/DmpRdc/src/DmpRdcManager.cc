/*=============================================================================
#       FileName :          DmpRdcManager.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-07   10:52:13
#
#------------------------------------------------------------------------------
#       Description  :
#           closed TriggerCheck
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-07   00:57:47
=============================================================================*/

#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "DmpRdcManager.hh"

#include "DmpEvtHeader.hh"
#include "DmpEvtPsd.hh"
#include "DmpEvtStk.hh"
#include "DmpEvtBgo.hh"
#include "DmpEvtNud.hh"

#include "DmpRdcHeader.hh"
#include "DmpRdcPsd.hh"
#include "DmpRdcStk.hh"
#include "DmpRdcBgo.hh"
#include "DmpRdcNud.hh"

DmpRdcManager*  DmpRdcManager::fInstance=0;

DmpRdcManager*  DmpRdcManager::GetInstance(){
  if (fInstance == 0) {
    fInstance = new DmpRdcManager();
  }
  return fInstance;
}

void DmpRdcManager::Clear(){
  if (fInstance == 0) {
    return;
  } else {
    delete fInstance;
    fInstance = 0;
  }
  std::cout<<"delete DmpRdc Manager"<<std::endl;
}
/*
TTree* DmpRdcManager::BookTree(TString treeName){
  fTree = new TTree(treeName,treeName);
  return fTree;
}
*/

Bool_t DmpRdcManager::BookBranch(){
  Bool_t read = false;
  if (fInRootFile)  read = true;
  if ( ! fHeader->GetEventPointer()->BookBranch(fTree, read, "Header") ) return false;
  if ( ! fPsd->GetEventPointer()->BookBranch(fTree, read, "Psd") )    return false;
  if ( ! fStk->GetEventPointer()->BookBranch(fTree, read, "Stk") )    return false;
  if ( ! fBgo->GetEventPointer()->BookBranch(fTree, read, "Bgo") )    return false;
  if ( ! fNud->GetEventPointer()->BookBranch(fTree, read, "Nud") )    return false;
  return true;
}

DmpRdcManager::DmpRdcManager()
 :DmpVManager()
{
  fHeader = new DmpRdcHeader();
  fPsd = new DmpRdcPsd();
  fStk = new DmpRdcStk();
  fBgo = new DmpRdcBgo();
  fNud = new DmpRdcNud();
}

DmpRdcManager::~DmpRdcManager(){
    delete fHeader;
    delete fPsd;
    delete fStk;
    delete fBgo;
    delete fNud;
}

void DmpRdcManager::FillAnEvent(){
  if (TriggerCheck() == true) {
    fHeader->GetEventPointer()->IsValidEvent();
  } else {
    std::cout<<"\t\t----> Fill event failed:\ttrigger not match\n"<<std::endl;
    return;
  }
  fTree->Fill();
#ifdef DEBUG
  //std::cout<<"Fill event "<<dec<<fHeader->GetEventPointer()->GetEventID()<<std::endl<<std::endl;
#endif
}

void DmpRdcManager::SaveRootFile(){
  fDataName.ReplaceAll(".dat","-rec0.root");
  fOutRootFile = new TFile(fOutDataPath+fDataName,"RECREATE");
  fTree->Write();
  fOutRootFile->Close();
  delete fOutRootFile;
  fOutRootFile = 0;
  fHeader->GetEventPointer()->Reset();
  Reset();
}

Bool_t DmpRdcManager::TriggerCheck() const {
  Bool_t Ans=true;
  Short_t tH = fHeader->GetTrigger();
  Short_t tP = fPsd->GetTrigger();
  Short_t tS = fStk->GetTrigger();
  Short_t tB = fBgo->GetTrigger();
  Short_t tN = fNud->GetTrigger();
  if (tH!=tP || tP!=tS || tP!=tB || tB!=tN) {
    Ans = false;
  }
  return true;
  //return Ans;
}

