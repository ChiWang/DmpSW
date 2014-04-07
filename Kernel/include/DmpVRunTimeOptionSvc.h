/*
 *  $Id: DmpVRunTimeOptionSvc.h, 2014-04-07 19:26:05 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/04/2014
*/

#ifndef DmpVRunTimeOptionSvc_H
#define DmpVRunTimeOptionSvc_H

#include "DmpVService.h"
#include "DmpDetectorID.h"

class DmpVRunTimeOptionSvc : public DmpVService{
/*
 * DmpVRunTimeOptionSvc
 *
 *  control some job options in run time through this class
 *
 */
public:
  DmpVRunTimeOptionSvc(const std::string &n):DmpVService(n){}
  virtual ~DmpVRunTimeOptionSvc(){}
  virtual bool Initialize() {return true;}
  virtual bool Finialize()  {return true;}

  virtual void Set(const std::string&,DmpDetector::DmpEDetectorID, const std::string&)=0;

};

#endif


