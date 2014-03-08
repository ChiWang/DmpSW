/*
 *  $Id: DmpEntranceRdc.h, 2014-03-08 19:44:00 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpEntranceRdc_H
#define DmpEntranceRdc_H

#include <string>

namespace DmpCore{
  void RdcSetInDataPath(std::string);
  void RdcSetOutDataPath(std::string);
  std::string RdcGetOutDataPath();
  void RdcInitialize();           // set connector
  void RdcSetOutDataName(std::string);    // just for the coming Execute()
  void RdcExecute(std::string);   // run a raw data
  void RdcClear();
}

#endif


