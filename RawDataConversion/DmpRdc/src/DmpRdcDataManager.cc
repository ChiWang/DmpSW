/*
 *  $Id: DmpRdcDataManager.cc, 2014-03-09 20:46:56 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef DmpDebug
#include <iostream>
#endif

#include "TTree.h"

#include "DmpEventRaw.h"
#include "DmpRdcDataManager.h"

DmpRdcDataManager* DmpRdcDataManager::sInstance = 0;

//-------------------------------------------------------------------
DmpRdcDataManager* DmpRdcDataManager::GetInstance(){
  if (sInstance == 0 ){
    sInstance = new DmpRdcDataManager();
  }
  return sInstance;
}

//-------------------------------------------------------------------
void DmpRdcDataManager::Vanish(){
  if (sInstance != 0 ){
    delete sInstance;
    sInstance = 0;
  }
}

//-------------------------------------------------------------------
void DmpRdcDataManager::BookBranch(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
}

//-------------------------------------------------------------------
void DmpRdcDataManager::CreateOutDataName(std::string name){
  if(fOutDataName == "default"){
    fOutDataName.replace(name.end()-4,fOutDataName.end(),"_raw.root");
  }
}

//-------------------------------------------------------------------
DmpRdcDataManager::DmpRdcDataManager()
 :fEvtRaw(0)
{
  fOutDataTree->SetNameTitle("DAMPE_Raw","ADC");
  fEvtRaw = new DmpEventRaw();
}

//-------------------------------------------------------------------
DmpRdcDataManager::~DmpRdcDataManager(){
  delete fEvtRaw;
}


