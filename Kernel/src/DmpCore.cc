/*
 *  $Id: DmpCore.cc, 2014-03-07 21:46:43 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include "DmpCore.h"
DmpCore::DmpPhase DmpCore::gPhase = DmpCore::kFinal;

void DmpCore::SetPhase(DmpCore::DmpPhase p){
  DmpCore::gPhase = p;
}

DmpCore::DmpPhase  DmpCore::GetPhase(){
  return  DmpCore::gPhase;
}
