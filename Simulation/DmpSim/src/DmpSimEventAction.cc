/*
 *  $Id: DmpSimEventAction.cc, 2014-03-05 17:11:25 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifdef DmpDebug
#include <iostream>
#include "G4Event.hh"
#endif
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
//#include "G4Event.hh"
*/
#include "DmpSimEventAction.h"
#include "DmpSimDataManager.h"

DmpSimEventAction::DmpSimEventAction()
 :fDataMgr(0)
{
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fDataMgr = DmpSimDataManager::GetInstance();
// *
// *  TODO: add digitizer here
// *
  //set the digitizer to the G4DigiManager
  //G4DigiManager *fDM = G4DigiManager::GetDMpointer();
  //DmpSimDigitization * myDM = new DmpSimDigitization( "DmpSimDigitization" );
  //fDM->AddNewModule(myDM);
}

DmpSimEventAction::~DmpSimEventAction(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
}

void DmpSimEventAction::BeginOfEventAction(const G4Event *aEvent){
#ifdef DmpDebug
  std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"\tEvent ID = "<<aEvent->GetEventID()<<std::endl;
#endif
  fDataMgr->Reset();
  fDataMgr->UpdateEventHeader(aEvent);
}

void DmpSimEventAction::EndOfEventAction(const G4Event *aEvent){
  fDataMgr->Digitize();
  fDataMgr->FillEvent();
}

