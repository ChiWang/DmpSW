/*
 *  $Id: DmpRdcLog.cc, 2014-04-02 10:58:35 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#include <iostream>

#include "DmpRdcLog.h"
#include "DmpRdcDataManager.h"
#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"

//-------------------------------------------------------------------
void DmpRdcLog::StatusLog(const short &x) const {
  static bool prepareForFirstIn = true;
  if(x == 0 && prepareForFirstIn){     // in convert function
    std::cout<<"\tfrom "<<gDataMgr->gInFile->tellg();
    prepareForFirstIn = false;
  }else if(x == 1){     // out convert function, not output data length
    std::cout<<" to "<<gDataMgr->gInFile->tellg()<<std::endl;
    prepareForFirstIn = true;
  }else if(x > 1){      // out convert function, output data length
    std::cout<<" to "<<gDataMgr->gInFile->tellg()<<"\t---> "<<x<<std::endl;
    prepareForFirstIn = true;
  }else if(x == -1){
    std::cout<<"\tError: not find 0xeb\t";
    PrintLocation();
    prepareForFirstIn = true;
  }else if(x == -2){
    std::cout<<"\tError: not find 0x90\t";
    PrintLocation();
    prepareForFirstIn = true;
  }else if(x == -3){
    std::cout<<"\tError: trigger not match\t";
    PrintLocation();
    prepareForFirstIn = true;
  }else if(x == -4){
    std::cout<<"\tError: run mode not match\t";
    PrintLocation();
    prepareForFirstIn = true;
  }
}

//-------------------------------------------------------------------
void DmpRdcLog::PrintLocation() const{
  static short tmp = 0;
  static DmpEvtHeader *evtHeader = gDataMgr->GetRawEvent()->GetEventHeader();
  std::cout<<"Location: ";
  for(short i=0;i<5;++i){
    gDataMgr->gInFile->read((char*)(&tmp),1);
    std::cout<<" "<<std::hex<<tmp<<std::dec;
  }
  std::cout<<"\t";
  evtHeader->PrintTime();
}


//-------------------------------------------------------------------
DmpRdcLog *gRdcLog = DmpRdcLog::GetInstance();


