/*
 *  $Id: DmpServiceManager.h, 2014-03-15 09:46:52 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/03/2014
*/

#ifndef DmpServiceManager_H
#define DmpServiceManager_H

#include <string>
#include <list>

class DmpVService;

class DmpServiceManager{
/*
 * DmpServiceManager
 *
 * manage all service of DAMPE software
 *
 *
 */
public:
  static DmpServiceManager* GetInstance(){
    static DmpServiceManager instance;
    return &instance;
  }
  ~DmpServiceManager();
  DmpVService*  GetService(const std::string &name, bool create=false);
  void AppendService(DmpVService*);
  void ReplaceService(DmpVService*);
  void ListAllService();

private:
  DmpServiceManager();

private:
  std::list<DmpVService*>   fSvcList;

};

//-------------------------------------------------------------------
extern DmpServiceManager  *gSvcMgr;

#endif


