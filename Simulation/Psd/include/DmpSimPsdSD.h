#ifndef DmpPsdSensitiveDetector_h
#define DmpPsdSensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class DmpDetectorConstruction;
class G4HCofThisEvent;
class G4Step;
#include "DmpSimuPsdHit.hh"

class DmpPsdSensitiveDetector : public G4VSensitiveDetector
{
public:
  
  DmpPsdSensitiveDetector(G4String);
  ~DmpPsdSensitiveDetector();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step* astep,G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  void clear();
  void DrawAll();
  void PrintAll();
  
private:
  
  DmpSimuPsdHitsCollection*  PSDHitCollection;      
  DmpDetectorConstruction* dmpDetector;
  G4int *HitID;
  G4int NbOfPSDStrips; 
};

#endif






