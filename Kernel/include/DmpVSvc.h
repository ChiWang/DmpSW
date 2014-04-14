/*
 *  $Id: DmpVSvc.h, 2014-04-12 16:32:51 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 10/04/2014
*/

#ifndef DmpVSvc_H
#define DmpVSvc_H

#include <string>
#include "DmpDetectorID.h"

class DmpVSvc{
/*
 *  DmpVSvc
 *
 *      all service derived from this class, and then
 *      append into Dmp Service Manager, in python
 *
 */
public:
  DmpVSvc(const std::string &n):fName(n){}
  virtual ~DmpVSvc(){}

public:
  virtual bool Initialize()=0;
  virtual bool Finalize()=0;
  virtual void Set(const std::string&,const std::string&){}    // for global options, binding me

public:
  const std::string& Name() const {return fName;}
  // for SubDet options, binding me
  void SetSubDet(DmpDetector::DmpEDetectorID id,const std::string &type,const std::string &argv){
    if(id == DmpDetector::kPsd){
      SetPsd(type,argv);
    }else if(id == DmpDetector::kStk){
      SetStk(type,argv);
    }else if(id == DmpDetector::kBgo){
      SetBgo(type,argv);
    }else if(id == DmpDetector::kNud){
      SetNud(type,argv);
    }
  }

protected:
  virtual void SetPsd(const std::string &type,const std::string &argv){}
  virtual void SetStk(const std::string &type,const std::string &argv){}
  virtual void SetBgo(const std::string &type,const std::string &argv){}
  virtual void SetNud(const std::string &type,const std::string &argv){}

private:
  std::string   fName;

};

#endif


