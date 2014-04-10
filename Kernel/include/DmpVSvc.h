/*
 *  $Id: DmpVSvc.h, 2014-04-10 20:32:40 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 10/04/2014
*/

#ifndef DmpVSvc_H
#define DmpVSvc_H

#include <string>

class DmpVSvc{
public:
  DmpVSvc(const std::string &n):fName(n){}
  virtual ~DmpVSvc(){}
  virtual bool Initialize()=0;
  virtual bool Finalize()=0;

public:
  std::string   Name() const {return fName;}

private:
  std::string   fName;

};

#endif

