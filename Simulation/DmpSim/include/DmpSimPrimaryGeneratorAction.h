/*
 *  $Id: DmpSimPrimaryGeneratorAction.h, 2014-05-24 12:43:19 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifndef DmpSimPrimaryGeneratorAction_H
#define DmpSimPrimaryGeneratorAction_H

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class DmpEvtMCPrimaryParticle;

class DmpSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
public:
  DmpSimPrimaryGeneratorAction();    
  ~DmpSimPrimaryGeneratorAction();
  
  void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource   *fGPS;
  DmpEvtMCPrimaryParticle   *fPrimaryParticle;
};

#endif

