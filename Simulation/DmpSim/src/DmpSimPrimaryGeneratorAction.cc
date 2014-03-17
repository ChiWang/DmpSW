/*
 *  $Id: DmpSimPrimaryGeneratorAction.cc, 2014-03-17 20:37:33 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "G4GeneralParticleSource.hh"

#include "DmpSimPrimaryGeneratorAction.h"
#include "DmpSimDataManager.h"

DmpSimPrimaryGeneratorAction::DmpSimPrimaryGeneratorAction()
 :fGPS(0)
{
  fGPS = new G4GeneralParticleSource();
  //fGPS->SetNumberOfParticles(1);
  //fGPS->SetParticleDefinition(particle);
}

DmpSimPrimaryGeneratorAction::~DmpSimPrimaryGeneratorAction(){
  delete fGPS;
}

void DmpSimPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent){
//std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
  fGPS->GeneratePrimaryVertex(anEvent);
  DmpSimDataManager::GetInstance()->UpdatePrimaryParticleInformation(anEvent);
}

