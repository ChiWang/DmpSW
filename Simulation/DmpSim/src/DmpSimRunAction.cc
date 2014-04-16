/*
 *  $Id: DmpSimRunAction.cc, 2014-04-16 11:15:19 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/03/2014
*/

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include <time.h>
#include "CLHEP/Random/Random.h"

#include "DmpSimRunAction.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpServiceManager.h"

//-------------------------------------------------------------------
DmpSimRunAction::DmpSimRunAction()
 :fDataMgr(0)
{
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
}

//-------------------------------------------------------------------
DmpSimRunAction::~DmpSimRunAction(){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
}

//-------------------------------------------------------------------
void DmpSimRunAction::BeginOfRunAction(const G4Run *aRun){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"Run ID = "<<aRun->GetRunID()<<std::endl;
  fDataMgr->BookBranch(); 
// *  TODO: engine not works...
/*
  //Random Engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = time((time_t*)NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  CLHEP::HepRandom::showEngineStatus(); 
  */

#ifdef G4VIS_USE
  if(G4VVisManager::GetConcreteInstance()){
    G4UImanager *uiManager = G4UImanager::GetUIpointer();
    uiManager->ApplyCommand("vis/clear/view");
  }
#endif
}

//-------------------------------------------------------------------
void DmpSimRunAction::EndOfRunAction(const G4Run* aRun){
#ifdef DmpDebug
  G4cout << "End of Run, saving the root file" << G4endl;
#endif
  fDataMgr->SaveOutput();
  /***
  if ( fSaveRndm ) { 
    G4int runNumber = run->GetRunID();
    std::ostringstream fileName;
    fileName << "run" << runNumber << "end.rndm";
    CLHEP::HepRandom::saveEngineStatus(fileName.str().c_str()); 
    CLHEP::HepRandom::showEngineStatus();
  }     
  ***/
}

//-------------------------------------------------------------------
bool DmpSimRunAction::Initialize(){
/*
 *  if get fDataMgr from gDmpSvcMgr in Constructor, must create service in strict order. So, better get it in Initialize()
 *
 */
  fDataMgr = (DmpSimSvcDataMgr*)gDmpSvcMgr->Get("Sim/DataMgr");
  return fDataMgr;
}


