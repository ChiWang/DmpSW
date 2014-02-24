#ifndef DmpSimuStkDigitizerMessenger_h
#define DmpSimuStkDigitizerMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DmpSimuStkDigitizer;
class G4UIcmdWithADoubleAndUnit;

class DmpSimuStkDigitizerMessenger: public G4UImessenger
{
public:
  DmpSimuStkDigitizerMessenger(DmpSimuStkDigitizer*);
  ~DmpSimuStkDigitizerMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DmpSimuStkDigitizer* dmpSimuDigitizer; 
  G4UIcmdWithADoubleAndUnit*  ThresholdCmd;

};

#endif


