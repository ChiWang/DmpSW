/*
 *  $Id: DmpDetectorID.h, 2014-05-27 20:09:00 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpDetectorID_H
#define DmpDetectorID_H

namespace DmpDetector{
  const short gSubDetNo=4;
  enum DmpEDetectorID{
    kPsd = 0,
    kStk = 1,
    kBgo = 2,
    kNud = 3,
    kWhole = gSubDetNo
  };
}

#endif


