#ifndef DmpSimuBgoDigitizer_h
#define DmpSimuBgoDigitizer_h 1

#include "G4VDigitizerModule.hh"
#include "DmpSimuBgoDigi.hh"
#include "globals.hh"

//class DmpSimuBgoDigitizerMessenger;
class DmpDetectorConstruction;

class DmpSimuBgoDigitizer : public G4VDigitizerModule
{
public:
  
  DmpSimuBgoDigitizer(G4String name);
  ~DmpSimuBgoDigitizer();
  
  void Digitize();
  void SetThreshold(G4double val) { BGOThreshold = val;}


private:
  
  DmpSimuBgoDigitsCollection*  DigitsCollection;

  G4double BGOThreshold; // energy threshold to produce a digit
  //DmpSimuBgoDigitizerMessenger* digiMessenger;

  DmpDetectorConstruction* dmpDetector;

};

#endif








