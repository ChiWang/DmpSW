/*
 *  $Id: DmpVOptionSvc.h, 2014-04-08 12:35:26 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/04/2014
*/

#ifndef DmpVOptionSvc_H
#define DmpVOptionSvc_H

#include "DmpVSvc.h"
#include "DmpDetectorID.h"

class DmpVOptionSvc : public DmpVSvc{
/*
 * DmpVOptionSvc
 *
 *  control some job options in run time through this class
 *
 */
public:
  DmpVOptionSvc(const std::string &n):DmpVSvc(n){}
  virtual ~DmpVOptionSvc(){}

  virtual void Set(const std::string&,DmpDetector::DmpEDetectorID, const std::string&)=0;
  virtual std::string Get(const std::string&)=0;

public:
  bool Initialize(){}
  bool Finalize(){}

};

#endif


