#ifndef DmpDetectorMessenger_h
#define DmpDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DmpDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class DmpDetectorMessenger: public G4UImessenger
{
public:
  DmpDetectorMessenger(DmpDetectorConstruction* );
  ~DmpDetectorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DmpDetectorConstruction*   dmpDetectorConstruction;
  
  G4UIdirectory*             dmpDetDir;

  // Total
  G4UIcmdWithoutParameter*   UpdateCmd;
};

#endif










