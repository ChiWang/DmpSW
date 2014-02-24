#ifndef DmpStkDetectorMessenger_h
#define DmpStkDetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DmpStkDetectorDescription;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithABool;

class DmpStkDetectorMessenger: public G4UImessenger
{
public:
  DmpStkDetectorMessenger(DmpStkDetectorDescription*);
  ~DmpStkDetectorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DmpStkDetectorDescription* dmpStkDetectorDescription;
 
  G4UIcmdWithADoubleAndUnit*   ThickWCmd;

};

#endif


