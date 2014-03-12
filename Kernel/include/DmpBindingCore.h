/*
 *  $Id: DmpBindingCore.h, 2014-03-12 11:21:37 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 12/03/2014
*/

#ifndef DmpBindingCore_H
#define DmpBindingCore_H

/*
 *  This file is an enctrance for sub-det (Core ackage).
 *
 *  The functions below are defined in DmpDetectorSubDetID.cc, and invoked from DmpBindCore.cc
 *
 *  So, SubDet could bind anything they like(in DmpDetectorSubDetID.cc) without change DmpBindCore.cc
 *
 *
 *  This method (DmpBindingEntrance for subDet) will be used to other pacakges, in order to split details of python interface of subDet.
 *
 */

namespace DmpBindingEntrance{
  namespace Core{
    void Psd();
    void Stk();
    void Bgo();
    void Nud();
  }
}

#endif


