/*
 *  $Id: DmpEvtRdcHeader.cc, 2014-05-29 21:41:42 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 28/04/2014
*/

#include "DmpEvtRdcHeader.h"
#include "DmpLog.h"

ClassImp(DmpEvtRdcHeader)

//-------------------------------------------------------------------
DmpEvtRdcHeader::DmpEvtRdcHeader()
 :fSec(0),
  fMillisec(0)
{
  for(short i=0;i<8;++i){
    fTime[i] = 0;
  }
}

//-------------------------------------------------------------------
DmpEvtRdcHeader::~DmpEvtRdcHeader(){
}

//-------------------------------------------------------------------
void DmpEvtRdcHeader::SetErrorLog(DmpDetector::DmpEDetectorID id,const short &FeeID,const DataErrorType &type){
  fStatus.push_back(id*1000 + FeeID*10 + type);
  switch(type){
    case NotFind_0xeb:
      LogError<<"\tnot find 0xeb\t";
      break;
    case NotFind_0x90:
      LogError<<"\tnot find 0x90\t";
      break;
    case Wrong_DataLength:
      LogError<<"\tdata length float\t";
      break;
    case NotMatch_RunMode:
      LogError<<"\trun mode not match\t";
      break;
    case NotMatch_Trigger:
      LogError<<"\ttrigger not match\t";
      break;
    case Wrong_CRC:
      LogError<<"\tCRC wrong\t";
      break;
  }
  std::cout<<"Time: ";
  for(std::size_t i=0;i<8;++i){
    std::cout<<" "<<std::hex<<fTime[i];
  }
  std::cout<<std::dec<<std::endl;
}

//-------------------------------------------------------------------
void DmpEvtRdcHeader::SetTime(const short &n,const short &v){
  fTime[n]=v;
  if(n < 6){
    fSec = fSec*256 + v;
  }else{
    fMillisec = fMillisec*256 + v;
  }
}

//-------------------------------------------------------------------
void DmpEvtRdcHeader::SetTrigger(DmpDetector::DmpEDetectorID id, const short &v){
  fTrigger.push_back(id*1000 + v);
}

//-------------------------------------------------------------------
void DmpEvtRdcHeader::SetRunMode(DmpDetector::DmpEDetectorID id, const short &v){
  fRunMode.push_back(id*1000 + v);
}

//-------------------------------------------------------------------
void DmpEvtRdcHeader::Reset(){
  fSec = 0;
  fMillisec = 0;
  fTrigger.resize(0);
  fRunMode.resize(0);
  fStatus.resize(1,0);
}

//-------------------------------------------------------------------
short DmpEvtRdcHeader::GetTrigger(DmpDetector::DmpEDetectorID id) const{
  short trg = fTrigger[0]%1000;
  if(id == DmpDetector::kWhole){
    for(short i=1;i<fTrigger.size();++i){
      if(trg != fTrigger[i]%1000){
        LogError<<"triggers not match"<<std::endl;
        return -1;
      }
    }
  }else{
    for(short i=0;i<fTrigger.size();++i){
      if(id == fTrigger[i]/1000){
        trg = fTrigger[i]%1000;
        break;
      }
    }
  }
  return trg;
}

//-------------------------------------------------------------------
short DmpEvtRdcHeader::GetRunMode(DmpDetector::DmpEDetectorID id) const{
  for(short i=0;i<fRunMode.size();++i){
    if(id == fRunMode[i]/1000){
      return fRunMode[i]%1000;
    }
  }
  return -1;
}


