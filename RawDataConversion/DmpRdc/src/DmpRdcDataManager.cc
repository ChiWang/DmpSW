/*
 *  $Id: DmpRdcDataManager.cc, 2014-03-09 01:57:56 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "TTree.h"

#include "DmpEvtHeader.h"
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

#include <stdlib.h>     // getenv()
//-------------------------------------------------------------------
DmpRdcDataManager::DmpRdcDataManager()
 :fConnectorPath("./"),
  fInDataName("no"),
  fInputData(0),
  fEvtRaw(0)
{
  std::cout<<"DAMPE software: Setup kernel of Raw Data Conversion"<<std::endl;
  fOutDataTree->SetName("DAMPE_Raw");
  fConnectorPath=(std::string)getenv("DMPSWSYS")+"/share/Connector/";
  if(gPhase == DmpCore::Phase::kQuarter){
    fConnectorPath = fConnectorPath + "Quarter/";
    fOutDataTree->SetTitle("ADC_Quarter");
  }else if(gPhase == DmpCore::Phase::kPrototype){
    fOutDataTree->SetTitle("ADC_Prototype");
  }else{
    fOutDataTree->SetTitle("ADC");
  }
  fEvtRaw = new DmpEventRaw();
// *
// *  TODO: create fTrigger right?
// *
  fTrigger.resize(DmpParameter::Detector::kSubDetNo + 1);
  for(short i = 0;i<fTrigger.size();++i) fTrigger[i] = 0;
}

//-------------------------------------------------------------------
DmpRdcDataManager::~DmpRdcDataManager(){
  if(fInputData != 0){
    delete fInputData;
    fInputData = 0;
  }
  delete fEvtRaw;
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::OpenInputData(std::string dataName){
  fInDataName = dataName;
  fInputData = new ifstream(fInDataPath+fInDataName,std::ios::in|std::ios::binary);
  if (!fInputData->good()) {
    std::cerr<<"\nwarning: open "<<fInDataPath+fInDataName<<" failed"<<std::endl;
// *
// *  TODO: does it right to delete fInputData at here
// *
    fInputData->close();  delete fInputData;
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
void DmpRdcDataManager::Convert(){
  for (long nEvt=0;!fInputData->eof();){
    if(ConvertEventHeader()){
      ++nEvt;
      fEvtRaw->GetEventHeader()->SetEventID(nEvt);
    }else{
      continue;
    }
#ifdef DmpDebug
if (nEvt > 5000) break;
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<" only Convert 5000 Event to test RDC"<<std::endl;
#endif
    if(not ConvertPsdEvent())   continue;
    if(not ConvertStkEvent())   continue;
    if(not ConvertBgoEvent())   continue;
    if(not ConvertNudEvent())   continue;

    if(not TriggerMatch()) continue;

#ifdef DmpDebug
if (nEvt%1000==0)   std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif

    FillEvent();
  }

  fInputData->close();  delete fInputData;
  for(short i=0;i<fTrigger.size();++i)  fTrigger[i]=0;
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::TriggerMatch() {
  for(short i=1;i<fTrigger.size();++i){
    if(fTrigger[0] != fTrigger[i]){
      std::cerr<<"warning:\ttriggers are not match:";
      for(i=0;i<fTrigger.size();++i){
        std::cerr<<"  "<<fTrigger[i]<<std::endl;
      }
      return false;
    }
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpRdcDataManager::ConvertEventHeader(){
// *
// *  TODO: 
// *
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::dec<<fInputData->tellg();
#endif
  static short tmp=0;
  fInputData->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  fInputData->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  fInputData->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  fInputData->read((char*)(&tmp),1);
  if (tmp!=0x13) {
    std::cout<<"\t\t\t\t----> Searching 0xe225 0813"<<std::endl;
    return false;
  } else {
    fHeader->CountPackage();
  }
  fInputData->read((char*)(&tmp),1);      //this needed
  fInputData->read((char*)(&fTrigger["Header"]),1);
  fInputData->read((char*)(&tmp),1);      //Datalength
  fInputData->read((char*)(&tmp),1);      //Datalength

  static short time[8], i;            // 8 bytes for time
  for (i=0;i<8;++i) {
    time[i]=0;
    fInputData->read((char*)(&time[i]),1);
  }

  fHeader->SetTime(time,8);
#ifdef DmpDebug
std::cerr<<"\tto "<<std::dec<<fInputData->tellg()<<std::endl;
//std::cout<<"\t\ttrigger = "<<fTrigger["Header"]<<"\tPackage ID = "<<fHeader->GetPackageID()<<std::endl;
#endif

  return true;
}

