/*
 *  $Id: DmpSimSvcOption.cc, 2014-04-10 21:09:06 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/03/2014
*/

#include "DmpSimSvcOption.h"
#include "DmpSimSvcDataMgr.h"

//-------------------------------------------------------------------
DmpSimSvcOption::DmpSimSvcOption()
 :DmpVOptionSvc("DmpSimSvcOption")
{
  for(short i=0;i<DmpDetector::gSubDetNo + 1;++i){
    fGdmlPath[i]="default";
  }
  fOffset[DmpDetector::kPsd] = -33.4;
  fOffset[DmpDetector::kStk] = 0;
  fOffset[DmpDetector::kBgo] = 200;
  fOffset[DmpDetector::kNud] = 0;
}

//-------------------------------------------------------------------
DmpSimSvcOption::~DmpSimSvcOption(){
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
void DmpSimSvcOption::Set(const std::string &type,DmpDetector::DmpEDetectorID id, const std::string &argv){
  if(type == "gdmlPath"){
    fGdmlPath[id] = argv;
  }else if(type == "offset"){
    fOffset[id] = boost::lexical_cast<float>(argv);
  }else if(type == "outDataPath"){
    gSimDataMgr->SetOutDataPath(argv);
  }else if(type == "outDataNote"){
    gSimDataMgr->AppendDataNote(argv);
  }
}


//-------------------------------------------------------------------
DmpSimSvcOption *gSimOpt = DmpSimSvcOption::GetInstance();


