/*
 *  $Id: DmpDetectorID.h, 2014-06-30 01:06:43 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpDetectorID_H
#define DmpDetectorID_H

namespace DmpDetectorID{
  const short gSubDetNo=4;
  enum Type{
    kPsd = 0,
    kStk = 1,
    kBgo = 2,
    kNud = 3,
    kWhole = gSubDetNo
  };
}

#endif


