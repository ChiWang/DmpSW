#ifndef DmpSimDetectorMessenger_h
#define DmpSimDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DmpSimDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class DmpSimDetectorMessenger: public G4UImessenger
{
public:
  DmpSimDetectorMessenger(DmpSimDetectorConstruction* );
  ~DmpSimDetectorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DmpSimDetectorConstruction*   dmpDetectorConstruction;
  
  G4UIdirectory*             dmpDetDir;

  // Total
  G4UIcmdWithoutParameter*   UpdateCmd;
};

#endif










