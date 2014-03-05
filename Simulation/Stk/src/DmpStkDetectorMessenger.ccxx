// Description: This class hinerits from G4UImessenger. It is used to
// pass user command to DmpStkDetectorDescription
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpStkDetectorMessenger.hh"

#include "DmpStkDetectorDescription.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"

DmpStkDetectorMessenger::DmpStkDetectorMessenger
(DmpStkDetectorDescription* stkDetector)
  :dmpStkDetectorDescription(stkDetector)
{ 

  ThickWCmd = new G4UIcmdWithADoubleAndUnit("/stk/thicknessThickW",this);
  ThickWCmd->SetGuidance("Thickness (and unit) of the thick W plates.");
  ThickWCmd->SetParameterName("choice",false);
  ThickWCmd->SetDefaultValue((G4double)2.*mm);
  ThickWCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}

DmpStkDetectorMessenger::~DmpStkDetectorMessenger()
{
  delete ThickWCmd;

}

void DmpStkDetectorMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  
  /*
  if( command == ThickWCmd )
    { dmpStkDetectorDescription->SetThickConverterThickness(ThickWCmd->GetNewDoubleValue(newValue));}
  */
  
}













