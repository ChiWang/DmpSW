// Description: This class hinerits from G4VDigitizerModule. It is used to
// manage the digitization of all the sub-detectors  
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpSimuDigitization.hh"
#include "DmpSimuStkDigi.hh"

#include "DmpSimuPsdDigitizer.hh"
#include "DmpSimuPsdHit.hh"

#include "DmpSimuBgoDigitizer.hh"
#include "DmpSimuBgoHit.hh"

#include "DmpSimuStkDigitizer.hh"
#include "DmpSimuStkHit.hh"

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"

#include <vector>

DmpSimuDigitization::DmpSimuDigitization(G4String name)
  :G4VDigitizerModule(name)
{

  //set the digitizer to the G4DigiManager
  G4DigiManager * fDM = G4DigiManager::GetDMpointer();

  DmpSimuPsdDigitizer* dmpSimuPsdDigitizer = new DmpSimuPsdDigitizer( "DmpSimuPsdDigitizer" );
  fDM->AddNewModule(dmpSimuPsdDigitizer);

  DmpSimuBgoDigitizer* dmpSimuBgoDigitizer = new DmpSimuBgoDigitizer( "DmpSimuBgoDigitizer" );
  fDM->AddNewModule(dmpSimuBgoDigitizer);

  DmpSimuStkDigitizer* dmpSimuStkDigitizer = new DmpSimuStkDigitizer( "DmpSimuStkDigitizer" );
  fDM->AddNewModule(dmpSimuStkDigitizer);
  
}

DmpSimuDigitization::~DmpSimuDigitization()
{
}

void DmpSimuDigitization::Digitize()
{

  G4DigiManager * fDM = G4DigiManager::GetDMpointer();
  DmpSimuPsdDigitizer * psdDM = (DmpSimuPsdDigitizer*)fDM->FindDigitizerModule( "DmpSimuPsdDigitizer" );
  psdDM->Digitize();

  DmpSimuBgoDigitizer * bgoDM = (DmpSimuBgoDigitizer*)fDM->FindDigitizerModule( "DmpSimuBgoDigitizer" );
  bgoDM->Digitize();
 
  DmpSimuStkDigitizer * stkDM = (DmpSimuStkDigitizer*)fDM->FindDigitizerModule( "DmpSimuStkDigitizer" );
  stkDM->Digitize();
  
}









