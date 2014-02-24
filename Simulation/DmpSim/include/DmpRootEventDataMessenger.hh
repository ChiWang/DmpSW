#ifndef DmpRootEventDataMessenger_h
#define DmpRootEventDataMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DmpRootEventDataManager;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;

class DmpRootEventDataMessenger: public G4UImessenger
{
public:

    DmpRootEventDataMessenger(DmpRootEventDataManager*);
  //DmpRootNtupleMessenger();
  ~DmpRootEventDataMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  G4UIdirectory * dmpRootEventDataDir;
  DmpRootEventDataManager*  dmpRootEventDataManager;
  

  G4UIcmdWithABool* RootGenDebugCmd;
  //G4UIcmdWithABool* GenerationOnlyCmd;
  //G4UIcmdWithABool* KeepOnlyDownwardCmd;
  G4UIcmdWithAString* RootFileCmd;
  G4UIcmdWithADoubleAndUnit*   CalEcutCmd;
  G4UIcmdWithAnInteger*        SiDigicutCmd;

};

#endif










