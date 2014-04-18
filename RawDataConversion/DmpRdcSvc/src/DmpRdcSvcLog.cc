/*
 *  $Id: DmpRdcSvcLog.cc, 2014-04-10 21:26:07 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/04/2014
*/

#include <iostream>

#include "DmpServiceManager.h"
#include "DmpRdcSvcDataMgr.h"
#include "DmpRdcSvcLog.h"
#include "DmpEvtHeader.h"

//-------------------------------------------------------------------
DmpRdcSvcLog::DmpRdcSvcLog()
 :DmpVSvc("Rdc/Log"),
  fFile(0),
  fEvtHeader(0)
{
}

//-------------------------------------------------------------------
DmpRdcSvcLog::~DmpRdcSvcLog(){
}

//-------------------------------------------------------------------
bool DmpRdcSvcLog::Initialize(){
  fFile = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->InFileStream();
  fEvtHeader = ((DmpRdcSvcDataMgr*)gDmpSvcMgr->Get("Rdc/DataMgr"))->GetEventHeader();
  return true;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
void DmpRdcSvcLog::Set(const std::string &type, const std::string &argv){
  if(type == "Log/Level"){
    fLevel = boost::lexical_cast<short>(argv);
  }
}

//-------------------------------------------------------------------
void DmpRdcSvcLog::Type(const short &x) const {
/*
 *  fLevel == 0
 *      print nothing
 *
 *  fLevel == 1
 *      print Error
 *
 *  fLevel > 1
 *      print all
 *
 */
  if(fLevel == 0){
    return;
  }else if(fLevel == 1 && x >= 0){
    return;
  }
  static bool prepareForFirstIn = true;
  if(x > 1){    // out convert (subDet)
    std::cout<<" to "<<fFile->tellg()<<"\t---> "<<x<<std::endl;
    prepareForFirstIn = true;
  }else{
    switch(x){
    case 1:     // out convert (header)
      std::cout<<" to "<<fFile->tellg()<<std::endl;
      prepareForFirstIn = true;
      break;
    case 0:     // start convert
      if(prepareForFirstIn){
        std::cout<<"\tfrom "<<fFile->tellg();
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
  std::cout<<"Location: ";
  for(short i=0;i<5;++i){
    fFile->read((char*)(&tmp),1);
    std::cout<<" "<<std::hex<<tmp<<std::dec;
  }
  std::cout<<"\t";
  fEvtHeader->PrintTime();
}


