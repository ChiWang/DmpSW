/*
 *  $Id: DmpServiceManager.h, 2014-03-15 09:46:52 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/03/2014
*/

#ifndef DmpServiceManager_H
#define DmpServiceManager_H

#include "DmpElementManager.h"

class DmpVService;

class DmpServiceManager : public DmpElementManager<DmpVService>{
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

private:
  DmpServiceManager();

};

//-------------------------------------------------------------------
extern DmpServiceManager  *gSvcMgr;

#endif


