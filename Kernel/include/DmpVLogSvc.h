/*
 *  $Id: DmpVLogSvc.h, 2014-04-08 06:44:11 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 08/04/2014
*/

#ifndef DmpVLogSvc_H
#define DmpVLogSvc_H

#include "DmpVSvc.h"

class DmpVLogSvc : public DmpVSvc{
/*
 *  DmpVLogSvc
 *
 *  all log class derived from here
 *
 */
public:
  DmpVLogSvc(const std::string &n):DmpVSvc(n){}
  virtual ~DmpVLogSvc(){}
  virtual void StatusLog(const short&) const=0;

public:
  bool Initialize(){}
  bool Finalize(){}

};

#endif

