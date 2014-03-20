/*
 *  $Id: DmpEvtHeader.cc, 2014-03-20 20:00:00 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/ 

#include <iostream>

#include "DmpEvtHeader.h"

ClassImp(DmpEvtHeader)

//-------------------------------------------------------------------
DmpEvtHeader::DmpEvtHeader()
 :fEventID(-1),
  fPdgCode(0),
  fTrgPsd(0),
  fTrgStk(0),
  fTrgBgo(0),
  fTrgNud(0),
  fModePsd(DmpDetector::kCompress),
  fModeStk(DmpDetector::kCompress),
  fModeBgo(DmpDetector::kCompress),
  fModeNud(DmpDetector::kCompress)
{
}

//-------------------------------------------------------------------
DmpEvtHeader::~DmpEvtHeader(){
}

//-------------------------------------------------------------------
void DmpEvtHeader::PrintTime() const{
 //*  use cerr instead of cout, since most situation while calling ShowTime() is just after a cerr.
 //*  So, if we use cout in this function, then the output file will not match the file of the last cerr information in.
 std::cout<<"Time:\t";
 for(short i=0;i<GetTimeSize();++i){
   std::cout<<" "<<std::hex<<fTime[i];
 }
 std::cout<<std::dec<<std::endl;
}

//-------------------------------------------------------------------
void DmpEvtHeader::SetTrigger(const DmpDetector::DmpEDetectorID &id,const short &t){
  if(id == DmpDetector::kPsd){
    fTrgPsd = t;
  }else if(id == DmpDetector::kStk){
    fTrgStk = t;
  }else if(id == DmpDetector::kBgo){
    fTrgBgo = t;
  }else if(id == DmpDetector::kNud){
    fTrgNud = t;
  }
}

//-------------------------------------------------------------------
short DmpEvtHeader::GetTrigger(const DmpDetector::DmpEDetectorID &id) const {
  if(id == DmpDetector::kPsd)   return fTrgPsd;
  if(id == DmpDetector::kStk)   return fTrgStk;
  if(id == DmpDetector::kBgo)   return fTrgBgo;
  if(id == DmpDetector::kNud)   return fTrgNud;
}

//-------------------------------------------------------------------
void DmpEvtHeader::SetRunMode(const DmpDetector::DmpEDetectorID &id,const short &m){
  if(id == DmpDetector::kPsd){
    fModePsd = (DmpDetector::DmpERunMode)(m-1);
  }else if(id == DmpDetector::kStk){
    fModeStk = (DmpDetector::DmpERunMode)m;
  }else if(id == DmpDetector::kBgo){
    fModeBgo = (DmpDetector::DmpERunMode)m;
  }else if(id == DmpDetector::kNud){
    fModeNud = (DmpDetector::DmpERunMode)(m-2);
  }
}

//-------------------------------------------------------------------
DmpDetector::DmpERunMode DmpEvtHeader::GetRunMode(const DmpDetector::DmpEDetectorID &id) const{
  if(id == DmpDetector::kPsd)   return fModePsd;
  if(id == DmpDetector::kStk)   return fModeStk;
  if(id == DmpDetector::kBgo)   return fModeBgo;
  if(id == DmpDetector::kNud)   return fModeNud;
}

