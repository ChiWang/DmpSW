/*
 *  $Id: DmpCore.cc, 2014-05-15 21:34:41 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/04/2014
*/

#include <time.h>

#include "DmpCore.h"

//-------------------------------------------------------------------
DmpCore::DmpCore()
 :fAlgMgr(0),
  fSvcMgr(0),
  fLogLevel(6),
  fMaxEventNo(-1),
  fStartTime(0),
  fStopTime(0)
{
  fAlgMgr = DmpAlgorithmManager::GetInstance();
  fSvcMgr = DmpServiceManager::GetInstance();
  SetTimeWindow("stop",2113,1,1,0,0,0);
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
void DmpCore::SetTimeWindow(const std::string &type,const short &year,const short &month,const short &day,const short &hour,const short &minute,const short &second){
  struct tm launchT;    // 20130101 000000
  launchT.tm_year = 113;    // since 1900
  launchT.tm_mon = 0;       // 0 ~ 11
  launchT.tm_mday = 1;      // 1 ~ 31
  launchT.tm_hour = 0;      // 0 ~ 23
  launchT.tm_min = 0;       // 0 ~ 59
  launchT.tm_sec = 0;       // 0 ~ 60
  if(type == "start"){
    struct tm startT;
    startT.tm_year = year-1900; startT.tm_mon = month-1;    startT.tm_mday = day;
    startT.tm_hour = hour;      startT.tm_min = minute;     startT.tm_sec = second;
    fStartTime = difftime(mktime(&startT),mktime(&launchT));
  }else if(type == "stop"){
    struct tm stopT;
    stopT.tm_year = year-1900;  stopT.tm_mon = month-1; stopT.tm_mday = day;
    stopT.tm_hour = hour;       stopT.tm_min = minute;  stopT.tm_sec = second;
    fStopTime = difftime(mktime(&stopT),mktime(&launchT));
  }
}

//-------------------------------------------------------------------
bool DmpCore::EventInTimeWindow(const long &t) const{
  if(fStartTime < t && t < fStopTime){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
bool DmpCore::PrintError() const{
  if((fLogLevel%8)/4 == 1){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
bool DmpCore::PrintWarning() const{
  if((fLogLevel%4)/2 == 1){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
bool DmpCore::PrintDebug() const{
  if(fLogLevel%2 == 1){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
DmpCore *gCore = DmpCore::GetInstance();


