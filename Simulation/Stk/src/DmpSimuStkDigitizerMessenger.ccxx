// Description: This class hinerits from G4UImessenger. It is used to
// pass user command to DmpSimuStkDigitizer
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpSimuStkDigitizerMessenger.hh"

#include "DmpSimuStkDigitizer.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

DmpSimuStkDigitizerMessenger::DmpSimuStkDigitizerMessenger
(DmpSimuStkDigitizer* digitizer)
  :dmpSimuDigitizer(digitizer)
{ 
  ThresholdCmd = new G4UIcmdWithADoubleAndUnit("/StkDigitizer/Threshold",this);
  ThresholdCmd->SetGuidance("Energy deposition threshold for STK digi generation");
  ThresholdCmd->SetParameterName("choice",true);
  ThresholdCmd->SetDefaultValue((G4double)20.*keV);
  ThresholdCmd->SetRange("Threshold >=0.");
  ThresholdCmd->SetUnitCategory("Energy");  
  ThresholdCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DmpSimuStkDigitizerMessenger::~DmpSimuStkDigitizerMessenger()
{
  delete ThresholdCmd;
}

void DmpSimuStkDigitizerMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  if( command == ThresholdCmd )
    { 
      dmpSimuDigitizer->SetThreshold
	(ThresholdCmd->GetNewDoubleValue(newValue));
    }
}












