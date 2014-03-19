/*
 *  $Id: DmpRunMode.h, 2014-03-19 09:56:02 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpRunMode_H
#define DmpRunMode_H

namespace DmpDetector{
  enum DmpERunMode{
    kUnknow = -1,
    kCompress = 5,
    kCalPed = 6,
    kCalADC = 7,
  };
}

#endif


