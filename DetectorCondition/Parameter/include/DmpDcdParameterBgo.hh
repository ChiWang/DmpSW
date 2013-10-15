/*=============================================================================
#       FileName :          DmpDcdParameterBgo.hh
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-06   11:12:32
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-03   16:57:31
=============================================================================*/

#ifndef DmpDcdParameterBgo_H
#define DmpDcdParameterBgo_H

namespace DmpDcdParameter{

  namespace Bgo{            //Sub-detector  Bgo parameters                             
    const short kPlaneNb = 1;
    const short kBarNb   = 22;
    const short kRefBarNb= 2;
    const short kSideNb  = 2;
    const short kDyNb    = 3;
    const short kStdDataLength = ((kBarNb+kRefBarNb)*kDyNb*kSideNb+3)*2;          //3: (1)data Length 0x00a2; (2)reverse 0x0000; (3)CRC 0x0xxx.  *2:to unit Byte
  }

}

#endif

