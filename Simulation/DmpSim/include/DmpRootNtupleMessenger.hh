#ifndef DmpRootNtupleMessenger_h
#define DmpRootNtupleMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DmpRootNtupleManager;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;

class DmpRootNtupleMessenger: public G4UImessenger
{
public:

  DmpRootNtupleMessenger(DmpRootNtupleManager*);
  //DmpRootNtupleMessenger();
  ~DmpRootNtupleMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  G4UIdirectory * dmpRootNtupleDir;
  //DmpRootNtupleManager*  dmpRootNtupleManager;
  DmpRootNtupleManager*  dmpRootNtupleManager;
  

  G4UIcmdWithABool* RootGenDebugCmd;
  G4UIcmdWithABool* GenerationOnlyCmd;
  G4UIcmdWithABool* KeepOnlyDownwardCmd;
  G4UIcmdWithAString* RootFileCmd;
  G4UIcmdWithADoubleAndUnit*   CalEcutCmd;
  G4UIcmdWithAnInteger*        SiDigicutCmd;

};

#endif










