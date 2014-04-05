/*
 *  $Id: DmpEvtStkMSD.cc, 2014-04-05 15:12:22 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtStkMSD.h"
#include "DmpDetectorStk.h"

ClassImp(DmpEvtStkMSD)

//------------------------------------------------------------------------------
DmpEvtStkMSD::DmpEvtStkMSD()
 :fSDID(0),
  fEnergy(0),
  fUsedSide(0)
{
  for (int i=0;i<3;++i) fPosition[i]=0;
}

//------------------------------------------------------------------------------
DmpEvtStkMSD::~DmpEvtStkMSD(){
}

//-------------------------------------------------------------------
void DmpEvtStkMSD::Reset(){

}

//------------------------------------------------------------------------------
void DmpEvtStkMSD::PrintHit() const{
}

void DmpEvtStkMSD::AddThisHit(double e, double x, double y, double z){
  double totE = e + fEnergy;
  double nX = (e*x + fEnergy*fPosition[0])/totE;
  double nY = (e*y + fEnergy*fPosition[1])/totE;
  double nZ = (e*z + fEnergy*fPosition[2])/totE;
  fPosition[0] = nX;
  fPosition[1] = nY;
  fPosition[2] = nZ;
  fEnergy = totE;
}
