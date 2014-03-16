/*
 *  $Id: DmpServiceManager.h, 2014-03-15 09:46:52 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/03/2014
*/

#ifndef DmpServiceManager_H
#define DmpServiceManager_H

#include <string>
#include <map>

class DmpVService;
class DmpServiceManager{
public:
  static DmpServiceManager*  GetInstance();
  ~DmpServiceManager();
  DmpVService*  GetService(const std::string&);
  void AppendThisService(const std::string&, DmpVService*);
  void ListAllService();

private:
  DmpServiceManager(){}

private:
  std::map<std::string,DmpVService*>        fServiceMap;

};

#endif

