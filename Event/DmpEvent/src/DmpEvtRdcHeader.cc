/*
 *  $Id: DmpEvtRdcHeader.cc, 2014-04-28 09:37:38 DAMPE $
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
bool DmpRdcHeaderSubDet::IsGoodEvent() const {
  if(fErrors.size() == 1 && fErrors[0] == 0){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
void DmpRdcHeaderSubDet::Reset(){
  fTrigger = -1;
  fRunMode = DmpDetector::kUnknow;
  fErrors.erase(fErrors.begin(),fErrors.end());
}

ClassImp(DmpEvtRdcHeader)
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
void DmpEvtRdcHeader::PrintTime()const{
  std::cout<<"Time: ";
  for(short i=0;i<8;++i){
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


