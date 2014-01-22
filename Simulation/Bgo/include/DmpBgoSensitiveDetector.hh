#ifndef DmpBgoSensitiveDetector_h
#define DmpBgoSensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class DmpDetectorConstruction;
class G4HCofThisEvent;
class G4Step;
#include "DmpSimuBgoHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class DmpBgoSensitiveDetector : public G4VSensitiveDetector
{
public:
  
  DmpBgoSensitiveDetector(G4String);
  ~DmpBgoSensitiveDetector();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step* astep,G4TouchableHistory* ROHist);
  void EndOfEvent(G4HCofThisEvent*);
  void clear();
  void DrawAll();
  void PrintAll();
  
private:
  
  DmpSimuBgoHitsCollection*  BGOHitCollection;      
  DmpDetectorConstruction*   dmpDetector;

  G4int (*ChitXID);
  G4int (*ChitYID);

  G4int NbOfCALLayers;
  G4int NbOfCALLayerBars; 
  G4int NbOfCALChannels; 

  G4double m_attenuation; //light attenuation constant

};

#endif






