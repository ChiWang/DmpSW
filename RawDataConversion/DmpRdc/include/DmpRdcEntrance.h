/*
 *  $Id: DmpRdcEntrance.h, 2014-03-14 11:15:54 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpRdcEntrance_H
#define DmpRdcEntrance_H

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


