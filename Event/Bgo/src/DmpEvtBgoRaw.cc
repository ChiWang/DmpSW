/*=============================================================================
#       FileName :          DmpEvtBgoRaw.cc
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-16   11:00:27
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-03   20:04:22
=============================================================================*/

#include "DmpEvtHeader.hh"
#include "DmpEvtBgoRaw.hh"

ClassImp(DmpEvtBgoRaw)

DmpEvtBgoRaw::DmpEvtBgoRaw()
 :fNSignal(0)
{}

//______________________________________________________________________________
DmpEvtBgoRaw::~DmpEvtBgoRaw()
{}

//______________________________________________________________________________
void DmpEvtBgoRaw::Reset(){
  fMode = kMixed;
  fNSignal = 0;
  fLBSD_ID.clear();
  fADC.clear();
}

//______________________________________________________________________________
void DmpEvtBgoRaw::PrintEvent() const{
  std::cout<<"--->  Bgo:\tEvent ID = "<<fHeader->GetEventID()<<"\tSignal No.of dynode = "<<fNSignal<<std::endl;
  std::cout<<"Layer | Bar | Side | Dy | ADC"<<std::endl;
  static Int_t id;
  static Short_t layer, bar, side, dy;
  for (Int_t i=0;i<fNSignal;++i) {
    id = fLBSD_ID[i];
    layer = id/10000; id = id%10000;
    bar = id/100;     id = id%100;
    side = id/10;     dy = id%10;
    std::cout<<layer<<"\t"<<bar<<"\t"<<side<<"\t"<<dy<<"\t"<<fADC[i]<<std::endl;
  }
}


//______________________________________________________________________________
void  DmpEvtBgoRaw::PrintEvent(Short_t layer,Short_t bar,Short_t side,Short_t dy) const{
  static Int_t iSignal, id;
  id = CreateLBSDID(layer,bar,side,dy);
  for (Int_t i=0; i<fNSignal;++i) {
    if (fLBSD_ID[i] == id) {
      iSignal = i;
      break;
    }
  }
  std::cout<<"--->  Bgo:\tEvent ID = "<<fHeader->GetEventID()<<"\tSignal No.of dynode = "<<fNSignal<<std::endl;
  std::cout<<"Layer | Bar | Side | Dy | ADC"<<std::endl;
  std::cout<<layer<<"\t"<<bar<<"\t"<<side<<"\t"<<dy<<"\t"<<fADC[i]<<std::endl;
}

//______________________________________________________________________________
void DmpEvtBgoRaw::SetSignal(Short_t L,Short_t B,Short_t S,Short_t D,Double_t ADC){
  fLBSD_ID.push_back(CreateLBSDID(L,B,S,D));
  fADC.push_back(ADC);
  ++fNSignal;
}


//______________________________________________________________________________
Int_t DmpEvtBgoRaw::CreateLBSDID(Short_t L,Short_t B,Short_t S,Short_t D){
  return D+S*10+B*100+L*10000;
}

