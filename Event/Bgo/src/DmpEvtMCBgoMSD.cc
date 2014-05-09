/*
 *  $Id: DmpEvtMCBgoMSD.cc, 2014-05-01 21:18:52 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtMCBgoMSD.h"

ClassImp(DmpEvtMCBgoMSD)

//------------------------------------------------------------------------------
DmpEvtMCBgoMSD::DmpEvtMCBgoMSD()
 :fSDID(0),
  fEnergy(0)
{
  for (short i=0;i<3;++i) fPosition[i]=0;
}

//------------------------------------------------------------------------------
DmpEvtMCBgoMSD::~DmpEvtMCBgoMSD(){
}

//-------------------------------------------------------------------
void DmpEvtMCBgoMSD::AddG4Hit(const double &e,const double &x,const double &y,const double &z){
  double totE = e + fEnergy;
  fPosition[0] = (e*x + fEnergy*fPosition[0])/totE;
  fPosition[1] = (e*y + fEnergy*fPosition[1])/totE;
  fPosition[2] = (e*z + fEnergy*fPosition[2])/totE;
  fEnergy = totE;
}


