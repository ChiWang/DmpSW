/*
 *  $Id: DmpSimPrimaryGeneratorAction.cc, 2014-03-17 20:37:33 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "G4GeneralParticleSource.hh"

#include "DmpSimPrimaryGeneratorAction.h"
#include "DmpEvtMCPrimaryParticle.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpCore.h"

DmpSimPrimaryGeneratorAction::DmpSimPrimaryGeneratorAction()
 :fGPS(0),
  fPrimaryParticle(0)
{
  fGPS = new G4GeneralParticleSource();
  //fGPS->SetNumberOfParticles(1);
  //fGPS->SetParticleDefinition(particle);
}

//-------------------------------------------------------------------
DmpSimPrimaryGeneratorAction::~DmpSimPrimaryGeneratorAction(){
  delete fGPS;
}

//-------------------------------------------------------------------
void DmpSimPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent){
  fGPS->GeneratePrimaryVertex(anEvent);
// *
// *  TODO: recorde primary particle information
// *
  //fPrimaryParticle->SetXXXX();
  fPrimaryParticle->SetPDGCode(anEvent->GetPrimaryVertex()->GetPrimary()->GetPDGcode());
}

//-------------------------------------------------------------------
bool DmpSimPrimaryGeneratorAction::Initialize(){
  fPrimaryParticle = ((DmpSimSvcDataMgr*)gCore->ServiceManager()->Get("Sim/DataMgr"))->GetPrimaryParticle();
  return fPrimaryParticle;
}

