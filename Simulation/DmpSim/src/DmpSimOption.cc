/*
 *  $Id: DmpSimOption.cc, 2014-04-08 13:33:40 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/03/2014
*/

#include "DmpSimOption.h"
#include "DmpSimDataManager.h"

//-------------------------------------------------------------------
DmpSimOption::DmpSimOption(){
  for(short i=0;i<DmpDetector::gSubDetNo + 1;++i){
    fGdmlPath[i]="default";
  }
  fOffset[DmpDetector::kPsd] = -33.4;
  fOffset[DmpDetector::kStk] = 0;
  fOffset[DmpDetector::kBgo] = 200;
  fOffset[DmpDetector::kNud] = 0;
}

//-------------------------------------------------------------------
DmpSimOption::~DmpSimOption(){
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
void DmpSimOption::Set(const std::string &type,DmpDetector::DmpEDetectorID id, const std::string &argv){
  if(type == "gdmlPath"){
    fGdmlPath[id] = argv;
  }else if(type == "offset"){
    fOffset[id] = boost::lexical_cast<float>(argv);
  }else if(type == "outDataPath"){
    gDataMgr->SetOutDataPath(argv);
  }else if(type == "outDataNote"){
    gDataMgr->AppendDataNote(argv);
  }
}


//-------------------------------------------------------------------
DmpSimOption *gSimOpt = DmpSimOption::GetInstance();


