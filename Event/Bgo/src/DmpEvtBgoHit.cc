/*
 *  $Id: DmpEvtBgoHit.cc, 2014-03-11 18:52:32 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtBgoHit.h"
#include "DmpDetectorBgo.h"

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
  fPMT0 = new DmpBgoPMT();
  fPMT1 = new DmpBgoPMT();
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

//-------------------------------------------------------------------
void DmpEvtBgoHit::AddG4Hit(double e, double x, double y, double z){
  double totE = e + fEnergy;
  double nX = (e*x + fEnergy*fPosition[0])/totE;
  double nY = (e*y + fEnergy*fPosition[1])/totE;
  double nZ = (e*z + fEnergy*fPosition[2])/totE;
  fPosition[0] = nX;
  fPosition[1] = nY;
  fPosition[2] = nZ;
  fEnergy = totE;
}

//-------------------------------------------------------------------
void DmpEvtBgoHit::SetSignal(const int &id,const short &v){
  static short dyID = 0;
  dyID = id%10;
  if(id/10 == 0){ // PMT0
    if(dyID == 5){
      fPMT0->fAdcDy5 = v;
    }else if(dyID == 2){
      fPMT0->fAdcDy2 = v;
    }else{
      fPMT0->fAdcDy8 = v;
    }
  }else{    // PMT1
    if(dyID == 5){
      fPMT1->fAdcDy5 = v;
    }else if(dyID == 2){
      fPMT1->fAdcDy2 = v;
    }else{
      fPMT1->fAdcDy8 = v;
    }
  }
}


