/*
 *  $Id: DmpRdcDataManager.cc, 2014-04-06 15:59:41 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "TTree.h"
#include "TClonesArray.h"

#include "DmpEvtHeader.h"
#include "DmpEvtPsdMSD.h"
#include "DmpEvtStkMSD.h"
#include "DmpEvtBgoMSD.h"
#include "DmpEvtNudMSD.h"
#include "DmpRdcDataManager.h"

//-------------------------------------------------------------------
DmpRdcDataManager::DmpRdcDataManager()
 :fEvtHeader(0),
  fPsdOutSet(0),
  fStkOutSet(0),
  fBgoOutSet(0),
  fNudOutSet(0)
{
  std::cout<<"Setting DmpRdcDataManager"<<std::endl;
  SetPackageID("Rdc_V1.0_");
  fEvtHeader = new DmpEvtHeader();
  fPsdOutSet = new TClonesArray("DmpEvtPsdMSD",300);
  fStkOutSet = new TClonesArray("DmpEvtStkMSD",300);
  fBgoOutSet = new TClonesArray("DmpEvtBgoMSD",300);
  fNudOutSet = new TClonesArray("DmpEvtNudMSD",300);
}

//-------------------------------------------------------------------
DmpRdcDataManager::~DmpRdcDataManager(){
  std::cout<<"Delete DmpRdcDataManager"<<std::endl;
  delete fEvtHeader;
  fPsdOutSet->Delete(); fPsdOutSet->Clear(); delete fPsdOutSet;
  fStkOutSet->Delete(); fStkOutSet->Clear(); delete fStkOutSet;
  fBgoOutSet->Delete(); fBgoOutSet->Clear(); delete fBgoOutSet;
  fNudOutSet->Delete(); fNudOutSet->Clear(); delete fNudOutSet;
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::InputData(const std::string &dataName){
  gInDataStream.open(dataName.c_str(),std::ios::in|std::ios::binary);
  DmpVIO::InputData(dataName);
  if(not gInDataStream.good()){
    std::cerr<<"\nwarning: open "<<dataName<<" failed"<<std::endl;
    gInDataStream.close();
    return false;
  }
  return true;
}

//-------------------------------------------------------------------
void DmpRdcDataManager::BookBranch(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fEvtHeader->Initialize();
  fOutDataTree = new TTree("DAMPE_Raw","ADC");
  fOutDataTree->Branch("EventHeader","DmpEvtHeader",&fEvtHeader,32000,2);
  fOutDataTree->Branch("Psd",fPsdOutSet,32000,2);
  fOutDataTree->Branch("Stk",fStkOutSet,32000,2);
  fOutDataTree->Branch("Bgo",fBgoOutSet,32000,2);
  fOutDataTree->Branch("Nud",fNudOutSet,32000,2);
}

//-------------------------------------------------------------------
void DmpRdcDataManager::FillEvent(){
  fEvtHeader->GenerateTriggerStatus();
  DmpVIO::FillEvent();
}

//-------------------------------------------------------------------
void DmpRdcDataManager::ResetEvent(){
  fPsdOutSet->Delete(); fPsdOutSet->Clear();
  fStkOutSet->Delete(); fStkOutSet->Clear();
  fBgoOutSet->Delete(); fBgoOutSet->Clear();
  fNudOutSet->Delete(); fNudOutSet->Clear();
}

//-------------------------------------------------------------------
TClonesArray* DmpRdcDataManager::GetOutCollection(DmpDetector::DmpEDetectorID id) const{
  switch(id){
    case DmpDetector::kPsd:
      return fPsdOutSet;
    case DmpDetector::kStk:
      return fStkOutSet;
    case DmpDetector::kBgo:
      return fBgoOutSet;
    case DmpDetector::kNud:
      return fNudOutSet;
  }
}

//-------------------------------------------------------------------
DmpRdcDataManager *gRdcDataMgr = DmpRdcDataManager::GetInstance();


