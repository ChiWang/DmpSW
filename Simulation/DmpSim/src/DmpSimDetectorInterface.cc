/*
 *  $Id: DmpSimDetectorInterface.cc, 2014-03-17 17:49:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/03/2014
*/

#include "DmpSimDetectorInterface.h"

DmpSimDetectorInterface* DmpSimDetectorInterface::GetInstance(){
  static DmpSimDetectorInterface instance;
  return &instance;
}

DmpSimDetectorInterface::~DmpSimDetectorInterface(){
}

DmpSimDetectorInterface::DmpSimDetectorInterface(){
  for(short i=0;i<DmpCore::gSubDetNo + 1;++i){
    fGdmlPath[i]="default";
  }
  fOffset[DmpCore::kPsd] = -33.4;
  fOffset[DmpCore::kStk] = 0;
  fOffset[DmpCore::kBgo] = 200;
  fOffset[DmpCore::kNud] = 0;
}

