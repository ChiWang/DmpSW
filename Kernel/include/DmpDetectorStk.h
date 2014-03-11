/*
 *  $Id: DmpDetectorStk.h, 2014-03-11 18:46:42 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpDetectorStk_H
#define DmpDetectorStk_H

/*  >>> Example Bgo <<<
 *  add any phase for yourself detector one day later
 *
 *  and set the unstable variables into your phase.
 *
 */
namespace DmpDetector{
  namespace Stk{            //Sub-detector  Stk parameters 
    const short kPlaneNo = 6;
    const short kBarNo   = 11;
    const short kRefBarNo= 2;
    const short kSideNo  = 1;
    const short kDyNo    = 3;
    const short kStdDataLength = ((kBarNo+kRefBarNo)*kDyNo*2+3)*2;          //3: (1)data Length 0x00a2; (2)reverse 0x0000; (3)CRC 0x0xxx.  *2:to unit Byte
  }
}

#endif

