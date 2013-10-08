#ifndef DmpStkSensitiveDetector_h
#define DmpStkSensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class DmpDetectorConstruction;
class DmpSimuPrimaryGeneratorAction;
class DmpStkROGeometry;
class G4HCofThisEvent;
class G4Step;

#include "DmpSimuStkHit.hh"

class DmpStkSensitiveDetector : public G4VSensitiveDetector
{
public:
  
  DmpStkSensitiveDetector(G4String);
  ~DmpStkSensitiveDetector();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step* astep,G4TouchableHistory* ROHist);
  void EndOfEvent(G4HCofThisEvent*);
  void clear();
  void DrawAll();
  void PrintAll();
  
private:
  
  DmpSimuStkHitsCollection*  TrackerCollection;      
  DmpDetectorConstruction* dmpDetector;
  DmpSimuPrimaryGeneratorAction* primaryGeneratorAction;

  G4bool isPhotonRun;

  G4int (*ThitXID);
  G4int (*ThitYID);
  
  G4int NbOfTKRLayers;
  G4int NbOfTKRStrips;
  G4int NbOfTKRChannels;


};

#endif






