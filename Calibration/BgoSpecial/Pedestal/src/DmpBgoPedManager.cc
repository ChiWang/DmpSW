/*=====================================================================
 *   File:   DmpBgoPedManager.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    26/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  26/12/2013   16:29:15
=====================================================================*/

#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "RooRealVar.h"
//#include "TH1F.h"

#include "DmpBgoPedManager.hh"
#include "DmpEvtHeader.hh"
#include "DmpEvtBgoRaw.hh"
#include "DmpParameterBgo.hh"

//------------------------------------------------------------------------------
DmpBgoPedManager*  DmpBgoPedManager::fInstance=0;

//------------------------------------------------------------------------------
DmpBgoPedManager*  DmpBgoPedManager::GetInstance(){
  if (fInstance == 0) {
    fInstance = new DmpBgoPedManager();
  }
  return fInstance;
}

//------------------------------------------------------------------------------
void DmpBgoPedManager::Clear(){
  if (fInstance != 0) {
    delete fInstance;
    fInstance = 0;
  }
  std::cout<<"\n\tdelete DmpPed Manager"<<std::endl;
}

//------------------------------------------------------------------------------
Bool_t DmpBgoPedManager::Core(){
  TFile *aFile = new TFile(fInDataPath+fDataName);

}

//------------------------------------------------------------------------------
DmpBgoPedManager::DmpBgoPedManager()
 :fTree(0)
{
  fEvt = new DmpEvtBgoRaw();
  fRecord = new DmpRecordBgoPed();
  fDy2ADC = new RooRealVar("dy2","dy2",0,800);
  fDy5ADC = new RooRealVar("dy5","dy5",0,800);
  fDy8ADC = new RooRealVar("dy8","dy8",0,800);
  SetupPMTCollection();
}

//------------------------------------------------------------------------------
DmpBgoPedManager::~DmpBgoPedManager(){
  delete fEvt;
  delete fRecord;
  delete fDy2ADC;
  delete fDy5ADC;
  delete fDy8ADC;
}


