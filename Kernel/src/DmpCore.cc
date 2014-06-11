/*
 *  $Id: DmpCore.cc, 2014-05-15 21:34:41 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/04/2014
*/

#include <time.h>

#include "DmpCore.h"
#include "DmpIOSvc.h"

//-------------------------------------------------------------------
DmpCore::DmpCore()
 :fAlgMgr(0),
  fSvcMgr(0),
  fMaxEventNo(-1),
  fStartTime(0),
  fStopTime(0),
  fInitializeDone(false)
{
  fAlgMgr = DmpAlgorithmManager::GetInstance();
  fSvcMgr = DmpServiceManager::GetInstance();
  fSvcMgr->Append(DmpIOSvc::GetInstance());
  SetTimeWindow("stop",21130101,0);
}

//-------------------------------------------------------------------
DmpCore::~DmpCore(){
}

//-------------------------------------------------------------------
bool DmpCore::Initialize(){
  //*
  //* Important! First, initialize servises, then algorithms
  //*
  if(not fSvcMgr->Initialize()) return false;
  if(not fAlgMgr->Initialize()) return false;
  if(-1 == fMaxEventNo){
    fMaxEventNo = 1234567890;
  }
  fInitializeDone = true;
  return true;
}

//-------------------------------------------------------------------
bool DmpCore::Run(){
  if(not fInitializeDone) return false;
// *
// *  TODO: use cut of time range??
// *
  for(long i=0;i<fMaxEventNo;++i){
    DmpLogDebug<<"event ID = "<<i<<DmpLogEndl;
    if(fAlgMgr->ProcessOneEvent()){
      DmpIOSvc::GetInstance()->FillEvent();
    }else{
      return false;
    }
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpCore::Finalize(){
  //*
  //* Important! First, finalize algorithms, then services!
  //*
  fAlgMgr->Finalize();
  fSvcMgr->Finalize();
  return true;
}

//-------------------------------------------------------------------
void DmpCore::SetLogLevel(const std::string &l,const short &s)const{
  if(1 == s){
    DmpLog::SetLogLevel(l,true);
  }else{
    DmpLog::SetLogLevel(l,false);
  }
}

//-------------------------------------------------------------------
void DmpCore::SetTimeWindow(const std::string &type,const int &YMD,const int &HMS){
  struct tm launchT;    // 20130101 000000
  launchT.tm_year = 113;    // since 1900
  launchT.tm_mon = 0;       // 0 ~ 11
  launchT.tm_mday = 1;      // 1 ~ 31
  launchT.tm_hour = 0;      // 0 ~ 23
  launchT.tm_min = 0;       // 0 ~ 59
  launchT.tm_sec = 0;       // 0 ~ 60
  if(type == "start"){
    struct tm startT;
    startT.tm_year = (YMD/10000)-1900;
    startT.tm_mon = (YMD%10000)/10-1;
    startT.tm_mday = YMD%10;
    startT.tm_hour = HMS/10000;
    startT.tm_min = (HMS%10000)/10;
    startT.tm_sec = HMS%10;
    fStartTime = difftime(mktime(&startT),mktime(&launchT));
  }else if(type == "stop"){
    struct tm stopT;
    stopT.tm_year = (YMD/10000)-1900;
    stopT.tm_mon = (YMD%10000)/10-1;
    stopT.tm_mday = YMD%10;
    stopT.tm_hour = HMS/10000;
    stopT.tm_min = (HMS%10000)/10;
    stopT.tm_sec = HMS%10;
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
DmpCore *gCore = DmpCore::GetInstance();


