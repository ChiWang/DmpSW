/*
 *  $Id: DmpParameterBgo.h, 2014-03-08 10:24:11 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 06/08/2013
*/

#ifndef DmpParameterBgo_H
#define DmpParameterBgo_H

namespace DmpParameter{
  namespace Detector{
    namespace Bgo{            //Sub-detector  Bgo parameters
      const short kPlaneNo = 7;
      const short kBarNo   = 22;
      const short kRefBarNo= 2;
      const short kSideNo  = 2;
      const short kDyNo    = 3;

      namespace BT2012{
        const short kPlaneNo = 6;
        const short kBarNo   = 11;
        const short kRefBarNo= 2;
        const short kSideNo  = 1;
        const short kDyNo    = 3;
      }

      namespace CT2013{
        const short kPlaneNo = 6;
        const short kBarNo   = 11;
        const short kRefBarNo= 2;
        const short kSideNo  = 1;
        const short kDyNo    = 3;
      }
    }
  }
}

#endif

