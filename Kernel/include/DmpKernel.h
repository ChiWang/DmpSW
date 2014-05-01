/*
 *  $Id: DmpKernel.h, 2014-04-30 23:18:38 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/04/2014
*/

#ifndef DmpKernel_H
#define DmpKernel_H

#include "DmpAlgorithmManager.h"
#include "DmpServiceManager.h"

class DmpKernel{
/*
 *  DmpKernel
 *
 *      Kernel of DAMPE software. It's a singleton in one job.
 *
 */
public:
  static DmpKernel* GetInstance(){
    static DmpKernel instance;
    return &instance;
  }
  ~DmpKernel();

public:     // binding functions
  bool Initialize();            // execute all elements' Initialize() in all *Mgr
  bool Run();                   // run one job
  bool Finalize();              // execute all elements' Finalize() in all *Mgr
  void SetLogLevel(const short &l) {fLogLevel = l;}

  DmpAlgorithmManager*  AlgorithmManager() const {return fAlgMgr;}
  DmpServiceManager*    ServiceManager() const {return fSvcMgr;}

public:
  bool PrintError() const;
  bool PrintWarning() const;
  bool PrintDebug() const;

private:
  DmpKernel();

private:
  DmpAlgorithmManager   *fAlgMgr;
  DmpServiceManager     *fSvcMgr;
  short                 fLogLevel;
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
};

//-------------------------------------------------------------------
extern DmpKernel  *gKernel;

#endif

