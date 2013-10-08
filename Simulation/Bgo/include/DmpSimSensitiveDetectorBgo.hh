#ifndef DmpSimSensitiveDetectorBgo_h
#define DmpSimSensitiveDetectorBgo_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class DmpDetectorConstruction;
class G4HCofThisEvent;
class G4Step;
#include "DmpSimHitBgo.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class DmpSimSensitiveDetectorBgo : public G4VSensitiveDetector
{
public:
  
  DmpSimSensitiveDetectorBgo(G4String);
  ~DmpSimSensitiveDetectorBgo();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step* astep,G4TouchableHistory* ROHist);
  void EndOfEvent(G4HCofThisEvent*);
  void clear();
  void DrawAll();
  void PrintAll();
  
private:
  
  DmpSimHitBgosCollection*  BGOHitCollection;      
  DmpDetectorConstruction*   dmpDetector;

  G4int (*ChitXID);
  G4int (*ChitYID);

  G4int NbOfCALLayers;
  G4int NbOfCALBars; 
  G4int NbOfCALChannels; 

};

#endif






