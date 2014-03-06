/*
 *  $Id: DmpPhases.h, 2014-03-06 17:11:43 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 06/03/2014
*/

#ifndef DmpPhases_H
#define DmpPhases_H

// *
// *  TODO: bindoing gPhase to boost python, and run jobs in python script with the key line set gPhase = xxxx
// *
namespace DmpParameters{
  enum DmpPhases {
    kBT2012,
    kCT2013,
    kFinal,
  };
  DmpPhases   gPhase;
}

#endif
