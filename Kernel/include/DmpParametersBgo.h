/*
 *  $Id: DmpParametersBgo.h, 2014-02-24 22:56:41 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 06/08/2013
*/

#ifndef DmpParametersBgo_H
#define DmpParametersBgo_H

namespace DmpParameters{

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

#endif

