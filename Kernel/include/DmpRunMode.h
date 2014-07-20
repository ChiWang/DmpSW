/*
 *  $Id: DmpRunMode.h, 2014-06-30 00:59:51 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpRunMode_H
#define DmpRunMode_H

namespace DmpRunMode{
  enum Type{
    kUnknow = 0,
    k0Compress = 1,
    kCompress = 5,
    kCalPed = 6,
    kCalDAC = 9
  };
}

#endif


