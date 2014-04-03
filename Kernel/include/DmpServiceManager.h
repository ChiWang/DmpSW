/*
 *  $Id: DmpServiceManager.h, 2014-04-03 17:30:49 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/03/2014
*/

#ifndef DmpServiceManager_H
#define DmpServiceManager_H

#include "DmpVService.h"
#include "DmpElementManager.h"

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


