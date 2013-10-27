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
//#include "TH1F.h"

#include "DmpCalL0Manager.hh"

#include "DmpEvtHeader.hh"
#include "DmpEvtPsd.hh"
#include "DmpEvtStk.hh"
#include "DmpEvtBgo.hh"
#include "DmpEvtNud.hh"

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
  fEvtHeader= new DmpEvtHeaderRaw();    // must before sub-detector. it will be used in ConstructorSubDet()
  ConstructorPsd();
  ConstructorStk();
  ConstructorBgo();
  ConstructorNud();
}

DmpCalL0Manager::~DmpCalL0Manager(){
  delete fEvtHeader;
  DestructorPsd();
  DestructorStk();
  DestructorBgo();
  DestructorNud();
}

void DmpCalL0Manager::FindPedetsalEevent(TString subDet){
  if (subDet == "Psd") {
  } else if (subDet == "Stk") {
  } else if (subDet == "Bgo") {
    FindPedetsalEeventBgo();
  } else if (subDet == "Nud") {
  } else {
    std::cout<<"Error: In DmpCalL0Manager::FindPedetsalEevent(TString subDet). subDet = {Psd | Stk | Bgo | Nud}"<<std::endl;
  }
}

