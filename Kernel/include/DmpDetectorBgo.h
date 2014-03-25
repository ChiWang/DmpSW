/*
 *  $Id: DmpDetectorBgo.h, 2014-03-25 12:26:21 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 06/08/2013
*/

#ifndef DmpDetectorBgo_H
#define DmpDetectorBgo_H

/*
 *  set only one phase.
 *
 *  If you want to use anything in run time job option files,
 *  bind them in the DmpDetectorSubDetID.cc file
 *
 */
namespace DmpDetector{
  namespace Bgo{
    const short kPlaneNo = 6;
    const short kRefBarNo= 2;
    const short kBarNo   = 11;
    const short kSideNo  = 1;
    const short kDyNo    = 3;
    const short kFEENo   = 6;
    const short kFEEType = 0;
    const short kFEEChannelNo = 78;
    /*
    enum DmpEBgoPhase{
      kQuarter,     // 1/4 prototype    >>>> Since 2012 <<<<
                    // (0)  Beam test at SPS. 2012
      kPrototype,   // full size        >>>> Since 2014 <<<<
                    // (0)  Beam test at ??
      kProduct,     // full size        >>>> Since 2015 <<<<
    };
    extern DmpEBgoPhase gPhase;
    namespace Quarter{
      const short kPlaneNo = 6;
      const short kBarNo   = 11;
      const short kSideNo  = 1;
      const short kFEENo   = 6;
      const short kFEEChannelNo = 78;
    }
    namespace Prototype{
      const short kPlaneNo = 7;
      const short kBarNo   = 22;
      const short kSideNo  = 2;
    }
    namespace Product{
      const short kPlaneNo = 7;
      const short kBarNo   = 22;
      const short kSideNo  = 2;
    }
    */
  }
}

#endif

