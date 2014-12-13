/*
 *  $Id: DmpEvtHeader.cc, 2014-08-05 14:20:44 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 28/04/2014
*/

#include "DmpEvtHeader.h"
#include "DmpLog.h"

ClassImp(DmpEvtHeader)

//-------------------------------------------------------------------
DmpEvtHeader::DmpEvtHeader()
 :fPackageID(-1)
{
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
  for(std::map<short,std::map<short,short> >::iterator it=fFeeErrorTag.begin(); it != fFeeErrorTag.end();++it){
    it->second.clear();
  }
  fFeeErrorTag.clear();
}

//-------------------------------------------------------------------
void DmpEvtHeader::AddFeeErrorTag(DmpDetectorID::Type id,const short &FeeID,const DmpDataError::Type &type){
  if(fFeeErrorTag.find(id) == fFeeErrorTag.end()){
    std::map<short,short>   newmap;
    fFeeErrorTag.insert(std::make_pair(id,newmap));
  }
  if(fFeeErrorTag[id].find(FeeID) == fFeeErrorTag[id].end()){
    fFeeErrorTag[id].insert(std::make_pair(FeeID,type));
  }else{
// *
// *  TODO:  one Fee, 2 type errors??
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
short DmpEvtHeader::GetTrigger(DmpDetectorID::Type id) const{
  short v = -1;
  if(TriggersMatch(id)){
    if(DmpDetectorID::kWhole == id){
      v = fPackageID;
    }else{
      v = fFeeTrigger.find(id)->second.begin()->second;
    }
  }
  return v;
}

//-------------------------------------------------------------------
bool DmpEvtHeader::TriggersMatch(DmpDetectorID::Type id) const{
  if(DmpDetectorID::kWhole != id){
    if(fFeeTrigger.find(id) != fFeeTrigger.end()){
      for(std::map<short,short>::const_iterator it = fFeeTrigger.find(id)->second.begin();it != fFeeTrigger.find(id)->second.end();++it){
        if(it->second != fFeeTrigger.find(id)->second.begin()->second){
          return false;
        }
      }
    }else{
      DmpLogError<<"not detector in this event. detector id =  "<<id<<DmpLogEndl;
      return false;
    }
  }else{
    for(std::map<short,std::map<short,short> >::const_iterator it=fFeeTrigger.begin(); it!=fFeeTrigger.end();++it){
      if(it->second.begin()->second != fPackageID){
        return false;
      }
    }
  }
  return true;
} 

bool DmpEvtHeader::RunModesMatch(DmpDetectorID::Type id)const{
  if(fFeeRunMode.find(id) != fFeeRunMode.end()){
    for(std::map<short,short>::const_iterator it = fFeeRunMode.find(id)->second.begin();it != fFeeRunMode.find(id)->second.end();++it){
      if(it->second != fFeeRunMode.find(id)->second.begin()->second){
        return false;
      }
    }
  }else{
    DmpLogError<<"not detector in this event. detector id =  "<<id<<DmpLogEndl;
    return false;
  }
}

//-------------------------------------------------------------------
bool DmpEvtHeader::IsGoodEvent() const{
  bool v = true;
//-------------------------------------------------------------------
// no fee errors
  if(0 != fFeeErrorTag.size()){
    v = false;
  }
//-------------------------------------------------------------------
// all sub-det triggers match
  v = TriggersMatch();
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

