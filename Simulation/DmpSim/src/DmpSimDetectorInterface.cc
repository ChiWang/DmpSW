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
  for(short i=0;i<DmpDetector::gSubDetNo + 1;++i){
    fGdmlPath[i]="default";
  }
  fOffset[DmpDetector::kPsd] = -33.4;
  fOffset[DmpDetector::kStk] = 0;
  fOffset[DmpDetector::kBgo] = 200;
  fOffset[DmpDetector::kNud] = 0;
}

