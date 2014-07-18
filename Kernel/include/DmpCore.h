/*
 *  $Id: DmpCore.h, 2014-06-27 09:56:59 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/04/2014
*/

#ifndef DmpCore_H
#define DmpCore_H

#include "DmpAlgorithmManager.h"
#include "DmpServiceManager.h"

class DmpCore{
/*
 *  DmpCore
 *
 *      Core of DAMPE software. It's a singleton in one job.
 *
 */
public:
  static DmpCore* GetInstance(){
    static DmpCore instance;
    return &instance;
  }
  ~DmpCore();

public:     // binding functions
  bool Initialize();            // execute all elements' Initialize() in all *Mgr
  bool Run();                   // run one job
  bool ExecuteEventID(const long &evtID);         // just execute event ID = evtID
  bool ExecuteEventTime(const std::string &time);   // execute one event, Event time = time
  bool Finalize();              // execute all elements' Finalize() in all *Mgr

public:
  const long& GetMaxEventNumber() const {return fMaxEventNo;}
  const long& GetCurrentEventID() const {return fCurrentEventID;}
  bool EventInTimeWindow(const long &second) const;
  const bool& InitializeDone() const {return fInitializeDone;}

public:
  void Set(const std::string &type,const std::string &value);
  DmpAlgorithmManager*  AlgorithmManager() const {return fAlgMgr;}
  DmpServiceManager*    ServiceManager() const {return fSvcMgr;}

public:
  void TerminateRun()   {fTerminateRun = true;} // call me in algorithms

private:
  DmpCore();
  long DeltaTime(const std::string&)const;

private:
  DmpAlgorithmManager   *fAlgMgr;       // algorithm manager, singleton
  DmpServiceManager     *fSvcMgr;       // service manager, singleton
  std::string           fLaunchTime;    // lauch time, 20130101-0000
  long                  fMaxEventNo;    // run how many event
  long                  fStartTime;     // unit: second. start time of time window
  long                  fStopTime;      // unit: second. stop time of time window

private:
  bool      fInitializeDone;        // default is false
  bool      fTerminateRun;          // concrete algorithm could set this value
  std::map<std::string,short>    OptMap; // option map

private:
  long      fCurrentEventID;        // the current event ID (processing)

};

//-------------------------------------------------------------------
extern DmpCore  *gCore;

#endif

