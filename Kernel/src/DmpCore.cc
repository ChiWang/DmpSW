/*
 *  $Id: DmpCore.cc, 2014-07-24 17:27:30 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/04/2014
*/

#include <time.h>

#include "DmpCore.h"
#include "DmpRootIOSvc.h"

//-------------------------------------------------------------------
DmpCore::DmpCore()
 :fAlgMgr(0),
  fSvcMgr(0),
  fLaunchTime("20130101-0000"),
  fMaxEventNo(-1),
  fStartTime(0),
  fStopTime(0),
  fInitializeDone(false),
  fTerminateRun(false),
  fCurrentEventID(0)    // must == 0
{
  std::cout<<"**************************************************"<<std::endl;
  std::cout<<"      Offline software of DAMPE (DMPSW)"<<std::endl;
  std::cout<<"      version:  1.0.2"<<std::endl;
  std::cout<<"**************************************************"<<std::endl;
  fAlgMgr = DmpAlgorithmManager::GetInstance();
  fSvcMgr = DmpServiceManager::GetInstance();
  fSvcMgr->Append(gRootIOSvc);
  OptMap.insert(std::make_pair("LogLevel",  0));    // value: None, Error, Warning, Info, Debug
  OptMap.insert(std::make_pair("EventNumber",1));   // value: any number
  OptMap.insert(std::make_pair("StartTime", 2));    // value: format 20131231-1430
  OptMap.insert(std::make_pair("StopTime",  3));    // value: format 20131231-1430
}

//-------------------------------------------------------------------
DmpCore::~DmpCore(){
}

//-------------------------------------------------------------------
bool DmpCore::Initialize(){
  //*
  //* Important! First, initialize servises, then algorithms
  //*
  std::cout<<"\n  [DmpCore::Initialize] Initialize..."<<std::endl;
  if(not fSvcMgr->Initialize()) return false;
  if(not fAlgMgr->Initialize()) return false;
  gRootIOSvc->PrepareMetaData();
  if(0 == fStopTime){
    fStopTime = DeltaTime("21130101-0000");
  }
  fInitializeDone = true;
  std::cout<<"  [DmpCore::Initialize] ... initialized successfully"<<std::endl;
  return true;
}

//-------------------------------------------------------------------
bool DmpCore::Run(){
  if(not fInitializeDone){
    return false;
  }
  std::cout<<"\n  [DmpCore::Run] Running..."<<std::endl;
// *
// *  TODO: use cut of time range??
// *
  while(not fTerminateRun){
    if(fCurrentEventID == fMaxEventNo){
      fTerminateRun = true;
      break;
    }else if(fCurrentEventID%5000 == 0){
      std::cout<<"\t [DmpCore::Run] event ID = "<<fCurrentEventID<<std::endl;
    }
    if(gRootIOSvc->PrepareEvent(fCurrentEventID)){
      if(fAlgMgr->ProcessOneEvent()){
        gRootIOSvc->FillEvent();
      }
      ++fCurrentEventID;
    }else{
      fTerminateRun = true;
      break;
    }
  }
  std::cout<<"  [DmpCore::Run] Done"<<std::endl;
  return true;
}

//-------------------------------------------------------------------
bool DmpCore::ExecuteEventID(const long &evtID){
  if(not fInitializeDone){
    return false;
  }
  fCurrentEventID = evtID;
  std::cout<<"\n  [DmpCore::ExecuteEvent] execute event: ID = "<<fCurrentEventID<<std::endl;
  gRootIOSvc->PrepareMetaData();
  if(gRootIOSvc->PrepareEvent(fCurrentEventID)){
    fAlgMgr->ProcessOneEvent();
  }
  std::cout<<"  [DmpCore::ExecuteEvent] Done\n"<<std::endl;
  return true;
}

//-------------------------------------------------------------------
bool DmpCore::ExecuteEventTime(const std::string &time){
  if(not fInitializeDone){
    return false;
  }
  std::cout<<"\n  [DmpCore::ExecuteEvent] event time = "<<time<<std::endl;
// *
// *  TODO:  finish me
// *
  std::cout<<"  [DmpCore::ExecuteEvent] Done\n"<<std::endl;
  return true;
}

//-------------------------------------------------------------------
bool DmpCore::Finalize(){
  std::cout<<"\n  [DmpCore::Finalize] Finalize..."<<std::endl;
  //*
  //* Important! First, finalize algorithms, then services!
  //*
  fAlgMgr->Finalize();
  fSvcMgr->Finalize();
  std::cout<<"  [DmpCore::Finalize] ... finalized successfully"<<std::endl;
  return true;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
void DmpCore::Set(const std::string &type,const std::string &value){
  if(OptMap.find(type) == OptMap.end()){
    DmpLogError<<"\t[DmpCore::Set] No argument type: "<<type<<DmpLogEndl;
    throw;
  }
  switch(OptMap[type]){
    case 0: // LogLevel
    {
      DmpLog::SetLogLevel(value);
      break;
    }
    case 1: // EventNumber
    {
      fMaxEventNo = boost::lexical_cast<long>(value);
      break;
    }
    case 2: // StartTime
    {
      fStartTime = DeltaTime(value);
      break;
    }
    case 3: // StopTime
    {
      fStopTime = DeltaTime(value);
      break;
    }
  }
}

//-------------------------------------------------------------------
long DmpCore::DeltaTime(const std::string &endT)const{
  std::string tmp;
  struct tm startT;    // 20130101-0000
  tmp.assign(fLaunchTime.begin(),  fLaunchTime.begin()+4);    startT.tm_year = boost::lexical_cast<int>(tmp) - 1900;  // since 1900
  tmp.assign(fLaunchTime.begin()+4,fLaunchTime.begin()+6);    startT.tm_mon  = boost::lexical_cast<int>(tmp) - 1;     // 0 ~ 11
  tmp.assign(fLaunchTime.begin()+6,fLaunchTime.begin()+8);    startT.tm_mday = boost::lexical_cast<int>(tmp);         // 1 ~ 31
  tmp.assign(fLaunchTime.end()-4,  fLaunchTime.end()-2);      startT.tm_hour = boost::lexical_cast<int>(tmp);         // 0 ~ 23
  tmp.assign(fLaunchTime.end()-2,  fLaunchTime.end());        startT.tm_min  = boost::lexical_cast<int>(tmp);         // 0 ~ 59
  startT.tm_sec = 0;       // 0 ~ 60
  struct tm stopT;
  tmp.assign(endT.begin(),  endT.begin()+4);    stopT.tm_year = boost::lexical_cast<int>(tmp) - 1900;  // since 1900
  tmp.assign(endT.begin()+4,endT.begin()+6);    stopT.tm_mon  = boost::lexical_cast<int>(tmp) - 1;     // 0 ~ 11
  tmp.assign(endT.begin()+6,endT.begin()+8);    stopT.tm_mday = boost::lexical_cast<int>(tmp);         // 1 ~ 31
  tmp.assign(endT.end()-4,  endT.end()-2);      stopT.tm_hour = boost::lexical_cast<int>(tmp);         // 0 ~ 23
  tmp.assign(endT.end()-2,  endT.end());        stopT.tm_min  = boost::lexical_cast<int>(tmp);         // 0 ~ 59
  stopT.tm_sec = 0;       // 0 ~ 60
  return difftime(mktime(&stopT),mktime(&startT));
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


