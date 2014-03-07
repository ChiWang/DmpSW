/*
 *  $Id: DmpParameterPhase.h, 2014-03-07 10:34:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 06/03/2014
*/

#ifndef DmpParameterPhases_H
#define DmpParameterPhases_H

// *
// *  TODO: binding gPhase to boost python, and run jobs in python script with the key line set gPhase = xxxx
// *
namespace DmpParameter{
  namespace DmpPhase{
    enum DmpEPhase {
      kBT2012,
      kCT2013,
      kFinal,
    };
    DmpPhase   gPhase;
  }
}

#endif
