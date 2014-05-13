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
  // Set information of current event
  fPrimaryParticle->SetEventID(anEvent->GetEventID());
  G4PrimaryVertex  *primaryVertex = anEvent->GetPrimaryVertex();
  fPrimaryParticle->SetPosition(primaryVertex->GetX0(),primaryVertex->GetY0(),primaryVertex->GetZ0());
  G4PrimaryParticle *primaryParticle = primaryVertex->GetPrimary();
  fPrimaryParticle->SetPDGCode(primaryParticle->GetPDGcode());
  fPrimaryParticle->SetMass(primaryParticle->GetMass());
  fPrimaryParticle->SetCharge(primaryParticle->GetCharge());
  fPrimaryParticle->SetMomentum(primaryParticle->GetPx(),primaryParticle->GetPy(),primaryParticle->GetPz());
}

//-------------------------------------------------------------------
bool DmpSimPrimaryGeneratorAction::Initialize(){
  fPrimaryParticle = ((DmpSimSvcDataMgr*)gCore->ServiceManager()->Get("Sim/DataMgr"))->GetPrimaryParticle();
  return fPrimaryParticle;
}

