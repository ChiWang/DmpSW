
#include "DmpEvtNudRaw.hh"

//______________________________________________________________________________
DmpEvtNudRaw::DmpEvtNudRaw()
{}

//______________________________________________________________________________
DmpEvtNudRaw::~DmpEvtNudRaw()
{}

//______________________________________________________________________________
void DmpEvtNudRaw::Reset(){
  fMode = kMixed;
  fADC.clear();
}

//______________________________________________________________________________
void DmpEvtNudRaw::PrintEvent() const {

}
//______________________________________________________________________________
void DmpEvtNudRaw::SetSignal(Float_t ADC){
}

