/*
 *  $Id: DmpRdcLog.cc, 2014-04-06 20:37:24 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#include <iostream>

#include "DmpRdcLog.h"
#include "DmpEvtHeader.h"
#include "DmpRdcDataManager.h"

//-------------------------------------------------------------------
void DmpRdcLog::StatusLog(const short &x) const {
  static bool prepareForFirstIn = true;
  if(x > 1){    // out convert (subDet)
    std::cout<<" to "<<gDataMgr->gInDataStream.tellg()<<"\t---> "<<x<<std::endl;
    prepareForFirstIn = true;
  }else{
    switch(x){
    case 1:     // out convert (header)
      std::cout<<" to "<<gDataMgr->gInDataStream.tellg()<<std::endl;
      prepareForFirstIn = true;
      break;
    case 0:     // start convert
      if(prepareForFirstIn){
        std::cout<<"\tfrom "<<gDataMgr->gInDataStream.tellg();
        prepareForFirstIn = false;
      }
      break;
    case -1:
      std::cout<<"\tError: not find 0xeb\t";
      PrintLocation();
      prepareForFirstIn = true;
      break;
    case -2:
      std::cout<<"\tError: not find 0x90\t";
      PrintLocation();
      prepareForFirstIn = true;
      break;
    case -3:
      std::cout<<"\tError: trigger not match\t";
      PrintLocation();
      prepareForFirstIn = true;
      break;
    case -4:
      std::cout<<"\tError: run mode not match\t";
      PrintLocation();
      prepareForFirstIn = true;
      break;
    }
  }
}

//-------------------------------------------------------------------
void DmpRdcLog::PrintLocation() const{
  static short tmp = 0;
  static DmpEvtHeader *evtHeader = gDataMgr->GetEventHeader();
  std::cout<<"Location: ";
  for(short i=0;i<5;++i){
    gDataMgr->gInDataStream.read((char*)(&tmp),1);
    std::cout<<" "<<std::hex<<tmp<<std::dec;
  }
  std::cout<<"\t";
  evtHeader->PrintTime();
}

//-------------------------------------------------------------------
DmpRdcLog *gRdcLog = DmpRdcLog::GetInstance();


