/*
 *  $Id: DmpCore.h, 2014-03-07 15:50:33 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpCore_H
#define DmpCore_H

namespace DmpCore{
  namespace Phase{
    enum DmpPhase{
      kBT2012,
      kCT2013,
      kFinal,
    };
  }
}
typedef DmpCore::Phase::DmpPhase DmpEPhase;

namespace DmpParameter{
  namespace Detector{
    const short kSubDetNo=4;
    enum DmpDetectorID{
      kWhole,
      kPsd,
      kStk,
      kBgo,
      kNud
    };
  }
}
typedef DmpParameter::Detector::DmpDetectorID DmpEDetectorID;

#endif
