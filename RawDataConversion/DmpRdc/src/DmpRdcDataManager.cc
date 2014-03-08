/*
 *  $Id: DmpRdcDataManager.cc, 2014-03-08 20:49:05 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>
#ifndef DmpDebug
#include <stdlib.h>
#endif

#include "TTree.h"

//#include "DmpEvtHeader.h"
//#include "DmpEvtPsdHit.h"
//#include "DmpEvtStkHit.h"
//#include "DmpEvtBgoHit.h"
//#include "DmpEvtNudHit.h"
#include "DmpEventRaw.h"
#include "DmpRdcDataManager.h"
#include "DmpParameterSubDetector.h"
#include "DmpParameterPhase.h"
using namespace DmpParameter;

DmpRdcDataManager* DmpRdcDataManager::sInstance = 0;
//std::string DmpRdcDataManager::fConnectorPath=(std::string)getenv("DMPSWSYS")+"/share/Connector/";

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
DmpRdcDataManager::DmpRdcDataManager()
 :fHexData(0)
{
  fEvtRaw = new DmpEventRaw();
  std::cout<<"DAMPE software: Setup kernel of Raw Data Conversion"<<std::endl;
// *
// *  TODO: set path correspond to phase
// *
  /*
  if (DmpPhase::gPhase == DmpPhase::kBT2012){
     fConnectorPath += "BT2012/";
  }else if(DmpPhase::gPhase == DmpPhase::kCT2013){
     fConnectorPath += "CT2013/";
  }
  */
  fOutDataTree->SetNameTitle("DAMPE_Raw","ADC");
  fTrigger.resize(DmpDetector::kSubDetNo + 1);
  for(short i = 0;i<fTrigger.size();++i) fTrigger[i] = 0;
}

//-------------------------------------------------------------------
DmpRdcDataManager::~DmpRdcDataManager(){
  if(fHexData != 0){
    delete fHexData;
    fHexData = 0;
  }
  delete fEvtRaw;
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::OpenInputData(std::string dataName){
  fInDataName = dataName;
  fHexData = new ifstream(fInDataPath+fInDataName,std::ios::in|std::ios::binary);
  if (!fHexData->good()) {
    std::cerr<<"\nwarning: open "<<fInDataPath+fInDataName<<" failed"<<std::endl;
// *
// *  TODO: does it right to delete fHexData
// *
    fHexData->close();  delete fHexData;    fHexData = 0;
    return false;
  }
#ifdef DmpDebug
  std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"\nReading "<<fInDataPath+fInDataName<<std::endl;
#endif
  return true;
}

//-------------------------------------------------------------------
void DmpRdcDataManager::BookBranch(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fOutDataTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
}

//-------------------------------------------------------------------
void DmpRdcDataManager::CreateOutDataName(){
  if(fOutDataName == "default"){
    fOutDataName.replace(fInDataName.end()-4,fOutDataName.end(),"_raw.root");
  }
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::Execute(){
// *
// *  TODO: not finish
// *
  for (long nEvt=0;!fHexData->eof();++nEvt){
//if (nEvt > 5) break;
    if ( !ConversionHeader() ) continue;
    if ( !ConversionPsd() ) continue;
    if ( !ConversionStk() ) continue;
    if ( !ConversionBgo() ) continue;
    if ( !ConversionNud() ) continue;

#ifdef DmpDebug
//if (nEvt == 0) fHeader->ShowTime(0);
#endif

    if (TriggerMatch()) {
      fHeader->CountEvent();
      FillEvent();
#ifdef DmpDebug
if (nEvt%1000==0) std::cout<<"\tFill event "<<std::dec<<fHeader->GetEventID()<<std::endl;
#endif
    } else {
      continue;
    }
  }

  fHeader->Reset();      // reset event ID, waiting next input data file
  fHexData->close();
  delete fHexData;
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::TriggerMatch() {
// *
// *  TODO: trigger
// *
  if (fTrigger["Bgo"] == fTrigger["Psd"] && fTrigger["Bgo"] == fTrigger["Stk"] && fTrigger["Bgo"] == fTrigger["Nud"] && fTrigger["Bgo"] == fTrigger["Header"]) {
  return true;
  } else {
    std::cerr<<"Error: Triggers of Sub-detectors not match\n";
    std::cerr<<std::hex<<"\tHeader = "<<fTrigger["Header"]<<"\tPsd = "<<fTrigger["Psd"]<<"\tStk = "<<fTrigger["Stk"]<<"\tBgo = "<<fTrigger["Bgo"]<<"\tNud = "<<fTrigger["Nud"]<<std::endl;
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::ConversionHeader(){
#ifdef DmpDebug
std::cerr<<"\n\tBegin Conversion:\n\t\t-->Header from "<<std::dec<<fHexData->tellg();
#endif
  static short tmp=0;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0x13) {
    std::cout<<"\t\t\t\t----> Searching 0xe225 0813"<<std::endl;
    return false;
  } else {
    fHeader->CountPackage();
  }
  fHexData->read((char*)(&tmp),1);      //this needed
  fHexData->read((char*)(&fTrigger["Header"]),1);
  fHexData->read((char*)(&tmp),1);      //Datalength
  fHexData->read((char*)(&tmp),1);      //Datalength

  static short time[8], i;            // 8 bytes for time
  for (i=0;i<8;++i) {
    time[i]=0;
    fHexData->read((char*)(&time[i]),1);
  }

  fHeader->SetTime(time,8);
#ifdef DmpDebug
std::cerr<<"\tto "<<std::dec<<fHexData->tellg()<<std::endl;
//std::cout<<"\t\ttrigger = "<<fTrigger["Header"]<<"\tPackage ID = "<<fHeader->GetPackageID()<<std::endl;
#endif

  return true;
}

