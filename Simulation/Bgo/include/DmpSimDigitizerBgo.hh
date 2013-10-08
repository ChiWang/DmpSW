#ifndef DmpSimDigBgotizer_h
#define DmpSimDigBgotizer_h 1

#include "G4VDigitizerModule.hh"
#include "DmpSimDigBgo.hh"
#include "globals.hh"

//class DmpSimDigBgotizerMessenger;
class DmpDetectorConstruction;

class DmpSimDigBgotizer : public G4VDigitizerModule
{
public:
  
  DmpSimDigBgotizer(G4String name);
  ~DmpSimDigBgotizer();
  
  void Digitize();
  void SetThreshold(G4double val) { BGOThreshold = val;}


private:
  
  DmpSimDigBgotsCollection*  DigitsCollection;

  G4double BGOThreshold; // energy threshold to produce a digit
  //DmpSimDigBgotizerMessenger* digiMessenger;

  DmpDetectorConstruction* dmpDetector;

};

#endif








