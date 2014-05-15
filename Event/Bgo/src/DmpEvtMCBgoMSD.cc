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
  fEnergy(0),
  fPosX(0),
  fPosY(0),
  fPosZ(0)
{
}

//------------------------------------------------------------------------------
DmpEvtMCBgoMSD::~DmpEvtMCBgoMSD(){
}

//-------------------------------------------------------------------
void DmpEvtMCBgoMSD::AddG4Hit(const double &e,const double &x,const double &y,const double &z){
  double totE = e + fEnergy;
  fPosX = (e*x + fEnergy*fPosX)/totE;
  fPosY = (e*y + fEnergy*fPosY)/totE;
  fPosZ = (e*z + fEnergy*fPosZ)/totE;
  fEnergy = totE;
}


