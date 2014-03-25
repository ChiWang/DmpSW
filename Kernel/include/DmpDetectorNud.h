/*
 *  $Id: DmpDetectorNud.h, 2014-03-12 11:25:35 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpDetectorNud_H
#define DmpDetectorNud_H

/*  >>> Example Bgo <<<
 *  set only one phase.
 *
 *  If you want to use anything in run time job option files,
 *  bind them in the DmpDetectorSubDetID.cc file
 *
 */
namespace DmpDetector{
  namespace Nud{            //Sub-detector  Nud parameters                             
    const short kPlaneNo = 1;
    const short kBlockNo = 4;
    const short kSideNo  = 1;
    const short kDyNo    = 1;
    const short kFEEType = 2;
  }
}

#endif

