/*
 *  $Id: DmpServiceManager.h, 2014-03-15 09:46:52 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/03/2014
*/

#ifndef DmpServiceManager_H
#define DmpServiceManager_H

#include "DmpVSvc.h"
#include "DmpElementManager.h"

class DmpServiceManager : public DmpElementManager<DmpVSvc>{
/*
 * DmpServiceManager
 *
 * manage all service of DAMPE software
 *
 */
public:
  static DmpServiceManager* GetInstance(){
    static DmpServiceManager instance;
    return &instance;
  }
  ~DmpServiceManager();
  DmpVSvc*  Get(const std::string&);

private:
  DmpServiceManager();

};

//-------------------------------------------------------------------
extern DmpServiceManager  *gDmpSvcMgr;

#endif


