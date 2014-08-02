/*
 *  $Id: DmpDataError.h, 2014-07-31 10:41:07 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 31/07/2014
*/

#ifndef DmpDataError_H
#define DmpDataError_H

namespace DmpDataError{
  enum Type{
    Good = 0,
    NotFind_0xeb = 1,
    NotFind_0x90 = 2,
    DataLength_Wrong = 3,
    Trigger_NotMatch = 4,
    Trigger_Skip = 5,        // TODO how to check?
    CRC_Wrong = 6
  };
}

#endif

