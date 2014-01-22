
#include "DmpEvtStkRaw.hh"

ClassImp(DmpEvtStkRaw)

//------------------------------------------------------------------------------
DmpEvtStkRaw::DmpEvtStkRaw()
{}

//------------------------------------------------------------------------------
DmpEvtStkRaw::~DmpEvtStkRaw()
{}

//------------------------------------------------------------------------------
void DmpEvtStkRaw::Reset(){
  fMode = kMixed;
  fADCCollection.clear();
}

//------------------------------------------------------------------------------
void DmpEvtStkRaw::PrintEvent() const {

}

//------------------------------------------------------------------------------
void DmpEvtStkRaw::SetSignal(Float_t ADC){
}


