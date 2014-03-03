#ifndef DmpSimuPrimaryGeneratorAction_h
#define DmpSimuPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"

class G4Event;
class DmpDetectorConstruction;
class DmpSimuPrimaryGeneratorMessenger;
class G4GeneralParticleSource;
class DmpG4RunManager;

class DmpSimuPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  DmpSimuPrimaryGeneratorAction();    
  ~DmpSimuPrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);

  void SetRndmFlag(G4String val)     { rndmFlag      = val;}
  void SetSourceType(G4int val)      { nSourceType   = val;}
  void SetSpectrumType(G4int val)    { nSpectrumType = val;}
  void SetupSourceType(G4int val);
  void SetupSpectrumType(G4int val);
  void SetVertexRadius(G4double val) { dVertexRadius = val;}
  void SetSourceGen(G4int val)       { sourceGen     = val;}
  void SetParticleCenterCoords(G4ThreeVector position){
    posDist->SetCentreCoords(position);
  }
  void SetParticleMomDirection(G4ThreeVector momentum){
    angDist->SetParticleMomentumDirection(momentum);
  }

  G4ParticleDefinition* GetParticleDefinition() {
    return particleGun->GetParticleDefinition();
  }
  G4GeneralParticleSource* GetParticleSource() {
    return fGPS;
  }
  G4int GetSpectrumType(){
    return nSpectrumType;
  }
  
  G4int GetSourceType(){
    return nSourceType;
  }
  
  G4double GetVertexRadius(){
    return dVertexRadius;
  }
  
  G4int GetSourceGen(){
    return sourceGen;
  }

  //bool GenOnly()                      { return genOnly; }
  //void SetGenOnly(G4bool val)         { genOnly = val;  }

  bool UseGenFilter()                 { return useGenFilter; }
  void SetUseGenFilter(G4bool val)    { useGenFilter = val;  }

  void runGenFilter(G4Event*);
  bool PassGenFilter()                { return passGenFilter; }

  void SetFilterShadowed(G4bool val)  { filterShadowed = val; }
  void SetFilterUpward  (G4bool val)  { filterUpward   = val; }
  void SetFilterBelowBGO(G4bool val)  { filterBelowBGO = val; }

private:
  G4ParticleGun*                 particleGun;
  G4GeneralParticleSource*       fGPS;	  
  DmpDetectorConstruction*       dmpDetector;  
  DmpSimuPrimaryGeneratorMessenger* gunMessenger; 
  G4String                       rndmFlag;    //flag for a random impact point (not used)
  G4int                          nSourceType;
  G4double                       dVertexRadius;
  G4int                          nSpectrumType;
  G4int                          sourceGen; // 1 for GeneralParticleSource
  G4SPSPosDistribution*          posDist; 
  G4SPSEneDistribution*          eneDist;
  G4SPSAngDistribution*          angDist;  
  G4SPSRandomGenerator*          rndDist;

  DmpG4RunManager*               runManager;

  //G4bool genOnly;
  G4bool useGenFilter;
  G4bool passGenFilter;

  G4bool filterShadowed;
  G4bool filterUpward;
  G4bool filterBelowBGO;

  G4int  nFilterRejected;
  G4int  nGenerated;

};

#endif

