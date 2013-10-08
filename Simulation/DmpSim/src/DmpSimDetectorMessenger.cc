// Description: This class hinerits from G4UImessenger. It is used to
// pass user command to DmpSimDetectorConstruction
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpSimDetectorMessenger.hh"

#include "DmpSimDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

DmpSimDetectorMessenger::DmpSimDetectorMessenger(DmpSimDetectorConstruction * detector)
  :dmpDetectorConstruction(detector)

{ 
  dmpDetDir = new G4UIdirectory("/payload/");
  dmpDetDir->SetGuidance("DAMPE payload control.");

  // update Payload

  UpdateCmd = new G4UIcmdWithoutParameter("/payload/update",this);
  UpdateCmd->SetGuidance("Update payload geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);
      
}

DmpSimDetectorMessenger::~DmpSimDetectorMessenger()
{
  delete UpdateCmd;
}

void DmpSimDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == UpdateCmd )
    { dmpDetectorConstruction->UpdateGeometry(); }
  
}







