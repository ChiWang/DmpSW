/*
 *  $Id: DmpRdcDataManager.cc, 2014-03-09 20:46:56 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include "TTree.h"

#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"
#include "DmpRdcDataManager.h"


//-------------------------------------------------------------------
void DmpRdcDataManager::Initialize(){
  fEvtRaw->GetEventHeader()->Initialize();
}

//-------------------------------------------------------------------
#ifdef DmpDebug
#include <iostream>
#endif
void DmpRdcDataManager::BookBranch(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree = new TTree("DAMPE_Raw","ADC");
  fOutDataTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
}

//-------------------------------------------------------------------
void DmpRdcDataManager::FillEvent(){
  fEvtRaw->GetEventHeader()->GenerateTriggerStatus();
  fOutDataTree->Fill();
}

//-------------------------------------------------------------------
DmpRdcDataManager::DmpRdcDataManager()
 :fEvtRaw(0)
{
  fEvtRaw = new DmpEventRaw();
  fPgkID += "Rdc_V1.0_";
}

//-------------------------------------------------------------------
DmpRdcDataManager::~DmpRdcDataManager(){
  delete fEvtRaw;
}


