/*
 *  $Id: DmpEvtRdcHeader.cc, 2014-07-28 10:01:33 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 28/04/2014
*/

#include "DmpEvtHeader.h"
#include "DmpLog.h"

ClassImp(DmpEvtHeader)

//-------------------------------------------------------------------
DmpEvtHeader::DmpEvtHeader()
 :fTrigger(-1),
{
  for(short i=0;i<8;++i){
    fHexTime[i] = 0;
  }
}

//-------------------------------------------------------------------
DmpEvtHeader::~DmpEvtHeader(){
}

//-------------------------------------------------------------------
void DmpEvtHeader::Reset(){
  fHexTime.clear();
//-------------------------------------------------------------------
  for(std::map<short,std::map<short,short> >::iterator it=fFeeTrigger.begin(); it != fFeeTrigger.end();++it){
    it->second.clear();
  }
  fFeeTrigger.clear();
//-------------------------------------------------------------------
  for(std::map<short,std::map<short,short> >::iterator it=fFeeRunMode.begin(); it != fFeeRunMode.end();++it){
    it->second.clear();
  }
  fFeeRunMode.clear();
//-------------------------------------------------------------------
  for(std::map<short,std::map<short,short> >::iterator it=fErrorTag.begin(); it != fErrorTag.end();++it){
    it->second.clear();
  }
  fErrorTag.clear();
}

//-------------------------------------------------------------------
void DmpEvtHeader::SetFeeErrorTag(DmpDetectorID::Type id,const short &FeeID,const DmpDataError::Type &type){
  if(fErrorTag.find(id) == fErrorTag.end()){
    std::map<short,short>   newmap;
    fErrorTag.insert(std::make_pair(id,newmap));
  }
  if(fErrorTag[id].find(FeeID) == fErrorTag[id].end()){
    fErrorTag[id].insert(std::make_pair(FeeID,type));
  }else{
// *
// *  TODO:  one Fee, 2 type errors
// *
    DmpLogError<<"\tfind the Fee id("<<FeeID<<") two times in this event..";
  }
  switch(type){
    case DmpDataError::NotFind_0xeb:
      DmpLogError<<"\tnot find 0xeb\t";
      break;
    case DmpDataError::NotFind_0x90:
      DmpLogError<<"\tnot find 0x90\t";
      break;
    case DmpDataError::DataLength_Wrong:
      DmpLogError<<"\tdata length float\t";
      break;
    case DmpDataError::CRC_Wrong:
      DmpLogError<<"\tCRC wrong\t";
      break;
  }
  PrintTime();
}

//-------------------------------------------------------------------
void DmpEvtHeader::SetFeeStatus(DmpDetectorID::Type id,const short &FeeID,short trigger,short runMode){
  if(fFeeTrigger.find(id) == fFeeTrigger.end()){
    std::map<short,short>  newmap;
    fFeeTrigger.insert(std::make_pair(id,newmap));
  }
  if(fFeeTrigger[id].find(FeeID) == fFeeTrigger[id].end()){
    fFeeTrigger[id].insert(std::make_pair(FeeID,trigger));
  }else{
    DmpLogError<<"Find Fee 0x"<<FeeID<<" two times..."<<DmpLogEndl;
  }
    //-------------------------------------------------------------------
  if(fFeeRunMode.find(id) == fFeeRunMode.end()){
    std::map<short, short> newmap;
    fFeeRunMode.insert(std::make_pair(id,newmap));
  }
  if(fFeeRunMode[id].find(FeeID) == fFeeRunMode[id].end()){
    fFeeRunMode[id].insert(std::make_pair(FeeID,runMode));
  }else{
    DmpLogError<<"Find Fee 0x"<<FeeID<<" two times..."<<DmpLogEndl;
  }
}

//-------------------------------------------------------------------
bool DmpEvtHeader::IsGoodEvent() const{
  bool v = true;
//-------------------------------------------------------------------
// no fee errors
  if(0 != fErrorTag.size()){
    v = false;
  }
//-------------------------------------------------------------------
// all sub-det triggers match
  v = TriggersMatch();
  return v;
}

//-------------------------------------------------------------------
short DmpEvtHeader::GetTrigger(DmpDetectorID::Type id) const{
  short v = -1;
  if(DmpDetectorID::kWhole == id){
    v = fTrigger;
  }else{
    if(fFeeTrigger.find(id) == fFeeTrigger.end()){
      DmpLogError<<"No detector ID "<<id<<DmpLogEndl;
      v = -1;
    }else{
      v = fFeeTrigger.find(id)->second.begin()->second;
      for(std::map<short,short>::const_iterator it=fFeeTrigger.find(id)->second.begin();it!=fFeeTrigger.find(id)->second.end();++it){
        if(it->second != v){
          DmpLogError<<"triggers not match"<<DmpLogEndl;
          v = -1;
          break;
        }
      }
    }
  }
  return v;
}

//-------------------------------------------------------------------
void DmpEvtHeader::PrintTime(const std::string &type)const{
  if("hex" == type){
    std::cout<<"Time: ";
    for(std::size_t i=0;i<fHexTime.size();++i){
      std::cout<<" "<<std::hex<<fHexTime[i];
    }
    std::cout<<std::dec<<std::endl;
  }else{
// *
// *  TODO: 
// *
  }
}

//-------------------------------------------------------------------
bool DmpEvtHeader::TriggersMatch(DmpDetectorID::Type id) const{
  if(DmpDetectorID::kWhole != id){
    if(fFeeTrigger.find(id) != fFeeTrigger.end()){
      for(std::map<short,short>::const_iterator it = fFeeTrigger.find(id).begin();it != fFeeTrigger[id].end();++it){
        if(it->second != fFeeTrigger.find(id).begin()->second){
          return false;
        }
      }
    }else{
      DmpLogError<<"not detector in this event. detector id =  "<<id<<DmpLogEndl;
    }
  }else{
    for(std::map<short,std::map<short,short> >::const_iterator it=fFeeTrigger.begin(); it!=fFeeTrigger.end();++it){
      if(it->second.begin()->second != fTrigger){
        return false;
      }
    }
  }
  return true;
}

