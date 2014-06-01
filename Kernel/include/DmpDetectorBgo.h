/*
 *  $Id: DmpDetectorBgo.h, 2014-05-28 17:38:01 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 06/08/2013
*/

#ifndef DmpDetectorBgo_H
#define DmpDetectorBgo_H

namespace DmpDetector{
/*
 *  only set one phase.
 *
 *  If you want to use anything in run time job option files,
 *  bind them in the DmpDetectorSubDetID.cc file
 *
 */
  namespace Bgo{
    const short kPlaneNo = 7;
    const short kRefBarNo= 2;
    const short kBarNo   = 22;
    const short kSideNo  = 2;
    const short kDyNo    = 3;
  }
}

#endif

