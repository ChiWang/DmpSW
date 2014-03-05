#ifndef DmpSimNudSD_H
#define DmpSimNudSD_H

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class DmpDetectorConstruction;
class G4HCofThisEvent;
class G4Step;
#include "DmpSimNudHit.h"

class DmpSimNudSD : public G4VSensitiveDetector{
public:
  DmpSimNudSD(G4String);
  ~DmpSimNudSD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step* astep,G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);

private:
//  DmpSimNudHitsCollection*  NUDHitCollection;  
   DmpSimNudHitsCollection*  NUDHitCollection0;  
   DmpSimNudHitsCollection*  NUDHitCollection1;  
   DmpSimNudHitsCollection*  NUDHitCollection2;  
   DmpSimNudHitsCollection*  NUDHitCollection3;   
  DmpDetectorConstruction* dmpDetector;
 // G4int *HitID;
  G4int *HitID0;
  G4int *HitID1;
  G4int *HitID2;
  G4int *HitID3;
  G4double EdepTime[150];

  G4int NbOfNUDStrips; 
  G4int NbOfNUDTimeIntervals; 
  G4double TimeInterval; 
};

#endif


