/*=====================================================================
 *   File:   DmpEvtPsdRaw.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  15/12/2013   21:07:20
=====================================================================*/

#include <iostream>

#include "DmpEvtHeader.hh"
#include "DmpEvtPsdRaw.hh"

ClassImp(DmpEvtPsdRaw)

//------------------------------------------------------------------------------
DmpEvtPsdRaw::DmpEvtPsdRaw()
{}

//------------------------------------------------------------------------------
DmpEvtPsdRaw::~DmpEvtPsdRaw()
{}

//------------------------------------------------------------------------------
void DmpEvtPsdRaw::Reset(){
  fMode = kMixed;
  fLBSD_ID.clear();
  fADC.clear();
}

//------------------------------------------------------------------------------
void DmpEvtPsdRaw::PrintEvent() const{
  std::cout<<"--->  Psd:\tEvent ID = "<<fHeader->GetEventID()<<std::endl;
  std::cout<<"Layer | Bar | Side | Dy | ADC"<<std::endl;
  static Int_t id, nSignal;
  static Short_t layer, bar, side, dy;
  nSignal = fADC.size();
  for (Int_t i=0;i<nSignal;++i) {
    id = fLBSD_ID[i];
    layer = id/10000; id = id%10000;
    bar = id/100;     id = id%100;
    side = id/10;     dy = id%10;
    std::cout<<std::dec<<layer<<"\t"<<bar<<"\t"<<side<<"\t"<<dy<<"\t"<<fADC[i]<<std::endl;
  }
}

//------------------------------------------------------------------------------
void  DmpEvtPsdRaw::PrintEvent(Short_t layer,Short_t bar,Short_t side,Short_t dy){
  static Int_t id, nSignal, iSignal;
  nSignal = fADC.size();
  id = CreateLBSDID(layer,bar,side,dy);
  for (Int_t i=0; i<nSignal;++i) {
    if (fLBSD_ID[i] == id) {
      iSignal = i;
      break;
    }
  }
  std::cout<<"--->  Psd:\tEvent ID = "<<fHeader->GetEventID()<<std::endl;
  std::cout<<"Layer | Bar | Side | Dy | ADC"<<std::endl;
  std::cout<<layer<<"\t"<<bar<<"\t"<<side<<"\t"<<dy<<"\t"<<fADC[iSignal]<<std::endl;
}

//------------------------------------------------------------------------------
void DmpEvtPsdRaw::SetSignal(Int_t LBSD_ID,Double_t ADC){
  fLBSD_ID.push_back(LBSD_ID);
  fADC.push_back(ADC);
}

//------------------------------------------------------------------------------
Int_t DmpEvtPsdRaw::CreateLBSDID(Short_t L,Short_t B,Short_t S,Short_t D){
  return L*10000+B*100+S*10+D;
}

