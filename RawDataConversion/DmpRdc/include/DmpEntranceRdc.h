/*
 *  $Id: DmpEntranceRdc.h, 2014-03-08 23:38:24 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpEntranceRdc_H
#define DmpEntranceRdc_H

#include <string>

namespace DmpCore{
  void RdcSetConnectorStk(std::string);        // set connector path
  void RdcSetConnectorPsd(std::string);
  void RdcSetConnectorBgo(std::string);
  void RdcSetConnectorNud(std::string);

  bool RdcSetInDataPath(std::string);
  void RdcSetOutDataPath(std::string);  std::string RdcGetOutDataPath();
  void RdcSetOutDataName(std::string);    // just for the coming Execute()
  void RdcInitialize();           // set connector
  void RdcExecute(std::string);   // run a raw data
  void RdcClear();
}

#endif


