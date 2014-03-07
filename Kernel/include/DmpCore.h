/*
 *  $Id: DmpCore.h, 2014-03-07 15:50:33 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#ifndef DmpCore_H
#define DmpCore_H

// *
// *  TODO: binding S(G)etPhase to boost python, and set it at the begining to run jobs in python script
// *
namespace DmpCore{
  // for phase
  enum DmpPhase{
    kBT2012,
    kCT2013,
    kFinal,
  };
  extern DmpPhase gPhase;
  void SetPhase(DmpPhase);
  DmpPhase GetPhase();

  //  for detector
  const short kSubDetNo=4;
  enum DmpDetectorID{
    kWhole,
    kPsd,
    kStk,
    kBgo,
    kNud
  };
}

#endif
