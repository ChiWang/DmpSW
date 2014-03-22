/*
 *  $Id: DmpDetectorNud.h, 2014-03-12 11:25:35 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpDetectorNud_H
#define DmpDetectorNud_H

/*  >>> Example Bgo <<<
 *  add any phase for yourself detector one day later
 *
 *  and set the unstable variables into your phase.
 *
 */
namespace DmpDetector{
  namespace Nud{            //Sub-detector  Nud parameters                             
    const short kPlaneNo = 6;
    const short kBarNo   = 11;
    const short kRefBarNo= 2;
    const short kSideNo  = 1;
    const short kDyNo    = 3;
    const short kFEEType = 2;
  }
}

#endif

