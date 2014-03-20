/*
 *  $Id: DmpRdcDataManager.cc, 2014-03-09 20:46:56 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef DmpDebug
#include <iostream>
#endif

#include "TTree.h"
#include "TFile.h"

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
  fOutDataTree = new TTree("DAMPE_Raw","ADC");
#endif
  fOutDataTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
}

//-------------------------------------------------------------------
void DmpRdcDataManager::FillEvent(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree->Fill();
}

//-------------------------------------------------------------------
#include <boost/filesystem/path.hpp>
#include <boost/lexical_cast.hpp>
void DmpRdcDataManager::SetOutDataName(){
  static int runID = -1;
  boost::filesystem::path inpath(fInDataName);
  if(fNote != "no"){
    fOutDataName = "DmpRaw_"+TimeStamp()+"_run"+boost::lexical_cast<std::string>(runID)+"_"+inpath.stem()+"_"+fNote+".root";
  }else{
    fOutDataName = "DmpRaw_"+TimeStamp()+"_run"+boost::lexical_cast<std::string>(runID)+"_"+inpath.stem()+".root";
  }
}

//-------------------------------------------------------------------
void DmpRdcDataManager::SaveOutput(){ 
  TFile *aFile = new TFile((TString)(fOutDataPath+fOutDataName),"recreate");
  fOutDataTree->Write();
  aFile->Close();
  delete fOutDataTree;
  delete aFile;
  std::cout<<"Result in : "<<fOutDataPath+fOutDataName<<std::endl;
  fInDataName = "no";
  fOutDataName = "no";
  fNote = "no";
}

//-------------------------------------------------------------------
DmpRdcDataManager::DmpRdcDataManager()
 :fEvtRaw(0)
{
  fEvtRaw = new DmpEventRaw();
}

//-------------------------------------------------------------------
DmpRdcDataManager::~DmpRdcDataManager(){
  delete fEvtRaw;
}


