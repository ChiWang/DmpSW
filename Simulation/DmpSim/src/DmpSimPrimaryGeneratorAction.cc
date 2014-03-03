/*
 *  $Id: DmpSimPrimaryGeneratorAction.cc, 2014-03-03 23:21:07 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "G4GeneralParticleSource.hh"

#include "DmpSimPrimaryGeneratorAction.h"
#include "DmpSimDataManager.h"
#include "DmpEvtSimPrimaryParticle.h"

DmpSimrimaryGeneratorAction::DmpSimrimaryGeneratorAction()
 :fGPS(0)
{
  fGPS = new G4GeneralParticleSource();
  fGPS->SetNumberOfParticles(1);
  fGPS->SetParticleDefinition(particle);
}

DmpSimrimaryGeneratorAction::~DmpSimrimaryGeneratorAction(){
  delete fGPS;
}

void DmpSimrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  fGPS->GeneratePrimaryVertex(anEvent);
// *
// *  TODO: Use DataManager to save informations of parimary particle
// *
  DmpEvtSimPrimaryParticle *primaryParticle = DmpSimDataManager::GetInstance()->GetPrimaryParticle();
  //primaryParticle->SetXXX();
}

