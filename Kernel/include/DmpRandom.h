/*
 *  $Id: DmpRandom.h, 2014-06-12 09:19:18 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 11/06/2014
*/

#ifndef DmpRandom_H
#define DmpRandom_H

namespace DmpRandom{
/*
 *  DmpRandom
 *
 *      Provide random number for whole job.
 *      using random engine: HepJamesRandom
 *
 */

//-------------------------------------------------------------------
  void SetSeed(long seed);
  long GetSeed();
  void ShowEngineStatus();

  extern bool fActive;
}

#endif


