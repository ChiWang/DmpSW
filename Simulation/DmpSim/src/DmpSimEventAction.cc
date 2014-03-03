/*
 *  $Id: DmpSimEventAction.cc, 2014-03-03 23:30:34 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

// *
// *  TODO:  delete old useless codes from svn
// *
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4DigiManager.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

#include "DmpSimEventAction.h"
#include "DmpSimDataManager.h"
#include "DmpSimStkHit.h"
#include "DmpSimDigitization.h"

DmpSimEventAction::DmpSimEventAction()
  :stkHitCollID(-1),bgoHitCollID(-1),psdHitCollID(-1), drawFlag("all")
{
  //set the digitizer to the G4DigiManager
  G4DigiManager *fDM = G4DigiManager::GetDMpointer();
  
  DmpSimDigitization * myDM = new DmpSimDigitization( "DmpSimDigitization" );
  fDM->AddNewModule(myDM);
}

DmpSimEventAction::~DmpSimEventAction()
{
}

void DmpSimEventAction::BeginOfEventAction(const G4Event *aEvent){
  //G4int evtNb = aEvent->GetEventID();
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
  //DmpSimDataManager::GetInstance()->BeginOfEventAction()
}

void DmpSimEventAction::EndOfEventAction(const G4Event* aEvent){
  //G4int event_id = aEvent->GetEventID();
  G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
  DmpSimStkHitsCollection* THC = 0;

  G4DigiManager * fDM = G4DigiManager::GetDMpointer();
  
  if (HCE)
    {      
      THC = (DmpSimStkHitsCollection*)(HCE->GetHC(stkHitCollID));
      /***
      if (THC)
	{
	  int n_hit = THC->entries();
	  G4cout <<G4endl;
	  G4cout << "Number of tracker hits in this event =  " << n_hit << G4endl;
	}
      ***/

      DmpSimDigitization * myDM = 
	(DmpSimDigitization*)fDM->FindDigitizerModule( "DmpSimDigitization" );
      myDM->Digitize();
    }
 
  //ask ntupleManager to fill ntuple data vectors 
  DmpSimDataManage::GetInstance()->FillEvent(aEvent);
}

