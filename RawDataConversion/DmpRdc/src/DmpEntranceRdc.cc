/*
 *  $Id: DmpEntranceRdc.cc, 2014-03-11 16:55:59 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>
#include <stdlib.h>     // getenv() chdir()

#include "DmpCore.h"
#include "DmpEntranceRdc.h"
#include "DmpRdcAlgorithm.h"
#include "DmpRdcDataManager.h"

using namespace DmpRdcAlg;

bool DmpCore::RdcSetConnector(DmpEDetectorID id,std::string p){
  short st[DmpParameter::Detector::kSubDetNo]={0};
  if(p=="default"){
    p = (std::strin)getenv("DMPSWSYS") + "/share/Connector/";
  }else if(p[p.length()-1] != '/'){
    p=p+'/';
  }
  if(id = DmpParameter::Detector::kWhole){
    if(not st[DmpEDetectorID::kPsd]){
      if(not Psd::SetConnector(p+"Psd/"))  return false;
    }
    if(not st[DmpEDetectorID::kStk]){
      if(not Stk::SetConnector(p+"Stk/"))  return false;
    }
    if(not st[DmpEDetectorID::kBgo]){
      if(not Bgo::SetConnector(p+"Bgo/"))  return false;
    }
    if(not st[DmpEDetectorID::kNud]){
      if(not Nud::SetConnector(p+"Nud/"))  return false;
    }
  }else if(id = DmpParameter::Detector::kPsd){
    if(Psd::SetConnector(p)) st[DmpEDetectorID::kPsd]=1;
    else return false;
  }else if(id = DmpParameter::Detector::kStk){
    if(Stk::SetConnector(p)) st[DmpEDetectorID::kStk]=1;
    else return false;
  }else if(id = DmpParameter::Detector::kBgo){
    if(Bgo::SetConnector(p)) st[DmpEDetectorID::kBgo]=1;
    else return false;
  }else if(id = DmpParameter::Detector::kNud){
    if(Nud::SetConnector(p)) st[DmpEDetectorID::kNud]=1;
    else return false;
  }
  return true;
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataPath(std::string p){
  DmpRdcDataManager::GetInstance()->SetOutDataPath(p);
}

//-------------------------------------------------------------------
std::string DmpCore::RdcGetOutDataPath(){
  DmpRdcDataManager::GetInstance()->GetOutDataPath();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataName(std::string n){
  DmpRdcDataManager::GetInstance()->SetOutDataName();
}

//-------------------------------------------------------------------
bool DmpCore::RdcInitialize(){
  std::cout<<"DAMPE software: Setup kernel of Raw Data Conversion"<<std::endl;
}

//-------------------------------------------------------------------
void DmpCore::RdcExecute(std::string dataName){
  DmpRdcDataManager *dataMan = DmpRdcDataManager::GetInstance();
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


