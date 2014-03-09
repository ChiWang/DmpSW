/*
 *  $Id: DmpRdcAlgorithm.cc, 2014-03-09 21:36:27 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#include <iostream>

#include "DmpEvtHeader.h"
#include "DmpRdcAlgorithm.h"
#include "DmpRdcDataManager.h"

DmpRdcAlgorithm* DmpRdcAlgorithm::sInstance = 0;

//-------------------------------------------------------------------
DmpRdcAlgorithm* DmpRdcAlgorithm::GetInstance(){
  if(sInstance == 0){
    sInstance = new DmpRdcAlgorithm();
  }
  return sInstance;
}

//-------------------------------------------------------------------
void DmpRdcAlgorithm::Vanish(){
  if(sInstance != 0){
    delete sInstance;
    sInstance = 0;
  }
}

//-------------------------------------------------------------------
#include <stdlib.h>     // getenv()
DmpRdcAlgorithm::DmpRdcAlgorithm()
 :fConnectorPath("./"),
  fInputData(0)
{
  fConnectorPath=(std::string)getenv("DMPSWSYS")+"/share/Connector/";
  if(DmpRdcDataManager::GetPhase() == DmpCore::Phase::kQuarter){
    fConnectorPath = fConnectorPath + "Quarter/";
  }else if(DmpRdcDataManager::GetPhase() == DmpCore::Phase::kPrototype){
    fConnectorPath = fConnectorPath + "Prototype/";
  }else{
    fConnectorPath = fConnectorPath + "Product/";
  }
// *
// *  TODO: create fTrigger right?
// *
  fTrigger.resize(DmpParameter::Detector::kSubDetNo + 1);
  for(short i = 0;i<fTrigger.size();++i) fTrigger[i] = 0;
}

//-------------------------------------------------------------------
DmpRdcAlgorithm::~DmpRdcAlgorithm(){
}

//-------------------------------------------------------------------
bool DmpRdcAlgorithm::ConvertEventHeader(){
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

//-------------------------------------------------------------------
bool DmpRdcAlgorithm::TriggerMatch() {
  for(short i=1;i<fTrigger.size();++i){
    if(fTrigger[0] != fTrigger[i]){
      std::cerr<<"Error:\ttriggers: ";
      for(i=0;i<fTrigger.size();++i){
        std::cerr<<"  "<<fTrigger[i]<<std::endl;
      }
      return false;
    }
  }
  return true;
}


