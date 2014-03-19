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


DmpRdcDataManager* DmpRdcDataManager::GetInstance(){
  static DmpRdcDataManager instance;
  return &instance;
}

//-------------------------------------------------------------------
void DmpRdcDataManager::BookBranch(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
void DmpRdcDataManager::SetOutDataName(std::string name){
  boost::filesystem::path inpath(name);
  if(fNameTag != "no"){
    fOutDataName = "DmpRaw_"+fNameTag+"_"+inpath.stem()+"_"+TimeStamp()+".root";
  }else{
    fOutDataName = "DmpRaw_"+inpath.stem()+"_"+TimeStamp()+".root";
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


