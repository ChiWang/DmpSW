#ifndef DmpSimuPsdDigitizer_h
#define DmpSimuPsdDigitizer_h 1

#include "G4VDigitizerModule.hh"
#include "DmpSimuPsdDigi.hh"
#include "globals.hh"

//class DmpSimuPsdDigitizerMessenger;
class DmpDetectorConstruction;

class DmpSimuPsdDigitizer : public G4VDigitizerModule
{
public:
  
  DmpSimuPsdDigitizer(G4String name);
  ~DmpSimuPsdDigitizer();
  
  void Digitize();
  void SetThreshold(G4double val) { PSDThreshold = val;}


private:
  
  DmpSimuPsdDigitsCollection*  DigitsCollection;

  G4double PSDThreshold; // energy threshold to produce a digit
  //DmpSimuPsdDigitizerMessenger* digiMessenger;

  DmpDetectorConstruction* dmpDetector;

};

#endif








