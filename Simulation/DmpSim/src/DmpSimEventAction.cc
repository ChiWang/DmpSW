/*
 *  $Id: DmpSimEventAction.cc, 2014-03-04 19:57:07 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

/*
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4DigiManager.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include "DmpSimStkHit.h"
#include "DmpSimDigitization.h"
*/
#include "G4Event.hh"
#include "DmpSimEventAction.h"
#include "DmpSimDataManager.h"

DmpSimEventAction::DmpSimEventAction()
 :fDataMan(0)
{
  fDataMan = DmpSimDataManager::GetInstance();
// *
// *  TODO: add digitizer here
// *
  //set the digitizer to the G4DigiManager
  //G4DigiManager *fDM = G4DigiManager::GetDMpointer();
  //DmpSimDigitization * myDM = new DmpSimDigitization( "DmpSimDigitization" );
  //fDM->AddNewModule(myDM);
}

DmpSimEventAction::~DmpSimEventAction(){
}

void DmpSimEventAction::BeginOfEventAction(const G4Event *aEvent){
#ifdef DmpDebug
  std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"Event ID = "<<aEvent->GetEventID()<<std::endl;
#endif
  /* useless
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
  */
  fDataMan->UpdateEventHeader(aEvent);
}

void DmpSimEventAction::EndOfEventAction(const G4Event *aEvent){
  fDataMan->Digitize();
  fDataMan->FillEvent();
/*
// *
// *  TODO: add digitizer here
// *
  G4DigiManager *fDM = G4DigiManager::GetDMpointer();
  G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
  DmpSimStkHitsCollection *THC = 0;
  if(HCE){
    THC = (DmpSimStkHitsCollection*)(HCE->GetHC(stkHitCollID));
    //if (THC){
	//int n_hit = THC->entries();
	//G4cout <<G4endl;
	//G4cout << "Number of tracker hits in this event =  " << n_hit << G4endl;
	//}
    DmpSimDigitization * myDM = (DmpSimDigitization*)fDM->FindDigitizerModule( "DmpSimDigitization" );
    myDM->Digitize();
  }
  */
}

