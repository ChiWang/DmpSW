/*
 *  $Id: DmpDetectorID.h, 2014-03-19 09:54:34 chi $
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


