/*
 *  $Id: DmpEvtMCBgoBar.cc, 2014-07-17 15:34:26 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#include "DmpEvtMCBgoBar.h"

ClassImp(DmpEvtMCBgoBar)

//------------------------------------------------------------------------------
DmpEvtMCBgoBar::DmpEvtMCBgoBar()
 :fGlobalBarID(0),
  fEnergy(0),
  fPosX(0),
  fPosY(0),
  fPosZ(0)
{
}

//------------------------------------------------------------------------------
DmpEvtMCBgoBar::~DmpEvtMCBgoBar(){
}

//-------------------------------------------------------------------
void DmpEvtMCBgoBar::AddG4Hit(const double &e,const double &x,const double &y,const double &z){
  double totE = e + fEnergy;
  fPosX = (e*x + fEnergy*fPosX)/totE;
  fPosY = (e*y + fEnergy*fPosY)/totE;
  fPosZ = (e*z + fEnergy*fPosZ)/totE;
  fEnergy = totE;
}


