/*
 *  $Id: DmpEvtBgoHit.cc, 2014-03-02 22:42:19 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtPMT.h"
#include "DmpEvtBgoHit.h"
#include "DmpParametersBgo.h"

using namespace DmpParameters::Bgo;

ClassImp(DmpEvtBgoHit)

//------------------------------------------------------------------------------
DmpEvtBgoHit::DmpEvtBgoHit()
 :fSDID(0),
  fEnergy(0),
  fUsedSide(0),
  fPMT0(0),
  fPMT1(0)
{
  for (int i=0;i<3;++i) fPosition[i]=0;
  fPMT0 = new DmpEvtPMT(kDyNo);
  fPMT1 = new DmpEvtPMT(kDyNo);
}

//------------------------------------------------------------------------------
DmpEvtBgoHit::~DmpEvtBgoHit(){
  delete fPMT0;
  delete fPMT1;
}

//-------------------------------------------------------------------
void DmpEvtBgoHit::Reset(){

}

//------------------------------------------------------------------------------
void DmpEvtBgoHit::PrintHit() const{
}

void DmpEvtBgoHit::AppendThisHit(double e, double x, double y, double z){
  double totE = e + fEnergy;
  double nX = (e*x + fEnergy*fPosition[0])/totE;
  double nY = (e*y + fEnergy*fPosition[1])/totE;
  double nZ = (e*z + fEnergy*fPosition[2])/totE;
  fPosition[0] = nX;
  fPosition[1] = nY;
  fPosition[2] = nZ;
  fEnergy = totE;
}
