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
DmpRdcDataManager* DmpRdcDataManager::GetInstance(){
  static DmpRdcDataManager instance;
  return &instance;
}

//-------------------------------------------------------------------
#ifdef DmpDebug
#include <iostream>
#endif
void DmpRdcDataManager::BookBranch(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fEvtRaw->GetEventHeader()->ResetEventID();
  fOutDataTree = new TTree("DAMPE_Raw","ADC");
  fOutDataTree->Branch("Event","DmpEventRaw",&fEvtRaw,32000,2);
}

//-------------------------------------------------------------------
void DmpRdcDataManager::Reset(){
  fEvtRaw->Reset();
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::TriggerMatch(const short &level){
  static short trigger = 0;
  trigger = fEvtRaw->GetEventHeader()->GetTrigger(DmpDetector::kBgo);
  for(short i=0;i<level;++i){
    if(trigger != fEvtRaw->GetEventHeader()->GetTrigger((DmpDetector::DmpEDetectorID)i)){
      std::cout<<"Error: Event triggers not match ("<<level<<" sub detectors) ";
      fEvtRaw->GetEventHeader()->PrintTime();
      return false;
    }
  }
  return true;
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


