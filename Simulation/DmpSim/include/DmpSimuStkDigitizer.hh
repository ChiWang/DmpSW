#ifndef DmpSimuStkDigitizer_h
#define DmpSimuStkDigitizer_h 1

#include "G4VDigitizerModule.hh"
#include "DmpSimuStkDigi.hh"
#include "globals.hh"

//class DmpSimuStkDigitizerMessenger;
class DmpDetectorConstruction;

class DmpSimuStkDigitizer : public G4VDigitizerModule
{
public:
  
  DmpSimuStkDigitizer(G4String name);
  ~DmpSimuStkDigitizer();
  
  void Digitize();
  void SetThreshold(G4double val) { STKThreshold = val;}
  inline G4int* GetThitID() {return ThitID;}

private:
  
  DmpSimuStkDigitsCollection*  DigitsCollection;

  G4double STKThreshold; // energy threshold to produce a digit
  //DmpSimuStkDigitizerMessenger* digiMessenger;

  DmpDetectorConstruction* dmpDetector;

  G4int (*ThitID);
  
  G4int NbOfTKRLayers;
  G4int NbOfTKRStrips;
  G4int NbOfTKRChannels;
  G4int NbOfTKRChannelsL;

};

#endif








