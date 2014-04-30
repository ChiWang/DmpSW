/*
 *  $Id: DmpDetectorPsd.h, 2014-03-11 19:42:50 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpDetectorPsd_H
#define DmpDetectorPsd_H

/*  >>> Example Bgo <<<
 *
 *  set only one phase.
 *
 *  If you want to use anything in run time job option files,
 *  bind them in the DmpDetectorSubDetID.cc file
 */
namespace DmpDetector{
  namespace Psd{
    const short kPlaneNo = 2;
    const short kBarNo   = 24;
    const short kRefBarNo= 2;
    const short kSideNo  = 2;
    const short kDyNo    = 2;
  }
}

#endif

