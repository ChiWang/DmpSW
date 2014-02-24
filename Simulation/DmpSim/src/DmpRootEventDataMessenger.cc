// Description: This class hinerits from G4UImessenger. It is used to
// pass user command to DmpRootNtupleManager
//
// Author(s):
//  - creation by F.gargano, 13/09/2013

#include "DmpRootEventDataMessenger.hh"

//#include "DmpDetectorConstruction.hh"
#include "DmpRootEventDataManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"

DmpRootEventDataMessenger::DmpRootEventDataMessenger(DmpRootEventDataManager * rootdataManager)
  :dmpRootEventDataManager(rootdataManager)
//DmpRootNtupleMessenger::DmpRootNtupleMessenger()
{ 
  dmpRootEventDataDir = new G4UIdirectory("/root/");
  dmpRootEventDataDir->SetGuidance("DAMPE root event class control");


  RootGenDebugCmd = new G4UIcmdWithABool("/root/GenTree",this);
  RootGenDebugCmd->SetGuidance("Set ot true to keep the tree of generetion events");
  RootGenDebugCmd->SetGuidance("  Choice : true, false");
  RootGenDebugCmd->SetParameterName("GenDebug",false);
  RootGenDebugCmd->SetDefaultValue((G4bool)false);
  RootGenDebugCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  /*
  KeepOnlyDownwardCmd = new G4UIcmdWithABool("/root/KeepOnlyDownward",this);
  KeepOnlyDownwardCmd->SetGuidance("Keep only event with downward primary particle");
  KeepOnlyDownwardCmd->SetGuidance("  Choice : true, false");
  KeepOnlyDownwardCmd->SetParameterName("KeepOnlyDownward",false);
  KeepOnlyDownwardCmd->SetDefaultValue((G4bool)false);
  KeepOnlyDownwardCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  */  

  RootFileCmd = new G4UIcmdWithAString("/root/RootFile",this);
  RootFileCmd->SetGuidance("Select the Root output file");
  RootFileCmd->SetGuidance("  Choice : Choose the root filename");
  RootFileCmd->SetParameterName("RootFileName",false);
  RootFileCmd->SetDefaultValue((G4String)"DmpSimu");
  RootFileCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  CalEcutCmd = new G4UIcmdWithADoubleAndUnit("/root/CalEcut",this);
  CalEcutCmd->SetGuidance("Minimum energy (and unit) in calorimeter for saving event to root file.");
  CalEcutCmd->SetParameterName("CalEcut",false);
  CalEcutCmd->SetDefaultValue((G4double)0.*MeV);
  CalEcutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SiDigicutCmd = new G4UIcmdWithAnInteger("/root/SiDigicut",this);
  SiDigicutCmd->SetGuidance("Minimum number of SiDigi in STK for saving event to root file.");
  SiDigicutCmd->SetParameterName("SiDigicut",false);
  SiDigicutCmd->SetDefaultValue((G4int)-1);
  SiDigicutCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


}

DmpRootEventDataMessenger::~DmpRootEventDataMessenger()
{
  //delete GenerationOnlyCmd;
  //delete KeepOnlyDownwardCmd;
  //delete RootGenDebugCmd;
  delete RootFileCmd;
  //delete CalEcutCmd;
  //delete SiDigicutCmd;
}

void DmpRootEventDataMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  	

  if( command == RootGenDebugCmd )
    { 
      dmpRootEventDataManager->SetRootGenDebug(RootGenDebugCmd->GetNewBoolValue(newValue));
      //G4cout << " new value  "<< RootGenDebugCmd->GetNewBoolValue(newValue) << G4endl;
   
    }
  /***
  if( command == GenerationOnlyCmd )
    { 
      dmpRootNtupleManager->SetGenerationOnly(GenerationOnlyCmd->GetNewBoolValue(newValue));
   
    }
  ***/ 
  /***	
  if( command == KeepOnlyDownwardCmd )
    { 
      dmpRootEventDataManager->SetKeepOnlyDownward(KeepOnlyDownwardCmd->GetNewBoolValue(newValue));
   
    }
 ***/
 if( command == RootFileCmd )
    { 
     dmpRootEventDataManager->SetRootFile(newValue);
   
    }

 if( command == CalEcutCmd )
    { 
     dmpRootEventDataManager->SetCalEcut(CalEcutCmd->GetNewDoubleValue(newValue));
      //G4cout << " new value  "<< CalEcutCmd->GetNewDoubleValue(newValue) << G4endl;   
    }
 if( command == SiDigicutCmd )
    { 
     dmpRootEventDataManager->SetSiDigicut(SiDigicutCmd->GetNewIntValue(newValue));
      //G4cout << " new value  "<< CalEcutCmd->GetNewDoubleValue(newValue) << G4endl;   
    }

}







