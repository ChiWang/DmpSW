// Description: This class hinerits from G4UserEventAction. It is used to
// access information in the G4Event and process them, for example digitization  
// and storage in the output ntuple
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpSimEventAction.hh"

#include "DmpSimRootNtupleManager.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

#include "DmpSimHitStk.hh"
#include "DmpSimDigitization.hh"
#include "G4DigiManager.hh"

DmpSimEventAction::DmpSimEventAction(DmpSimRootNtupleManager* ntupleMgr)
  :stkHitCollID(-1),bgoHitCollID(-1),psdHitCollID(-1), drawFlag("all")
{ 
  //set the digitizer to the G4DigiManager
  G4DigiManager * fDM = G4DigiManager::GetDMpointer();
  
  DmpSimDigitization * myDM = new DmpSimDigitization( "DmpSimDigitization" );
  fDM->AddNewModule(myDM);
  
  ntupleManager = ntupleMgr;
}

DmpSimEventAction::~DmpSimEventAction()
{
}

void DmpSimEventAction::BeginOfEventAction(const G4Event* evt)
{

  //G4int evtNb = evt->GetEventID();
  G4SDManager * SDman = G4SDManager::GetSDMpointer();  
  
  if (stkHitCollID==-1) {
    stkHitCollID = SDman->GetCollectionID("STKHitCollection");
  }
  if(psdHitCollID==-1) {
    psdHitCollID = SDman->GetCollectionID("PSDHitCollection");
  }
  if(bgoHitCollID==-1) {
    bgoHitCollID = SDman->GetCollectionID("BGOHitCollection");
  }
  
  //ask ntupleManager to clear ntuple data vectors
  ntupleManager->beginEvent(evt); 

}

void DmpSimEventAction::EndOfEventAction(const G4Event* evt)
{

  //G4int event_id = evt->GetEventID();
  
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  DmpSimHitsCollectionStk* THC = 0;

  G4DigiManager * fDM = G4DigiManager::GetDMpointer();
  
  if (HCE)
    {      
      THC = (DmpSimHitsCollectionStk*)(HCE->GetHC(stkHitCollID));

      if (THC)
	{
	  int n_hit = THC->entries();
	  G4cout <<G4endl;
	  G4cout << "Number of tracker hits in this event =  " << n_hit << G4endl;
	}
      

      DmpSimDigitization * myDM = 
	(DmpSimDigitization*)fDM->FindDigitizerModule( "DmpSimDigitization" );
      myDM->Digitize();
    }
 
  //ask ntupleManager to fill ntuple data vectors 
  ntupleManager->FillEvent(evt); 


}













