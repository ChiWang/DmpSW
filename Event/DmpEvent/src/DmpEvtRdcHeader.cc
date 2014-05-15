/*
 *  $Id: DmpEvtRdcHeader.cc, 2014-05-15 22:39:41 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 28/04/2014
*/

#include <iostream>

#include "DmpEvtRdcHeader.h"

ClassImp(DmpRdcHeaderSubDet)

//-------------------------------------------------------------------
DmpRdcHeaderSubDet::DmpRdcHeaderSubDet()
 :fTrigger(-1),
  fRunMode(DmpDetector::kUnknow)
{
}

//-------------------------------------------------------------------
DmpRdcHeaderSubDet::~DmpRdcHeaderSubDet(){
}

//-------------------------------------------------------------------
void DmpRdcHeaderSubDet::SetErrorLog(const short &FeeID,const DataErrorType &type){
  fErrors.push_back(FeeID*10 + type);
  switch(type){
    case NotFind_0xeb:
      std::cout<<"\tError: not find 0xeb\t";
      break;
    case NotFind_0x90:
      std::cout<<"\tError: not find 0x90\t";
      break;
    case Wrong_DataLength:
      std::cout<<"\tError: data length float\t";
      break;
    case NotMatch_RunMode:
      std::cout<<"\tError: run mode not match\t";
      break;
    case NotMatch_Trigger:
      std::cout<<"\tError: trigger not match\t";
      break;
  }
  if(type != Good){
          DmpEvtRdcHeader::PrintTime();
  }
}

//-------------------------------------------------------------------
void DmpRdcHeaderSubDet::Reset(){
  fTrigger = -1;
  fRunMode = DmpDetector::kUnknow;
  std::cout<<"\nDEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"fErrors.size = "<<fErrors.size();
  for(short i=0;i<fErrors.size();++i){
    std::cout<<" fErrors["<<i<<"] = "<<fErrors[i];
  }
  fErrors.erase(fErrors.begin(),fErrors.end());
}

//-------------------------------------------------------------------
bool DmpRdcHeaderSubDet::IsGoodEvent() const {
  if(fErrors.size() == 1 && fErrors[0] == 0){
    return true;
  }
  return false;
}

ClassImp(DmpEvtRdcHeader)

//-------------------------------------------------------------------
short DmpEvtRdcHeader::fTime[8]={0};

//-------------------------------------------------------------------
DmpEvtRdcHeader::DmpEvtRdcHeader()
 :fSec(0),
  fMillisec(0),
  fTrigger(-1),
  fStatus(0),
  fPsd(0),
  fStk(0),
  fBgo(0),
  fNud(0)
{
  fPsd = new DmpRdcHeaderSubDet();
  fStk = new DmpRdcHeaderSubDet();
  fBgo = new DmpRdcHeaderSubDet();
  fNud = new DmpRdcHeaderSubDet();
}

//-------------------------------------------------------------------
DmpEvtRdcHeader::~DmpEvtRdcHeader(){
  delete fPsd;
  delete fStk;
  delete fBgo;
  delete fNud;
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
void DmpEvtRdcHeader::PrintTime(){
  std::cout<<"Time: ";
  for(std::size_t i=0;i<8;++i){
    std::cout<<" "<<std::hex<<fTime[i];
  }
  std::cout<<std::dec<<std::endl;
}

//-------------------------------------------------------------------
void DmpEvtRdcHeader::GenerateStatus(){
  static short nTrg[DmpDetector::gSubDetNo];
  nTrg[0] = fBgo->Trigger() - fPsd->Trigger();
  nTrg[1] = fBgo->Trigger() - fStk->Trigger();
  nTrg[2] = fBgo->Trigger() - fNud->Trigger();
  nTrg[3] = fBgo->Trigger() - fTrigger;
  for(std::size_t i=0;i<DmpDetector::gSubDetNo;++i){
    if(nTrg[i] == 0) continue;
    short v=1;
    for(std::size_t n=0;n<i;++n){
      v = v*2;
    }
    fStatus += v;
  }
}

//-------------------------------------------------------------------
void DmpEvtRdcHeader::Reset(){
  fSec = 0;
  fMillisec = 0;
  fTrigger = -1;
  fStatus = 0;
  fPsd->Reset();
  fStk->Reset();
  fBgo->Reset();
  fNud->Reset();
}

//-------------------------------------------------------------------
short DmpEvtRdcHeader::Trigger() const {
  if(fStatus>0){
    return -1;
  }
  return fTrigger;
}

//-------------------------------------------------------------------
DmpRdcHeaderSubDet* DmpEvtRdcHeader::Detector(const DmpDetector::DmpEDetectorID &id) const {
  switch (id){
    case DmpDetector::kPsd:
       return fPsd;
    case DmpDetector::kStk:
       return fStk;
    case DmpDetector::kBgo:
       return fBgo;
    case DmpDetector::kNud:
       return fNud;
  }
}

