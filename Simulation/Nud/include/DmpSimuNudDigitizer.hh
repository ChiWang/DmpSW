#ifndef DmpSimuNudDigitizer_h
#define DmpSimuNudDigitizer_h 1

#include "G4VDigitizerModule.hh"
#include "DmpSimuNudDigi.hh"
#include "globals.hh"

//class DmpSimuPsdDigitizerMessenger;
class DmpDetectorConstruction;

class DmpSimuNudDigitizer : public G4VDigitizerModule
{
public:
  
  DmpSimuNudDigitizer(G4String name);
  ~DmpSimuNudDigitizer();
  
  void Digitize();
  void SetThreshold(G4double val) { NUDThreshold = val;}


private:
  
//  DmpSimuNudDigitsCollection*  DigitsCollection;
 DmpSimuNudDigitsCollection*  DigitsCollection0;
 DmpSimuNudDigitsCollection*  DigitsCollection1; 
 DmpSimuNudDigitsCollection*  DigitsCollection2;
 DmpSimuNudDigitsCollection*  DigitsCollection3;


  G4double NUDThreshold; // energy threshold to produce a digit
  //DmpSimuPsdDigitizerMessenger* digiMessenger;

  DmpDetectorConstruction* dmpDetector;

};

#endif








