/*
 *  $Id: DmpRunMode.h, 2014-05-02 14:20:16 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpRunMode_H
#define DmpRunMode_H

namespace DmpDetector{
  enum DmpERunMode{
    kUnknow = -1,
    k0Compress = 1,
    kCompress = 5,
    kCalPed = 6,
    kCalADC = 7,
  };
}

#endif


