#ifndef DmpSimuNudDigitizerMessenger_h
#define DmpSimuNudDigitizerMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DmpSimuNudDigitizer;
class G4UIcmdWithADoubleAndUnit;

class DmpSimuNudDigitizerMessenger: public G4UImessenger
{
public:
  DmpSimuNudDigitizerMessenger(DmpSimuNudDigitizer*);
  ~DmpSimuNudDigitizerMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DmpSimuNudDigitizer* dmpSimuDigitizer; 
  G4UIcmdWithADoubleAndUnit*  ThresholdCmd;

};

#endif


