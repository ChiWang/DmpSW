#ifndef DmpSimDetectorMessenger_H
#define DmpSimDetectorMessenger_H

#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithoutParameter;
class DmpSimDetectorConstruction;

class DmpSimDetectorMessenger : public G4UImessenger{
public:
  DmpSimDetectorMessenger(DmpSimDetectorConstruction*);
  ~DmpSimDetectorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DmpSimDetectorConstruction    *fDetectorConstruction;
  G4UIdirectory                 *fDmpDetDir;
  G4UIcmdWithoutParameter       *fUpdateCmd;
};

#endif


