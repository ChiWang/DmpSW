/*=====================================================================
 *   File:   DmpEvtBgoRaw.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  16/12/2013   11:33:40
=====================================================================*/

#include <iostream>

#include "DmpEvtHeader.hh"
#include "DmpEvtBgoRaw.hh"

ClassImp(DmpEvtBgoRaw)

//------------------------------------------------------------------------------
DmpEvtBgoRaw::DmpEvtBgoRaw()
{}

//------------------------------------------------------------------------------
DmpEvtBgoRaw::~DmpEvtBgoRaw()
{}

//------------------------------------------------------------------------------
void DmpEvtBgoRaw::Reset(){
  fMode = kMixed;
  fLBSDCollection.clear();
  fADCCollection.clear();
}

//------------------------------------------------------------------------------
void DmpEvtBgoRaw::PrintEvent() const{
  std::cout<<"--->  Bgo:\tEvent ID = "<<fHeader->GetEventID()<<std::endl;
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
double  DmpEvtBgoRaw::GetSignal(Int_t id){
  Int_t iSignal=-1;
  for (Int_t i=0; i<fADCCollection.size();++i) {
    if (fLBSDCollection[i] == id) {
      iSignal = i;
      break;
    }
  }
  if (iSignal == -1) {
    return -2000;
  }
  return fADCCollection[iSignal];
}

//------------------------------------------------------------------------------
void DmpEvtBgoRaw::SetSignal(Int_t LBSD_ID,Double_t ADC){
  fLBSDCollection.push_back(LBSD_ID);
  fADCCollection.push_back(ADC);
}

