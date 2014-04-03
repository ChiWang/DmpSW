/*
 *  $Id: DmpRdcEntrance.h, 2014-03-19 12:40:33 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpRdcEntrance_H
#define DmpRdcEntrance_H

#include <string>

namespace DmpCore{
  void RdcInitialize();           // create algorithm of detectors, setup connectors
  void RdcExecute(const std::string&);
  void RdcClear();
}

#endif


