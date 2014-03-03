//#include <stdlib.h>
#include <time.h>
#include "G4Run.hh"
#include "G4Event.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

#include "DmpSimRunAction.h"
#include "DmpSimDataManager.h"
#include "DmpSimPrimaryGeneratorAction.h"

DmpSimRunAction::DmpSimRunAction(){
}

DmpSimRunAction::~DmpSimRunAction(){
}

void DmpSimRunAction::BeginOfRunAction(const G4Run* aRun){
  G4cout << "### Run ID = " << aRun->GetRunID() << " start." << G4endl;
  DmpSimDataManager   *dataMan = DmpSimDataManager::GetInstance();
  //Random Engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = time((time_t*)NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  CLHEP::HepRandom::showEngineStatus(); 

  rootEventDataManager->book(aRun);
  rootEventDataManager->beginRun(aRun);
#ifdef G4VIS_USE
  if(G4VVisManager::GetConcreteInstance()){
    G4UImanager* UIManager = G4UImanager::GetUIpointer();
    UIManager->ApplyCommand("vis/clear/view");
  }
#endif

}

void DmpSimRunAction::EndOfRunAction(const G4Run* aRun){
  rootEventDataManager->FillRun(aRun, dmpSimPrimaryGeneratorAction);
  G4cout << "End of Run, saving the ntuple " << G4endl;
  rootEventDataManager->save();

  //can also save random seed for multiple jobs of the same simulation
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









