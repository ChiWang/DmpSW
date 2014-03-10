/*
 *  $Id: DmpEntranceRdcDataManager.cc, 2014-03-09 23:46:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "DmpRdcAlgorithm.h"
#include "DmpRdcDataManager.h"
#include "DmpEntranceRdc.h"

using namespace DmpRdcAlg;

DmpRdcDataManager *dataMan = 0;
//-------------------------------------------------------------------
void DmpCore::RdcInitialize(){
  std::cout<<"DAMPE software: Setup kernel of Raw Data Conversion"<<std::endl;
  dataMan = DmpRdcDataManager::GetInstance();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetInDataPath(std::string p){
  dataMan->SetInDataPath(p);
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataPath(std::string p){
  dataMan->SetOutDataPath(p);
}

//-------------------------------------------------------------------
std::string DmpCore::RdcGetOutDataPath(){
  dataMan->GetOutDataPath();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataName(std::string n){
  dataMan->SetOutDataName();
}

//-------------------------------------------------------------------
void DmpCore::RdcExecute(std::string dataName){
  gInputData = new ifstream(dataMan->GetInDataPath()+dataName,std::ios::in|std::ios::binary);
  if (!gInputData->good()) {
    std::cerr<<"\nwarning: open "<<dataMan->GetInDataPath()+dataName<<" failed"<<std::endl;
    gInputData->close();
    delete gInputData;
    return;
  }

  dataMan->BookBranch();
  dataMan->CreateOutDataName(dataName);
  for (long nEvt=0;!inData->eof();){
    if(ConvertEventHeader()){
      ++nEvt;
      dataMan->GetEventHeader()->SetEventID(nEvt);
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
    if(not Psd::ConvertEvent())   continue;
    if(not Stk::ConvertEvent())   continue;
    if(not Bgo::ConvertEvent())   continue;
    if(not Nud::ConvertEvent())   continue;
    if((gTrigger != Psd::trigger) || (gTrigger != Stk::trigger) || (gTrigger != Bgo::trigger) || gTrigger != Nug::trigger) continue;

    dataMan->FillEvent();
  }
  dataMan->SaveOutput();

  gInputData->close();
  delete gInputData;
  for(short i=0;i<fTrigger.size();++i)  fTrigger[i]=0;
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
  DmpRdcDataManager::Vanish();
}


