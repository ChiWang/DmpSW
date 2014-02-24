#ifndef DmpNudSensitiveDetector_h
#define DmpNudSensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class DmpDetectorConstruction;
class G4HCofThisEvent;
class G4Step;
#include "DmpSimuNudHit.hh"

class DmpNudSensitiveDetector : public G4VSensitiveDetector
{
public:
  
  DmpNudSensitiveDetector(G4String);
  ~DmpNudSensitiveDetector();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step* astep,G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  void clear();
  void DrawAll();
  void PrintAll();
  
private:
  
//  DmpSimuNudHitsCollection*  NUDHitCollection;  
   DmpSimuNudHitsCollection*  NUDHitCollection0;  
   DmpSimuNudHitsCollection*  NUDHitCollection1;  
   DmpSimuNudHitsCollection*  NUDHitCollection2;  
   DmpSimuNudHitsCollection*  NUDHitCollection3;   
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






