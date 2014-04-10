/*
 *  $Id: DmpRdcOption.cc, 2014-04-08 15:19:43 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#include "DmpRdcOption.h"
#include "DmpRdcDataManager.h"

//-------------------------------------------------------------------
DmpRdcOption::DmpRdcOption(){
  for(short i=0;i<DmpDetector::gSubDetNo;++i){
    fConnectorPath[i]="default";
  }
}

//-------------------------------------------------------------------
DmpRdcOption::~DmpRdcOption(){
}

//-------------------------------------------------------------------
void DmpRdcOption::Set(const std::string &type, DmpDetector::DmpEDetectorID id, const std::string &argv){
  if(type == "cnctPath"){
    fConnectorPath[id] = argv;
  }else if(type == "outDataPath"){
    gRdcDataMgr->SetOutDataPath(argv);  
  }else if(type == "outDataNote"){
    gRdcDataMgr->AppendDataNote(argv);  
  }
}

//-------------------------------------------------------------------
std::string DmpRdcOption::Get(const std::string &type){
  if(type == "outDataName"){
    return gRdcDataMgr->GetOutDataName();
  }
}

//-------------------------------------------------------------------
DmpRdcOption *gRdcOpt = DmpRdcOption::GetInstance();


