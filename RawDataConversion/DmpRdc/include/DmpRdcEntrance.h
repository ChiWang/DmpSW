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
  void RdcExecute(const std::string&, const short &level);   // run one raw data. Trigger match level(with Bgo) 1: Psd; 2(or 3): Psd, Stk; 4: Psd, Stk, Nud
  void RdcClear();
}

#endif


