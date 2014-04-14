/*
 *  $Id: DmpRdcSvcOption.h, 2014-04-10 21:26:14 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcSvcOption_H
#define DmpRdcSvcOption_H

#include "DmpVOptionSvc.h"

class DmpRdcSvcOption : public DmpVOptionSvc{
public:
        /*
  static DmpRdcSvcOption*  GetInstance(){
    static DmpRdcSvcOption  instance;
    return &instance;
  }
  */
  DmpRdcSvcOption();
  ~DmpRdcSvcOption();
  void Set(const std::string&,DmpDetector::DmpEDetectorID,const std::string&);
  std::string Get(const std::string&);

public:
  std::string GetConnectorPath(DmpDetector::DmpEDetectorID id) const {return fConnectorPath[id];}

private:
  std::string    fConnectorPath[DmpDetector::gSubDetNo];

};

#endif


