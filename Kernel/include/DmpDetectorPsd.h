/*
 *  $Id: DmpDetectorPsd.h, 2014-03-11 19:42:50 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpDetectorPsd_H
#define DmpDetectorPsd_H

/*  >>> Example Bgo <<<
 *  add any phase for yourself detector one day later
 *
 *  and set the unstable variables into your phase.
 *
 */
namespace DmpDetector{
  namespace Psd{
    enum DmpEPsdPhase{
      kQuarter,     // 1/4 prototype    >>>> Since 2012 <<<<
                    // (0)  Beam test at SPS. 2012
      kPrototype,   // full size        >>>> Since 2014 <<<<
                    // (0)  Beam test at ??
      kProduct,     // full size        >>>> Since 2015 <<<<
    };
    extern DmpEPsdPhase gPhase;
    const short kPlaneNo = 4;
    const short kRefBarNo= 2;
    const short kSideNo  = 2;
    const short kDyNo    = 2;
    namespace Quarter{
      const short kBarNo  = 11;
      const short kSideNo = 1;
      const short kFEENo  = 1;
    }
    namespace Prototype{
      const short kBarNo   = 22;
      const short kSideNo  = 2;
    }
    namespace Product{
      const short kBarNo   = 22;
      const short kSideNo  = 2;
    }
  }
}

#endif

