/*
 *  $Id: DmpSimDetectorMessenger.cc, 2014-02-26 21:18:48 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "DmpSimDetectorMessenger.h"
#include "DmpSimDetectorConstruction.h"

DmpSimDetectorMessenger::DmpSimDetectorMessenger(DmpSimDetectorConstruction *detector)
  :fDetectorConstruction(detector)
{
  fDmpDetDir = new G4UIdirectory("/payload/");
  fDmpDetDir->SetGuidance("DAMPE payload control.");

  // update Payload
  fUpdateCmd = new G4UIcmdWithoutParameter("/payload/update",this);
  fUpdateCmd->SetGuidance("Update payload geometry.");
  fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  fUpdateCmd->SetGuidance("if you changed geometrical value(s).");
  fUpdateCmd->AvailableForStates(G4State_Idle);
}

DmpSimDetectorMessenger::~DmpSimDetectorMessenger(){
  delete fUpdateCmd;
}

void DmpSimDetectorMessenger::SetNewValue(G4UIcommand *command,G4String newValue){ 
  if( command == fUpdateCmd ){
    fDetectorConstruction->fUpdateGeometry();
  }
}


