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
  fTime(0),
  fPosX(0),
  fPosY(0),
  fPosZ(0),
  fDirectionX(0),
  fDirectionY(0),
  fDirectionZ(0),
  fKineticE(0),
  fPDGCode(0),
  fMass(0),
  fCharge(0),
  fLeptonNo(0),
  fBaryonNo(0)
{}

//-------------------------------------------------------------------
DmpEvtMCPrimaryParticle::~DmpEvtMCPrimaryParticle(){

}

