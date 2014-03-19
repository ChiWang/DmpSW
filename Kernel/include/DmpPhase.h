/*
 *  $Id: DmpPhase.h, 2014-03-19 10:19:58 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpPhase_H
#define DmpPhase_H

namespace DmpCore{
  enum DmpEPhase{
    kQuarter,     // 1/4 prototype, contains Psd, Bgo, Nud.       >>>> Since 2012 <<<<
                  // (0)  Beam test at SPS, include Si and MecMegas       2012/10
    kPrototype,   // whole DAMPE payload, Stk, Psd, Bgo, Nud.     >>>> Since 2014 <<<<
                  // (0)  Beam test at ??
    kProduct,     // the final one which send into outspace.      >>>> Since 2015 <<<<
  };
}

#endif


