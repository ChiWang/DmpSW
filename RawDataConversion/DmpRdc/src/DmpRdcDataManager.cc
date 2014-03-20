/*
 *  $Id: DmpRdcDataManager.cc, 2014-03-09 20:46:56 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include "TTree.h"

#include "DmpEventRaw.h"
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
  fOutDataTree = new TTree("DAMPE_Raw","ADC");
#endif
  fOutDataTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
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


