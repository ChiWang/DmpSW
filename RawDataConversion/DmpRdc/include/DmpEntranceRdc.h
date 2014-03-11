/*
 *  $Id: DmpEntranceRdc.h, 2014-03-11 16:44:12 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpEntranceRdc_H
#define DmpEntranceRdc_H

#include <string>

namespace DmpCore{
  bool RdcSetConnector(Detector::DmpDetectorID,std::string);

  void RdcSetOutDataPath(std::string);  std::string RdcGetOutDataPath();
  void RdcSetOutDataName(std::string);    // just for the coming Execute()
  bool RdcInitialize();           // actually, do nothing
  void RdcExecute(std::string);   // run a raw data
  void RdcClear();
}

#endif


