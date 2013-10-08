#ifndef DmpSimDigPsdtizer_h
#define DmpSimDigPsdtizer_h 1

#include "G4VDigitizerModule.hh"
#include "DmpSimDigPsd.hh"
#include "globals.hh"

//class DmpSimDigitizerMessengerPsd;
class DmpSimDetectorConstruction;

class DmpSimDigitizer : public G4VDigitizerModule
{
public:
  
  DmpSimDigitizerPsd(G4String name);
  ~DmpSimDigitizerPsd();
  
  void Digitize();
  void SetThreshold(G4double val) { PSDThreshold = val;}


private:
  
  DmpSimDigitsCollection*  DigitsCollection;

  G4double PSDThreshold; // energy threshold to produce a digit
  //DmpSimDigitizerMessengerPsd* digiMessenger;

  DmpSimDetectorConstruction* dmpDetector;

};

#endif








