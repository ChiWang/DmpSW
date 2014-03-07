/*
 *  $Id: DmpEvtPsdHit.cc, 2014-03-03 21:02:13 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtPMT.h"
#include "DmpEvtPsdHit.h"
#include "DmpParameterPsd.h"

using namespace DmpParameter::DmpDetector;

ClassImp(DmpEvtPsdHit)

//------------------------------------------------------------------------------
DmpEvtPsdHit::DmpEvtPsdHit()
 :fBarID(0),
  fEnergy(0),
  fUsedSide(0),
  fPMT0(0),
  fPMT1(0)
{
  for (int i=0;i<3;++i) fPosition[i]=0;
  fPMT0 = new DmpEvtPMT(Psd::kDyNo);
  fPMT1 = new DmpEvtPMT(Psd::kDyNo);
}

//------------------------------------------------------------------------------
DmpEvtPsdHit::~DmpEvtPsdHit(){
  delete fPMT0;
  delete fPMT1;
}

//-------------------------------------------------------------------
void DmpEvtPsdHit::Reset(){

}

//------------------------------------------------------------------------------
void DmpEvtPsdHit::PrintHit() const{
}

void DmpEvtPsdHit::AddThisStep(double e, double x, double y, double z){
  double totE = e + fEnergy;
  double nX = (e*x + fEnergy*fPosition[0])/totE;
  double nY = (e*y + fEnergy*fPosition[1])/totE;
  double nZ = (e*z + fEnergy*fPosition[2])/totE;
  fPosition[0] = nX;
  fPosition[1] = nY;
  fPosition[2] = nZ;
  fEnergy = totE;
}
