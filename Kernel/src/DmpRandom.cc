/*
 *  $Id: DmpRandom.cc, 2014-06-12 13:57:24 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 11/06/2014
*/

#include "CLHEP/Random/Random.h"
#include "DmpRandom.h"
#include "DmpLog.h"

//-------------------------------------------------------------------
bool DmpRandom::fActive = false;

//-------------------------------------------------------------------
void DmpRandom::SetSeed(long seed){
  if(fActive){
    DmpLogWarning<<"Already boot random engine"<<DmpLogEndl;
    ShowEngineStatus();
    return;
  }
  CLHEP::HepRandom::setTheSeed(seed);
  fActive = true;
}

//-------------------------------------------------------------------
long DmpRandom::GetSeed(){
  return CLHEP::HepRandom::getTheSeed();
}

//-------------------------------------------------------------------
void DmpRandom::ShowEngineStatus(){
  CLHEP::HepRandom::showEngineStatus();
}

