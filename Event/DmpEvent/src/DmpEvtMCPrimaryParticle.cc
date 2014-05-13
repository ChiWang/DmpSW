/*
 *  $Id: DmpEvtMCPrimaryParticle.cc, 2014-04-30 20:47:18 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 02/03/2014
*/

#include "DmpEvtMCPrimaryParticle.h"

ClassImp(DmpEvtMCPrimaryParticle)

//-------------------------------------------------------------------
DmpEvtMCPrimaryParticle::DmpEvtMCPrimaryParticle()
 :fEventID(0),
  fPosX(0),
  fPosY(0),
  fPosZ(0),
  fPDGCode(0),
  fMass(0),
  fCharge(0),
  fPx(0),
  fPy(0),
  fPz(0)
{}

//-------------------------------------------------------------------
DmpEvtMCPrimaryParticle::~DmpEvtMCPrimaryParticle(){

}

//-------------------------------------------------------------------
double DmpEvtMCPrimaryParticle::GetEnergy() const {
// *
// *  TODO: 
// *

}
