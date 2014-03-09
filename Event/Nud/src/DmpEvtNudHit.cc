/*
 *  $Id: DmpEvtNudHit.cc, 2014-03-03 21:05:40 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtPMT.h"
#include "DmpEvtNudHit.h"
#include "DmpParameterNud.h"

using namespace DmpParameter::Detector;

ClassImp(DmpEvtNudHit)

//------------------------------------------------------------------------------
DmpEvtNudHit::DmpEvtNudHit()
 :fBarID(0),
  fEnergy(0),
  fUsedSide(0),
  fPMT0(0),
  fPMT1(0)
{
  for (int i=0;i<3;++i) fPosition[i]=0;
  fPMT0 = new DmpEvtPMT(Nud::kDyNo);
  fPMT1 = new DmpEvtPMT(Nud::kDyNo);
}

//------------------------------------------------------------------------------
DmpEvtNudHit::~DmpEvtNudHit(){
  delete fPMT0;
  delete fPMT1;
}

//-------------------------------------------------------------------
void DmpEvtNudHit::Reset(){

}

//------------------------------------------------------------------------------
void DmpEvtNudHit::PrintHit() const{
}

void DmpEvtNudHit::AddThisStep(double e, double x, double y, double z){
  double totE = e + fEnergy;
  double nX = (e*x + fEnergy*fPosition[0])/totE;
  double nY = (e*y + fEnergy*fPosition[1])/totE;
  double nZ = (e*z + fEnergy*fPosition[2])/totE;
  fPosition[0] = nX;
  fPosition[1] = nY;
  fPosition[2] = nZ;
  fEnergy = totE;
}
