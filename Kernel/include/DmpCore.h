/*
 *  $Id: DmpCore.h, 2014-03-11 18:40:31 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpCore_H
#define DmpCore_H

namespace DmpCore{
  enum EPhase{
    kQuarter,     // 1/4 prototype, contains Psd, Bgo, Nud.       >>>> Since 2012 <<<<
                  // (0)  Beam test at SPS, include Si and MecMegas       2012/10
    kPrototype,   // whole DAMPE payload, Stk, Psd, Bgo, Nud.     >>>> Since 2014 <<<<
                  // (0)  Beam test at ??
    kProduct,     // the final one which send into outspace.      >>>> Since 2015 <<<<
  };
  enum ERunMode{
    kUnknow = -1,
    kCompress = 5,
    kCalPed = 6,
    kCalADC = 7,
  };
  const short gSubDetNo=4;
  enum EDetectorID{
    kPsd = 0,
    kStk = 1,
    kBgo = 2,
    kNud = 3,
    kWhole = gSubDetNo,
  };
}

typedef DmpCore::EPhase         DmpEPhase;
typedef DmpCore::ERunMode       DmpERunMode;
typedef DmpCore::EDetectorID    DmpEDetectorID;

#endif


