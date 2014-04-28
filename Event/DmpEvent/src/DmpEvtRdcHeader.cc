/*
 *  $Id: DmpEvtRdcHeader.cc, 2014-04-28 09:37:38 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 28/04/2014
*/

#include <iostream>

#include "DmpEvtRdcHeader.h"

ClassImp(DmpRdcHeaderSubDet)
ClassImp(DmpEvtRdcHeader)

//-------------------------------------------------------------------
DmpRdcHeaderSubDet::DmpRdcHeaderSubDet()
 :fTrigger(-1),
  fRunMode(DmpDetector::kUnknow),
  fNFee(1)
{
  fSubStatus.push_back(0);
}

//-------------------------------------------------------------------
DmpRdcHeaderSubDet::DmpRdcHeaderSubDet(const short &nFee)
 :fTrigger(-1),
  fRunMode(DmpDetector::kUnknow),
  fNFee(nFee)
{
  fSubStatus.push_back(0);
}

//-------------------------------------------------------------------
DmpRdcHeaderSubDet::~DmpRdcHeaderSubDet(){

}

//-------------------------------------------------------------------
bool DmpRdcHeaderSubDet::IsGoodEvent() const {
  if(fSubStatus.size() == 1 && fSubStatus[0] == 0){
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
void DmpRdcHeaderSubDet::Reset(){
  fTrigger = -1;
  fRunMode = DmpDetector::kUnknow;
  fSubStatus.resize(1);
  fSubStatus[0] = 0;
}

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
  fBgo = new DmpRdcHeaderSubDet(16);
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
void DmpEvtRdcHeader::SetTrigger(const DmpDetector::DmpEDetectorID &id, const short &v){
  switch (id){
    case DmpDetector::kPsd:
      fPsd->SetTrigger(v);
      break;
    case DmpDetector::kStk:
      fStk->SetTrigger(v);
      break;
    case DmpDetector::kBgo:
      fBgo->SetTrigger(v);
      break;
    case DmpDetector::kNud:
      fNud->SetTrigger(v);
      break;
  }
}

//-------------------------------------------------------------------
short DmpEvtRdcHeader::GetTrigger(const DmpDetector::DmpEDetectorID &id) const {
  switch (id){
    case DmpDetector::kPsd:
       return fPsd->Trigger();
    case DmpDetector::kStk:
       return fStk->Trigger();
    case DmpDetector::kBgo:
       return fBgo->Trigger();
    case DmpDetector::kNud:
       return fNud->Trigger();
  }
}

//-------------------------------------------------------------------
void DmpEvtRdcHeader::SetRunMode(const DmpDetector::DmpEDetectorID &id, const  short &m){
  switch (id){
    case DmpDetector::kPsd:
       fPsd->SetRunMode((DmpDetector::DmpERunMode)m);
       break;
    case DmpDetector::kStk:
       fStk->SetRunMode((DmpDetector::DmpERunMode)m);
       break;
    case DmpDetector::kBgo:
       fBgo->SetRunMode((DmpDetector::DmpERunMode)m);
       break;
    case DmpDetector::kNud:
       fNud->SetRunMode((DmpDetector::DmpERunMode)m);
       break;
  }
}

//-------------------------------------------------------------------
DmpDetector::DmpERunMode DmpEvtRdcHeader::GetRunMode(const DmpDetector::DmpEDetectorID &id) const {
  switch (id){
    case DmpDetector::kPsd:
       return fPsd->RunMode();
    case DmpDetector::kStk:
       return fStk->RunMode();
    case DmpDetector::kBgo:
       return fBgo->RunMode();
    case DmpDetector::kNud:
       return fNud->RunMode();
  }
}

//-------------------------------------------------------------------
DmpRdcHeaderSubDet* DmpEvtRdcHeader::GetDetector(const DmpDetector::DmpEDetectorID &id) const {
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

