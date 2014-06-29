#ifndef DmpStkDummySD_h
#define DmpStkDummySD_h 1

#include "G4VSensitiveDetector.hh"
#include "globals.hh"

class G4Step;

class DmpStkDummySD : public G4VSensitiveDetector
{
public:
  DmpStkDummySD(G4String name):G4VSensitiveDetector(name){};
  ~DmpStkDummySD() {};
  
  void Initialize(G4HCofThisEvent* ) {};
  G4bool ProcessHits(G4Step*,G4TouchableHistory*) {return false;}
  void EndOfEvent(G4HCofThisEvent*) {};
  void clear() {};
  void DrawAll() {};
  void PrintAll() {};
};

#endif
