/*
 *  $Id: DmpRdcSvcDataMgr.cc, 2014-04-30 09:09:23 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "TTree.h"
#include "TClonesArray.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcMSD.h"
#include "DmpRdcSvcDataMgr.h"

//-------------------------------------------------------------------
DmpRdcSvcDataMgr::DmpRdcSvcDataMgr()
 :DmpVSvc("Rdc/DataMgr"),
  fEvtHeader(0),
  fPsdOutSet(0),
  fStkOutSet(0),
  fBgoOutSet(0),
  fNudOutSet(0)
{
  SetPackageID("Rdc_V1.0_");
  fEvtHeader = new DmpEvtRdcHeader();
  fPsdOutSet = new TClonesArray("DmpEvtRdcMSD",300);
  fStkOutSet = new TClonesArray("DmpEvtRdcMSD",300);
  fBgoOutSet = new TClonesArray("DmpEvtRdcMSD",300);
  fNudOutSet = new TClonesArray("DmpEvtRdcMSD",300);
}

//-------------------------------------------------------------------
DmpRdcSvcDataMgr::~DmpRdcSvcDataMgr(){
  delete fEvtHeader;
  fPsdOutSet->Delete(); fPsdOutSet->Clear(); delete fPsdOutSet;
  fStkOutSet->Delete(); fStkOutSet->Clear(); delete fStkOutSet;
  fBgoOutSet->Delete(); fBgoOutSet->Clear(); delete fBgoOutSet;
  fNudOutSet->Delete(); fNudOutSet->Clear(); delete fNudOutSet;
}

//-------------------------------------------------------------------
void DmpRdcSvcDataMgr::Set(const std::string &type, const std::string &argv){
  if(type == "OutDataPath"){
    SetOutDataPath(argv);
  }else if(type == "OutDataNote"){
    AppendDataNote(argv);
  }else if(type == "InData"){
    SetInputData(argv);
  }
}

//-------------------------------------------------------------------
void DmpRdcSvcDataMgr::BookBranch(){
#ifdef DmpDebug
std::cout<<"\n\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree = new TTree("DAMPE_Raw","ADC");
  fOutDataTree->Branch("EventHeader","DmpEvtRdcHeader",&fEvtHeader,32000,2);
  fOutDataTree->Branch("Psd",fPsdOutSet,32000,2);
  fOutDataTree->Branch("Stk",fStkOutSet,32000,2);
  fOutDataTree->Branch("Bgo",fBgoOutSet,32000,2);
  fOutDataTree->Branch("Nud",fNudOutSet,32000,2);
}

//-------------------------------------------------------------------
void DmpRdcSvcDataMgr::FillEvent(){
  fEvtHeader->GenerateStatus();
  DmpVDataMgr::FillEvent();
  ResetEvent();
}

//-------------------------------------------------------------------
bool DmpRdcSvcDataMgr::OpenInputData(){
  if(fInDataStream.is_open()){
    fInDataStream.close();
  }
  //std::string dataName = InputData();
  //std::cout<<InputData()<<std::endl;
  fInDataStream.open(InputData().c_str(),std::ios::in|std::ios::binary);
  if(not fInDataStream.good()){
    std::cerr<<"\nwarning: open "<<InputData()<<" failed"<<std::endl;
    fInDataStream.close();
    return false;
  }
  return true;
}

//-------------------------------------------------------------------
void DmpRdcSvcDataMgr::ResetEvent(){
  fEvtHeader->Reset();
  fPsdOutSet->Delete(); fPsdOutSet->Clear();
  fStkOutSet->Delete(); fStkOutSet->Clear();
  fBgoOutSet->Delete(); fBgoOutSet->Clear();
  fNudOutSet->Delete(); fNudOutSet->Clear();
}

//-------------------------------------------------------------------
TClonesArray* DmpRdcSvcDataMgr::GetOutCollection(DmpDetector::DmpEDetectorID id) const{
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


