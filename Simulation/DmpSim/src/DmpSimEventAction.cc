/*
 *  $Id: DmpSimEventAction.cc, 2014-04-06 15:45:13 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "G4Event.hh"
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
#include "DmpEvtHeader.h"
#include "DmpSimEventAction.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpServiceManager.h"

//-------------------------------------------------------------------
DmpSimEventAction::DmpSimEventAction()
 :fDataMgr(0)
{
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
// *
// *  TODO: add digitizer here
// *
  //set the digitizer to the G4DigiManager
  //G4DigiManager *fDM = G4DigiManager::GetDMpointer();
  //DmpSimDigitization * myDM = new DmpSimDigitization( "DmpSimDigitization" );
  //fDM->AddNewModule(myDM);
}

//-------------------------------------------------------------------
DmpSimEventAction::~DmpSimEventAction(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
}

//-------------------------------------------------------------------
void DmpSimEventAction::BeginOfEventAction(const G4Event *anEvent){
#ifdef DmpDebug
  std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"\tEvent ID = "<<anEvent->GetEventID()<<std::endl;
#endif
  static DmpEvtHeader *eventHeader = fDataMgr->GetEventHeader();
  eventHeader->CountThisEvent();
  eventHeader->SetParticlePdgCode(anEvent->GetPrimaryVertex()->GetPrimary()->GetPDGcode());
}

//-------------------------------------------------------------------
void DmpSimEventAction::EndOfEventAction(const G4Event *anEvent){
  fDataMgr->Digitize();
  fDataMgr->FillEvent();
}

//-------------------------------------------------------------------
bool DmpSimEventAction::Initialize(){
  fDataMgr = (DmpSimSvcDataMgr*)gDmpSvcMgr->Get("Sim/DataMgr");
  return fDataMgr;
}


