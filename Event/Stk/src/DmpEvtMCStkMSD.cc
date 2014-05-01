/*
 *  $Id: DmpEvtMCStkMSD.cc, 2014-05-01 21:19:20 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtMCStkMSD.h"

ClassImp(DmpEvtMCStkMSD)

//------------------------------------------------------------------------------
DmpEvtMCStkMSD::DmpEvtMCStkMSD()
 :fSDID(0),
  fEnergy(0)
{
  for (short i=0;i<3;++i) fPosition[i]=0;
}

//------------------------------------------------------------------------------
DmpEvtMCStkMSD::~DmpEvtMCStkMSD(){
}

//-------------------------------------------------------------------
void DmpEvtMCStkMSD::AddG4Hit(const double &e,const double &x,const double &y,const double &z){
  double totE = e + fEnergy;
  double nX = (e*x + fEnergy*fPosition[0])/totE;
  double nY = (e*y + fEnergy*fPosition[1])/totE;
  double nZ = (e*z + fEnergy*fPosition[2])/totE;
  fPosition[0] = nX;
  fPosition[1] = nY;
  fPosition[2] = nZ;
  fEnergy = totE;
}


