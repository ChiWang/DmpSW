/*
 *  $Id: DmpCore.h, 2014-05-04 15:33:11 DAMPE $
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
  void SetLogLevel(const short &l) {fLogLevel = l;}
  void SetMaxEventNumber(const long &i) {fMaxEventNo = i;}

  DmpAlgorithmManager*  AlgorithmManager() const {return fAlgMgr;}
  DmpServiceManager*    ServiceManager() const {return fSvcMgr;}

public:
  bool PrintError() const;
  bool PrintWarning() const;
  bool PrintDebug() const;

private:
  DmpCore();

private:
// *
// *  TODO:     add 2 variables
//          1.  max event number, process how many event?
//          2.  time window, only event in this time range
// *
  DmpAlgorithmManager   *fAlgMgr;       // algorithm manager, singleton
  DmpServiceManager     *fSvcMgr;       // service manager, singleton
  short                 fLogLevel;      // log level
  /*
   * fLogLevel
   *     types: {error(4) | warning(2) | debug(1)}
   *    0:      nothing
   *    1:      debug
   *    2:      warning
   *    3:      warning + debug
   *    4:      error
   *    5:      error + debug
   *    6:      error + warning
   *    7:      error + warning + debug
   */
  long                  fMaxEventNo;    // run how many event
};

//-------------------------------------------------------------------
extern DmpCore  *gCore;

#endif

