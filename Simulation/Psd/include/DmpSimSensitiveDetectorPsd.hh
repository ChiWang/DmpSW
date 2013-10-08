#ifndef DmpSimSensitiveDetectorPsd_h
#define DmpSimSensitiveDetectorPsd_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class DmpSimDetectorConstruction;
class G4HCofThisEvent;
class G4Step;
#include "DmpSimHitPsd.hh"

class DmpSimSensitiveDetectorPsd : public G4VSensitiveDetector
{
public:
  
  DmpSimSensitiveDetectorPsd(G4String);
  ~DmpSimSensitiveDetectorPsd();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step* astep,G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  void clear();
  void DrawAll();
  void PrintAll();
  
private:
  
  DmpSimHitPsdsCollection*  PSDHitCollection;      
  DmpSimDetectorConstruction* dmpDetector;
  G4int *HitID;
  G4int NbOfPSDStrips; 
};

#endif






