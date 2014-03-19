/*
 *  $Id: DmpRdcConnectorInterface.h, 2014-03-19 10:45:52 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

#ifndef DmpRdcConnectorInterface_H
#define DmpRdcConnectorInterface_H

#include <string>

#include "DmpDetectorID.h"

class DmpRdcConnectorInterface{
public:
  static DmpRdcConnectorInterface*  GetInstance();
  ~DmpRdcConnectorInterface();
  void SetConnectorPath(DmpDetector::DmpEDetectorID id,const std::string &p) {fConnectorPath[id] = p;}
  std::string GetConnectorPath(DmpDetector::DmpEDetectorID id) const         {return fConnectorPath[id];}

private:
  DmpRdcConnectorInterface();

private:
  std::string    fConnectorPath[DmpDetector::gSubDetNo];

};

#endif

