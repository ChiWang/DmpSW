/*
 *  $Id: DmpRdcSvcOption.h, 2014-04-10 21:26:14 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcOption_H
#define DmpRdcOption_H

#include "DmpVOptionSvc.h"

class DmpRdcOption : public DmpVOptionSvc{
public:
  static DmpRdcOption*  GetInstance(){
    static DmpRdcOption  instance;
    return &instance;
  }
  ~DmpRdcOption();
  void Set(const std::string&,DmpDetector::DmpEDetectorID,const std::string&);
  std::string Get(const std::string&);

private:
  DmpRdcOption();

public:
  std::string GetConnectorPath(DmpDetector::DmpEDetectorID id) const {return fConnectorPath[id];}

private:
  std::string    fConnectorPath[DmpDetector::gSubDetNo];

};

extern DmpRdcOption *gRdcOpt;

#endif


