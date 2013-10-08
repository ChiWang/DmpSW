#ifndef DmpSimPrimaryGeneratorMessenger_h
#define DmpSimPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DmpSimPrimaryGeneratorAction;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithABool;

class DmpSimPrimaryGeneratorMessenger: public G4UImessenger
{
public:
  DmpSimPrimaryGeneratorMessenger(DmpSimPrimaryGeneratorAction*);
  ~DmpSimPrimaryGeneratorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DmpSimPrimaryGeneratorAction* dmpSimPrimaryGeneratorAction;
 
  G4UIcmdWithAString*          RndmCmd;
  G4UIcmdWithAnInteger*        SourceTypeCmd;
  G4UIcmdWithADoubleAndUnit*   VertexRadiusCmd;
  G4UIcmdWithAnInteger*        SpectrumTypeCmd;
  G4UIcmdWithABool*            SourceGenCmd;

};

#endif


