/*
 *  $Id: DmpSimPrimaryGeneratorAction.h, 2014-03-03 23:06:32 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifndef DmpSimPrimaryGeneratorAction_H
#define DmpSimPrimaryGeneratorAction_H

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class DmpSimrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction{
public:
  DmpSimrimaryGeneratorAction();    
  ~DmpSimrimaryGeneratorAction();
  
  void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource*       fGPS;

};

#endif

