/*
 *  $Id: DmpRdcSvcLog.cc, 2014-04-10 21:26:07 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#include <iostream>

#include "DmpRdcSvcLog.h"
#include "DmpEvtHeader.h"
#include "DmpRdcSvcDataMgr.h"

//-------------------------------------------------------------------
void DmpRdcSvcLog::StatusLog(const short &x) const {
  static bool prepareForFirstIn = true;
  if(x > 1){    // out convert (subDet)
    std::cout<<" to "<<gRdcDataMgr->gInDataStream.tellg()<<"\t---> "<<x<<std::endl;
    prepareForFirstIn = true;
  }else{
    switch(x){
    case 1:     // out convert (header)
      std::cout<<" to "<<gRdcDataMgr->gInDataStream.tellg()<<std::endl;
      prepareForFirstIn = true;
      break;
    case 0:     // start convert
      if(prepareForFirstIn){
        std::cout<<"\tfrom "<<gRdcDataMgr->gInDataStream.tellg();
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
void DmpRdcSvcLog::PrintLocation() const{
  static short tmp = 0;
  static DmpEvtHeader *evtHeader = gRdcDataMgr->GetEventHeader();
  std::cout<<"Location: ";
  for(short i=0;i<5;++i){
    gRdcDataMgr->gInDataStream.read((char*)(&tmp),1);
    std::cout<<" "<<std::hex<<tmp<<std::dec;
  }
  std::cout<<"\t";
  evtHeader->PrintTime();
}

//-------------------------------------------------------------------
DmpRdcSvcLog *gRdcLog = DmpRdcSvcLog::GetInstance();


