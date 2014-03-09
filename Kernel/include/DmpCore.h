/*
 *  $Id: DmpCore.h, 2014-03-09 00:39:47 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpCore_H
#define DmpCore_H

namespace DmpCore{
  namespace Phase{
    enum DmpPhase{
      kQuarter,     // 1/4 prototype, contains Psd, Bgo, Nud.       >>>> Since 2012 <<<<
                    // (0)  Beam test at SPS, include Si and MecMegas       2012/10
      kPrototype,   // whole DAMPE payload, Stk, Psd, Bgo, Nud.     >>>> Since 2014 <<<<
                    // (0)  Beam test at ??
      kProduct,     // the final one which send into outspace.      >>>> Since 2015 <<<<
    };
  }
  namespace RunMode{
    enum DmpRunMode{
      kUnknow = -1,
      kCompress = 5,
      kCalPed = 6,
      kCalADC = 7,
    };
  }
}
typedef DmpCore::Phase::DmpPhase        DmpEPhase;
typedef DmpCore::RunMode::DmpRunMode    DmpERunMode;

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


