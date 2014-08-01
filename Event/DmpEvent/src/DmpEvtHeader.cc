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
void DmpEvtRdcHeader::SetErrorLog(DmpDetectorID::Type id,const short &FeeID,const DataErrorType &type){
  fStatus.insert(std::make_pair(id*100+FeeID,type));
  switch(type){
    case NotFind_0xeb:
      DmpLogError<<"\tnot find 0xeb\t";
      break;
    case NotFind_0x90:
      DmpLogError<<"\tnot find 0x90\t";
      break;
    case Wrong_DataLength:
      DmpLogError<<"\tdata length float\t";
      break;
    //case NotMatch_RunMode:
    //  DmpLogError<<"\trun mode not match\t";
    //  break;
    case NotMatch_Trigger:
      DmpLogError<<"\ttrigger not match\t";
      break;
    case Wrong_CRC:
      DmpLogError<<"\tCRC wrong\t";
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
void DmpEvtRdcHeader::SetRunMode(DmpDetectorID::Type id, short v){
  if(fRunMode.find(id) == fRunMode.end()){
    fRunMode[id] = v;
    return;
  }else{
    if(fRunMode[id] != v){
      if(fRunMode[id] > 0){
        fRunMode[id] = 0 - (fRunMode[id]*10 + v);
      }else{
        fRunMode[id] = fRunMode[id]*10 - v;
      }
    }
  }
}

//-------------------------------------------------------------------
void DmpEvtRdcHeader::Reset(){
  fSec = 0;
  fMillisec = 0;
  fTrigger.clear();
  fRunMode.clear();
  fStatus.clear();
  fStatus.insert(std::make_pair(DmpDetectorID::kWhole,0));
}

//-------------------------------------------------------------------
bool DmpEvtRdcHeader::IsGoodEvent() const{
  if(0 == fStatus.find(DmpDetectorID::kWhole)->second){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
short DmpEvtRdcHeader::GetTrigger(DmpDetectorID::Type id) const{
  if(fTrigger.find(id) == fTrigger.end()){
    DmpLogError<<"No detector ID "<<id<<DmpLogEndl;
    return -1;
  }
  if(id == DmpDetectorID::kWhole){
    for(std::map<short,short>::const_iterator it=fTrigger.begin();it!=fTrigger.end();++it){
      if(it->second != fTrigger.find(id)->second){
        DmpLogError<<"triggers not match"<<DmpLogEndl;
        return -1;
      }
    }
  }
  return fTrigger.find(id)->second;
}

