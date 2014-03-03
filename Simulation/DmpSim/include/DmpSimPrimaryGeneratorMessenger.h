#ifndef DmpSimuPrimaryGeneratorMessenger_h
#define DmpSimuPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DmpSimuPrimaryGeneratorAction;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithABool;
class G4UIcmdWith3VectorAndUnit;

class DmpSimuPrimaryGeneratorMessenger: public G4UImessenger
{
public:
  DmpSimuPrimaryGeneratorMessenger(DmpSimuPrimaryGeneratorAction*);
  ~DmpSimuPrimaryGeneratorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DmpSimuPrimaryGeneratorAction* dmpSimuPrimaryGeneratorAction;
 
  G4UIcmdWithAString*          RndmCmd;
  G4UIcmdWithAnInteger*        SourceTypeCmd;
  G4UIcmdWithADoubleAndUnit*   VertexRadiusCmd;
  G4UIcmdWithAnInteger*        SpectrumTypeCmd;
  G4UIcmdWithAnInteger*        SourceGenCmd;
  G4UIcmdWithABool*            GenerationOnlyCmd;
  G4UIcmdWithABool*            UseGenFilterCmd;
  G4UIcmdWithABool*            FilterShadowedCmd;
  G4UIcmdWithABool*            FilterUpwardCmd;
  G4UIcmdWithABool*            FilterBelowBGOCmd;
  G4UIcmdWith3VectorAndUnit*   SetPartcilePosCmd;
  G4UIcmdWith3VectorAndUnit*   SetPartcileMomDirCmd;

};

#endif


