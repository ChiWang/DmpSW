/*=============================================================================
#       FileName :          DmpRdcManager.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-07   10:52:13
#
#------------------------------------------------------------------------------
#       Description  :
#           This file only implement functions of manager, functions of sub-detector in ../sub-det/src/*.cc
#           closed TriggerCheck()
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

DmpRdcManager* DmpRdcManager::fInstance=0;

DmpRdcManager* DmpRdcManager::GetInstance(){
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
  std::cout<<"\ndelete DmpRdc Manager"<<std::endl;
}

Bool_t DmpRdcManager::BookBranch(){
  Bool_t read = false;
  if (fInRootFile)  read = true;
  if ( ! fEvtHeader->BookBranch(fTree, read, "Header") ) return false;
  if ( ! fEvtPsd->BookBranch(fTree, read, "Psd") )    return false;
  if ( ! fEvtStk->BookBranch(fTree, read, "Stk") )    return false;
  if ( ! fEvtBgo->BookBranch(fTree, read, "Bgo") )    return false;
  if ( ! fEvtNud->BookBranch(fTree, read, "Nud") )    return false;
  return true;
}

DmpRdcManager::DmpRdcManager()
 :DmpVManager(),
#ifdef Dmp_DEBUG
  fConnectorPath("../DetectorCondition/Connector")
#endif
#ifdef Dmp_RELEASE
  fConnectorPath("Absolute path of /prefix/share/connector")
#endif
{
  fEvtHeader = new DmpEvtHeaderRaw();        // must before subDet
  ConstructorPsd();
  ConstructorStk();
  ConstructorBgo();
  ConstructorNud();
  fTrigger.insert(std::make_pair("Psd",0));
  fTrigger.insert(std::make_pair("Stk",0));
  fTrigger.insert(std::make_pair("Bgo",0));
  fTrigger.insert(std::make_pair("Nud",0));
}

DmpRdcManager::~DmpRdcManager(){
  delete fEvtHeader;
}

Bool_t DmpRdcManager::SetConnector(TString subDet){
  Bool_t Ans = true;
  if (subDet == "Dampe") {
    Bool_t ans0 = SetConnectorPsd();
    Bool_t ans1 = SetConnectorStk();
    Bool_t ans2 = SetConnectorBgo();
    Bool_t ans3 = SetConnectorNud();
    Ans = (ans0 && ans1 && ans2 && ans3);
  } else if (subDet == "Psd") {
    Ans = SetConnectorPsd();
  } else if (subDet == "Stk") {
    Ans = SetConnectorStk();
  } else if (subDet == "Bgo") {
    Ans = SetConnectorBgo();
  } else if (subDet == "Nud") {
    Ans = SetConnectorNud();
  } else {
    Ans = false;
    std::cout<<"Error: DmpRdcManager::SetConnector(TString name):\tname = { Dampe | Psd | Stk | Bgo | Nud }"<<std::endl;
  }
  return Ans;
}

Bool_t DmpRdcManager::Conversion(ifstream *data,TString subDet){
  Bool_t Ans = true;
  if (subDet == "Dampe") {
    Bool_t ans0 = ConversionHeader(data);
    Bool_t ans1 = ConversionPsd(data);
    Bool_t ans2 = ConversionStk(data);
    Bool_t ans3 = ConversionBgo(data);
    Bool_t ans4 = ConversionNud(data);
    Ans = (ans0 && ans1 && ans2 && ans3 && ans4);
  } else if (subDet == "Header") {
    Ans = ConversionHeader(data);
  } else if (subDet == "Psd") {
    Ans = ConversionPsd(data);
  } else if (subDet == "Stk") {
    Ans = ConversionStk(data);
  } else if (subDet == "Bgo") {
    Ans = ConversionBgo(data);
  } else if (subDet == "Nud") {
    Ans = ConversionNud(data);
  } else {              // must match sub-detector order in Hex data
    Ans = false;
    std::cout<<"Error: DmpRdcManager::SetConnector(TString name):\tname = { Dampe | Psd | Stk | Bgo | Nud }"<<std::endl;
  }
  return Ans;
}

template <typename TDmpEvt>
TDmpEvt* DmpRdcManager::GetEventPointer(TString subDet){
  if (subDet == "Header") {
    return (TDmpEvt*)fEvtHeader;
  } else if (subDet == "Psd") {
    return (TDmpEvt*)fEvtPsd;
  } else if (subDet == "Stk") {
    return (TDmpEvt*)fEvtStk;
  } else if (subDet == "Bgo") {
    return (TDmpEvt*)fEvtBgo;
  } else if (subDet == "Nud") {
    return (TDmpEvt*)fEvtNud;
  }
  return 0;
}

void DmpRdcManager::FillAnEvent(){
  if (TriggerCheck() == true) {
    fEvtHeader->IsValidEvent();
  } else {
    std::cout<<"\t\t----> Fill event failed:\ttrigger not match\n"<<std::endl;
    return;
  }
  fTree->Fill();
#ifdef Dmp_DEBUG
  //std::cout<<"Fill event "<<dec<<fHeader->GetEventPointer()->GetEventID()<<std::endl<<std::endl;
#endif
}

void DmpRdcManager::SaveRootFile(){
  fDataName.ReplaceAll(".dat","-rec0.root");
  fOutRootFile = new TFile(fOutDataPath+fDataName,"RECREATE");
  fTree->Write();
  ResetRootFile();
  fEvtHeader->Reset();      // reset event ID, waiting next input data file
}

Bool_t DmpRdcManager::TriggerCheck() {
  if (fTrigger["Bgo"] != fTrigger["Psd"] || fTrigger["Bgo"] != fTrigger["Stk"] || fTrigger["Bgo"] != fTrigger["Nud"]) return true;
  return true;
}


