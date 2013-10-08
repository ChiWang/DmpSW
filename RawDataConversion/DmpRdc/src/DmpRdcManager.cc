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

using namespace std;

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
  cout<<"delete DmpRdc Manager"<<endl;
}

DmpRdcManager::DmpRdcManager()
 :fOutDataFile(0)
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
    fHeader->GetEventPointer()->SetMode(fPsd->GetEventPointer()->GetMode(),fStk->GetEventPointer()->GetMode(),fBgo->GetEventPointer()->GetMode(),fNud->GetEventPointer()->GetMode());
  } else {
    cout<<"\t\t----> Fill event failed:\ttrigger not match\n"<<endl;
    return;
  }
  fHeader->GetTree()->Fill();
  fPsd->GetTree()->Fill();
  fStk->GetTree()->Fill();
  fBgo->GetTree()->Fill();
  fNud->GetTree()->Fill();
#ifdef DEBUG
  cout<<"Fill event "<<fHeader->GetEventPointer()->GetEventID()<<endl<<endl;
#endif
}

void DmpRdcManager::SaveRootFile(){
  fDataName.ReplaceAll(".dat","-rec0.root");
  
  fOutDataFile = new TFile(fOutDataPath+fDataName,"RECREATE");
  fHeader->GetTree()->Write();
  fPsd->GetTree()->Write();
  fStk->GetTree()->Write();
  fBgo->GetTree()->Write();
  fNud->GetTree()->Write();

  fOutDataFile->Close();
  delete fOutDataFile;
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

