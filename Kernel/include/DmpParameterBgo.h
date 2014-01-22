/*=====================================================================
 *   File:   DmpParameterBgo.h
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    06/08/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  14/12/2013   16:09:41
=====================================================================*/

#ifndef DmpParameterBgo_H
#define DmpParameterBgo_H

namespace DmpParameter{

  namespace Bgo{            //Sub-detector  Bgo parameters                             
    const short kPlaneNb = 7;
    const short kBarNb   = 22;
    const short kRefBarNb= 2;
    const short kSideNb  = 2;
    const short kDyNb    = 3;

    namespace BT2012{
      const short kPlaneNb = 6;
      const short kBarNb   = 11;
      const short kRefBarNb= 2;
      const short kSideNb  = 1;
      const short kDyNb    = 3;
    }

    namespace CT2013{
      const short kPlaneNb = 6;
      const short kBarNb   = 11;
      const short kRefBarNb= 2;
      const short kSideNb  = 1;
      const short kDyNb    = 3;
    }
  }

}

#endif

