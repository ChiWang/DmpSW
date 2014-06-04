/*
 *  $Id: DmpCore.h, 2014-05-14 09:46:15 DAMPE $
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
  bool Initialise();            // execute all elements' Initialise() in all *Mgr
  bool Run();                   // run one job
  bool Finalize();              // execute all elements' Finalize() in all *Mgr

public:
  void SetLogLevel(const std::string&, const short &s=0) const;
  void SetMaxEventNumber(const long &i) {fMaxEventNo = i;}
  void SetTimeWindow(const std::string &type,const short &year,const short &month,const short &day,const short &hour,const short &minute,const short &second);
  const long& GetMaxEventNumber() const {return fMaxEventNo;}
  bool EventInTimeWindow(const long &second) const;
  const bool& InitialiseDone() const {return fInitializeDone;}

  DmpAlgorithmManager*  AlgorithmManager() const {return fAlgMgr;}
  DmpServiceManager*    ServiceManager() const {return fSvcMgr;}

private:
  DmpCore();

private:
  DmpAlgorithmManager   *fAlgMgr;       // algorithm manager, singleton
  DmpServiceManager     *fSvcMgr;       // service manager, singleton
  long                  fMaxEventNo;    // run how many event
  long                  fStartTime;     // unit: second. start time of time window
  long                  fStopTime;      // unit: second. stop time of time window

private:
  bool      fInitializeDone;        // default is false
};

//-------------------------------------------------------------------
extern DmpCore  *gCore;

#endif

