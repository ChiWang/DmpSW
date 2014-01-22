// Description: This class hinerits from G4UImessenger. It is used to
// pass user command to DmpRootNtupleManager
//
// Author(s):
//  - creation by F.gargano, 13/09/2013

#include "DmpRootNtupleMessenger.hh"

//#include "DmpDetectorConstruction.hh"
#include "DmpRootNtupleManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"

DmpRootNtupleMessenger::DmpRootNtupleMessenger(DmpRootNtupleManager * ntupleManager)
  :dmpRootNtupleManager(ntupleManager)
//DmpRootNtupleMessenger::DmpRootNtupleMessenger()
{ 
  dmpRootNtupleDir = new G4UIdirectory("/root/");
  dmpRootNtupleDir->SetGuidance("DAMPE root ntuple control");

  // update Payload

//   UpdateCmd = new G4UIcmdWithoutParameter("/payload/update",this);
//   UpdateCmd->SetGuidance("Update payload geometry.");
//   UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
//   UpdateCmd->SetGuidance("if you changed geometrical value(s).");
//   UpdateCmd->AvailableForStates(G4State_Idle);
  RootGenDebugCmd = new G4UIcmdWithABool("/root/GenDebug",this);
  RootGenDebugCmd->SetGuidance("Select the debug mode for generetion of events");
  RootGenDebugCmd->SetGuidance("  Choice : true, false");
  RootGenDebugCmd->SetParameterName("GenDebug",false);
  RootGenDebugCmd->SetDefaultValue((G4bool)false);
  RootGenDebugCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
  /***
  GenerationOnlyCmd = new G4UIcmdWithABool("/root/GenerationOnly",this);
  GenerationOnlyCmd->SetGuidance("Only generate primary particles");
  GenerationOnlyCmd->SetGuidance("  Choice : true, false");
  GenerationOnlyCmd->SetParameterName("GenerationOnly",false);
  GenerationOnlyCmd->SetDefaultValue((G4bool)false);
  GenerationOnlyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
  ***/
  KeepOnlyDownwardCmd = new G4UIcmdWithABool("/root/KeepOnlyDownward",this);
  KeepOnlyDownwardCmd->SetGuidance("Keep only event with downward primary particle");
  KeepOnlyDownwardCmd->SetGuidance("  Choice : true, false");
  KeepOnlyDownwardCmd->SetParameterName("KeepOnlyDownward",false);
  KeepOnlyDownwardCmd->SetDefaultValue((G4bool)false);
  KeepOnlyDownwardCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  RootFileCmd = new G4UIcmdWithAString("/root/RootFile",this);
  RootFileCmd->SetGuidance("Select the Root output file");
  RootFileCmd->SetGuidance("  Choice : Choose the root filename");
  RootFileCmd->SetParameterName("RootFileName",false);
  RootFileCmd->SetDefaultValue((G4String)"DmpSimu");
  RootFileCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  


  CalEcutCmd = new G4UIcmdWithADoubleAndUnit("/root/CalEcut",this);
  CalEcutCmd->SetGuidance("Minimum energy (and unit) in calorimeter for saving event to ntuple.");
  CalEcutCmd->SetParameterName("CalEcut",false);
  CalEcutCmd->SetDefaultValue((G4double)0.*MeV);
  CalEcutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SiDigicutCmd = new G4UIcmdWithAnInteger("/root/SiDigicut",this);
  SiDigicutCmd->SetGuidance("Minimum number of SiDigi in STK for saving event to ntuple.");
  SiDigicutCmd->SetParameterName("SiDigicut",false);
  SiDigicutCmd->SetDefaultValue((G4int)-1);
  SiDigicutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

DmpRootNtupleMessenger::~DmpRootNtupleMessenger()
{
  //delete GenerationOnlyCmd;
  delete KeepOnlyDownwardCmd;
  delete RootGenDebugCmd;
  delete RootFileCmd;
  delete CalEcutCmd;
  delete SiDigicutCmd;
}

void DmpRootNtupleMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == RootGenDebugCmd )
    { 
      dmpRootNtupleManager->SetRootGenDebug(RootGenDebugCmd->GetNewBoolValue(newValue));
      //G4cout << " new value  "<< RootGenDebugCmd->GetNewBoolValue(newValue) << G4endl;
   
    }
  /***
  if( command == GenerationOnlyCmd )
    { 
      dmpRootNtupleManager->SetGenerationOnly(GenerationOnlyCmd->GetNewBoolValue(newValue));
   
    }
  ***/
  if( command == KeepOnlyDownwardCmd )
    { 
      dmpRootNtupleManager->SetKeepOnlyDownward(KeepOnlyDownwardCmd->GetNewBoolValue(newValue));
   
    }
 if( command == RootFileCmd )
    { 
      dmpRootNtupleManager->SetRootFile(newValue);
   
    }

 if( command == CalEcutCmd )
    { 
      dmpRootNtupleManager->SetCalEcut(CalEcutCmd->GetNewDoubleValue(newValue));
      //G4cout << " new value  "<< CalEcutCmd->GetNewDoubleValue(newValue) << G4endl;   
    }

 if( command == SiDigicutCmd )
    { 
      dmpRootNtupleManager->SetSiDigicut(SiDigicutCmd->GetNewIntValue(newValue));
      //G4cout << " new value  "<< CalEcutCmd->GetNewDoubleValue(newValue) << G4endl;   
    }

    // to check
    //{ dmpDetectorConstruction->UpdateGeometry(); }
  
}







