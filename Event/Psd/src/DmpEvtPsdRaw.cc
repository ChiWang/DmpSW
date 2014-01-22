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

#include "DmpEvtHeader.h"
#include "DmpEvtPsdRaw.h"

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
  fLBSDCollection.clear();
  fADCCollection.clear();
}

//------------------------------------------------------------------------------
void DmpEvtPsdRaw::PrintEvent() const{
  std::cout<<"--->  Psd:\tEvent ID = "<<fHeader->GetEventID()<<std::endl;
  std::cout<<"Layer | Bar | Side | Dy | ADC"<<std::endl;
  static Int_t id, nSignal;
  static Short_t layer, bar, side, dy;
  nSignal = fADCCollection.size();
  for (Int_t i=0;i<nSignal;++i) {
    id = fLBSDCollection[i];
    layer = id/10000; id = id%10000;
    bar = id/100;     id = id%100;
    side = id/10;     dy = id%10;
    std::cout<<std::dec<<layer<<"\t"<<bar<<"\t"<<side<<"\t"<<dy<<"\t"<<fADCCollection[i]<<std::endl;
  }
}

//------------------------------------------------------------------------------
void  DmpEvtPsdRaw::PrintEvent(Short_t layer,Short_t bar,Short_t side,Short_t dy){
  static Int_t id, nSignal, iSignal;
  nSignal = fADCCollection.size();
  id = CreateLBSDID(layer,bar,side,dy);
  for (Int_t i=0; i<nSignal;++i) {
    if (fLBSDCollection[i] == id) {
      iSignal = i;
      break;
    }
  }
  std::cout<<"--->  Psd:\tEvent ID = "<<fHeader->GetEventID()<<std::endl;
  std::cout<<"Layer | Bar | Side | Dy | ADC"<<std::endl;
  std::cout<<layer<<"\t"<<bar<<"\t"<<side<<"\t"<<dy<<"\t"<<fADCCollection[iSignal]<<std::endl;
}

//------------------------------------------------------------------------------
void DmpEvtPsdRaw::SetSignal(Int_t LBSD_ID,Double_t ADC){
  fLBSDCollection.push_back(LBSD_ID);
  fADCCollection.push_back(ADC);
}

//------------------------------------------------------------------------------
Int_t DmpEvtPsdRaw::CreateLBSDID(Short_t L,Short_t B,Short_t S,Short_t D){
  return L*10000+B*100+S*10+D;
}

