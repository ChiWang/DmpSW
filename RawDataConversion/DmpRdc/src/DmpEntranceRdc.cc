/*
 *  $Id: DmpEntranceRdc.cc, 2014-03-09 21:37:37 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "DmpRdcAlgorithm.h"
#include "DmpRdcDataManager.h"
#include "DmpEntranceRdc.h"

DmpRdcAlgorithm     *algorithm = 0;
DmpRdcDataManager   *dataManager = 0;

//-------------------------------------------------------------------
bool DmpCore::RdcInitialize(){
  std::cout<<"DAMPE software: Setup kernel of Raw Data Conversion"<<std::endl;
  algorithm = DmpRdcAlgorithm::GetInstance();
  if (not algorithm->SetConnectorPsd()) return false;
  if (not algorithm->SetConnectorStk()) return false;
  if (not algorithm->SetConnectorBgo()) return false;
  if (not algorithm->SetConnectorNud()) return false;
  dataManager = DmpRdcDataManager::GetInstance();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetInDataPath(std::string p){
  dataManager->SetInDataPath(p);
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataPath(std::string p){
  dataManager->SetOutDataPath(p);
}

//-------------------------------------------------------------------
std::string DmpCore::RdcGetOutDataPath(){
  dataManager->GetOutDataPath();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataName(std::string n){
  dataManager->SetOutDataName();
}

//-------------------------------------------------------------------
void DmpCore::RdcExecute(std::string dataName){
  ifstream *indata = new ifstream(dataManager->GetInDataPath()+dataName,std::ios::in|std::ios::binary);
  if (!indata->good()) {
    std::cerr<<"\nwarning: open "<<dataManager->GetInDataPath()+dataName<<" failed"<<std::endl;
    indata->close();
    delete indata;
    return;
  }else{
    algorithm->SetInputData(indata);
    std::cout<<"\n open "<<dataManager->GetInDataPath()+dataName<<std::endl;
  }

  dataManager->BookBranch();
  dataManager->CreateOutDataName(dataName);
  for (long nEvt=0;!inData->eof();){
    if(algorithm->ConvertEventHeader()){
      ++nEvt;
      fEvtRaw->GetEventHeader()->SetEventID(nEvt);
    }else{
      continue;
    }
#ifdef DmpDebug
if (nEvt < 5000){
  std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"nEvt = "<<nEvt<<std::endl;
}else{
  break;
}
#endif
    if(not algorithm->ConvertEventPsd())   continue;
    if(not algorithm->ConvertEventStk())   continue;
    if(not algorithm->ConvertEventBgo())   continue;
    if(not algorithm->ConvertEventNud())   continue;
    if(not TriggerMatch()) continue;

    dataManager->FillEvent();
  }
  dataManager->SaveOutput();

  indata->close();
  delete indata;
  for(short i=0;i<fTrigger.size();++i)  fTrigger[i]=0;
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
  DmpRdcDataManager::Vanish();
  DmpRdcAlgorithm::Vanish();
}


