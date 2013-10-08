// Description: This class hinerits from G4VDigitizerModule. It is used to
// manage the digitization of all the sub-detectors  
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpSimDigitization.hh"
#include "DmpSimDigStk.hh"

#include "DmpSimDigitizerPsd.hh"
#include "DmpSimHitPsd.hh"

#include "DmpSimDigitizerBgo.hh"
#include "DmpSimHitBgo.hh"

#include "DmpSimDigitizerStk.hh"
#include "DmpSimHitStk.hh"

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"

#include <vector>

DmpSimDigitization::DmpSimDigitization(G4String name)
  :G4VDigitizerModule(name)
{

  //set the digitizer to the G4DigiManager
  G4DigiManager * fDM = G4DigiManager::GetDMpointer();

  DmpSimDigitizerPsd* dmpSimPsdDigitizer = new DmpSimDigitizerPsd( "DmpSimDigitizerPsd" );
  fDM->AddNewModule(dmpSimPsdDigitizer);

  DmpSimDigitizerBgo* dmpSimBgoDigitizer = new DmpSimDigitizerBgo( "DmpSimDigitizerBgo" );
  fDM->AddNewModule(dmpSimBgoDigitizer);

  DmpSimDigitizerStk* dmpSimStkDigitizer = new DmpSimDigitizerStk( "DmpSimDigitizerStk" );
  fDM->AddNewModule(dmpSimDigitizerStk);
  
}

DmpSimDigitization::~DmpSimDigitization()
{
}

void DmpSimDigitization::Digitize()
{

  G4DigiManager * fDM = G4DigiManager::GetDMpointer();
  DmpSimDigitizerPsd * psdDM = (DmpSimPsdDigitizer*)fDM->FindDigitizerModule( "DmpSimDigitizerPsd" );
  psdDM->Digitize();

  DmpSimDigitizerBgo * bgoDM = (DmpSimBgoDigitizer*)fDM->FindDigitizerModule( "DmpSimDigitizerBgo" );
  bgoDM->Digitize();
 
  DmpSimDigitizerStk * stkDM = (DmpSimDigitizerStk*)fDM->FindDigitizerModule( "DmpSimDigitizerStk" );
  stkDM->Digitize();
  
}









