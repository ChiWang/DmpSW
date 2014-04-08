/*
 *  $Id: DmpRdcCnctPath.cc, 2014-04-07 21:13:22 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#include "DmpRdcOption.h"

//-------------------------------------------------------------------
DmpRdcOption::DmpRdcOption(const std::string &n)
 :DmpVRunTimeOptionSvc(n)
{
  for(short i=0;i<DmpDetector::gSubDetNo;++i){
    fConnectorPath[i]="default";
  }
}


//-------------------------------------------------------------------
DmpRdcOption::~DmpRdcOption(){
}

//-------------------------------------------------------------------
void DmpRdcOption::Set(const std::string &type, DmpDetector::DmpEDetectorID id, const std::string &argv){
  switch(type){
    case "connector/path":
      fConnectorPath[id] = argv;
      break;
  }
}


