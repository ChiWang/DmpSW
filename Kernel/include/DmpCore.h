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
  bool Initialize();            // execute all elements' Initialize() in all *Mgr
  bool Run();                   // run one job
  bool Finalize();              // execute all elements' Finalize() in all *Mgr
  void SetLogLevel(const short &level)const;
  /*
   * LogLevel
   *     types: {error(8) | warning(4) | information(2) | debug(1)}
   *    0:      nothing
   *    1:      debug
   *    2:      infor.
   *    3:      debug + infor.
   *    4:      warning
   *    5:      warning + debug
   *    6:      warning + infor.
   *    7:      warning + infor. + debug
   *    8:      error
   *    9:      error + debug
   *    10:     error + infor.
   *    11:     error + infor. + debug
   *    12:     error + warning
   *    13:     error + warning + debug
   *    14:     error + warning + infor.
   *    15:     error + warning + infor. + debug
   */
  void SetMaxEventNumber(const long &i) {fMaxEventNo = i;}
  void SetTimeWindow(const std::string &type,const short &year,const short &month,const short &day,const short &hour,const short &minute,const short &second);
  bool EventInTimeWindow(const long &second) const;

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
};

//-------------------------------------------------------------------
extern DmpCore  *gCore;

#endif

