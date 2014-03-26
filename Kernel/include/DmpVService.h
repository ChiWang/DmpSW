/*
 *  $Id: DmpVService.h, 2014-03-15 09:46:48 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/03/2014
*/

#ifndef DmpVService_H
#define DmpVService_H

#include <string>

class DmpVService{
/*
 *  DmpVService
 *
 *  user could add theirself service(derive from DmpVService) and AppendThisService into DmpServiceManager, only accept DmpVService*
 *
 */
public:
  DmpVService(const std::string &n):fName(n){}
  virtual ~DmpVService(){}
  std::string Name() const   {return fName;}

private:
  std::string   fName;

};

#endif


