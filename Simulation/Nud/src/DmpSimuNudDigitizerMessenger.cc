// Description: This class hinerits from G4UImessenger. It is used to
// pass user command to DmpSimuNudDigitizer
//
// Author(s):
//  - added by Tiekuang Dong 2012/12/23

#include "DmpSimuNudDigitizerMessenger.hh"

#include "DmpSimuNudDigitizer.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

DmpSimuNudDigitizerMessenger::DmpSimuNudDigitizerMessenger
(DmpSimuNudDigitizer* digitizer)
  :dmpSimuDigitizer(digitizer)
{ 
  ThresholdCmd = new G4UIcmdWithADoubleAndUnit("/NudDigitizer/Threshold",this);
  ThresholdCmd->SetGuidance("Energy deposition threshold for NUD digi generation");
  ThresholdCmd->SetParameterName("choice",true);
  ThresholdCmd->SetDefaultValue((G4double)20.*keV);
  ThresholdCmd->SetRange("Threshold >=0.");
  ThresholdCmd->SetUnitCategory("Energy");  
  ThresholdCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DmpSimuNudDigitizerMessenger::~DmpSimuNudDigitizerMessenger()
{
  delete ThresholdCmd;
}

void DmpSimuNudDigitizerMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  if( command == ThresholdCmd )
    { 
      dmpSimuDigitizer->SetThreshold
	(ThresholdCmd->GetNewDoubleValue(newValue));
    }
}












