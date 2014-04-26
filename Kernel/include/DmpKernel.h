/*
 *  $Id: DmpKernel.h, 2014-04-22 13:45:03 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/04/2014
*/

#ifndef DmpKernel_H
#define DmpKernel_H

//#include <string>

class DmpAlgorithmManager;
class DmpServiceManager;

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
  bool Initialize();            // execute all elements' Initialize() in all *Mgr
  bool Run();                   // run one job
  bool Finalize();              // execute all elements' Finalize() in all *Mgr

  DmpAlgorithmManager*  AlgorithmManager() const {return fAlgMgr;}
  DmpServiceManager*    ServiceManager() const {return fSvcMgr;}

private:
  DmpKernel();

private:
  DmpAlgorithmManager   *fAlgMgr;
  DmpServiceManager     *fSvcMgr;

};

#endif

