/*
 *  $Id: DmpCore.cc, 2014-05-04 15:14:58 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/04/2014
*/

#include "DmpCore.h"

//-------------------------------------------------------------------
DmpCore::DmpCore()
 :fAlgMgr(0),
  fSvcMgr(0),
  fLogLevel(6),
  fMaxEventNo(-1),
  fStartYMD(20130101),
  fStopYMD(30130101),
  fStartHMS(0),
  fStopHMS(0)
{
  fAlgMgr = DmpAlgorithmManager::GetInstance();
  fSvcMgr = DmpServiceManager::GetInstance();
}

//-------------------------------------------------------------------
DmpCore::~DmpCore(){
}

//-------------------------------------------------------------------
bool DmpCore::Initialize(){
  if(not fSvcMgr->Initialize()){
    return false;
  }
  if(not fAlgMgr->Initialize()){
    return false;
  }
}

//-------------------------------------------------------------------
bool DmpCore::Run(){
// *
// *  TODO:  how to
// *

}

//-------------------------------------------------------------------
bool DmpCore::Finalize(){
  if(not fSvcMgr->Finalize()){
    return false;
  }
  if(not fAlgMgr->Finalize()){
    return false;
  }
}

//-------------------------------------------------------------------
void DmpCore::SetTimeWindow(const std::string &type,const int &YMD,const int &HMS){
  if(type == "start"){
    fStartYMD = YMD;
    fStartHMS = HMS;
  }else if(type == "stop"){
    fStopYMD = YMD;
    fStopHMS = HMS;
  }
}

//-------------------------------------------------------------------
bool DmpCore::PrintError() const {
  if((fLogLevel%8)/4 == 1){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
bool DmpCore::PrintWarning() const {
  if((fLogLevel%4)/2 == 1){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
bool DmpCore::PrintDebug() const {
  if(fLogLevel%2 == 1){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
DmpCore *gCore = DmpCore::GetInstance();


