/*
 *  $Id: DmpRdcOption.h, 2014-04-02 22:18:01 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcOption_H
#define DmpRdcOption_H

#include "DmpVRunTimeOptionSvc.h"

class DmpRdcOption : public DmpVRunTimeOptionSvc{
public:
  /*
  static DmpRdcOption*  GetInstance(){
    static DmpRdcOption  instance;
    return &instance;
  }
  */
  DmpRdcOption(const std::string&);
  ~DmpRdcOption();
  void Set(const std::string&,DmpDetector::DmpEDetectorID,const std::string&);

public:
  std::string GetConnectorPath(DmpDetector::DmpEDetectorID id) const {return fConnectorPath[id];}

private:
  std::string    fConnectorPath[DmpDetector::gSubDetNo];

};

#endif

