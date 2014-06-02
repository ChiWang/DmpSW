/*
 *  $Id: DmpSimAlgRunManager.cc, 2014-05-28 20:20:58 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 12/04/2014
*/

#include "G4PhysListFactory.hh"

#include "DmpSimDetector.h"
#include "DmpSimPrimaryGeneratorAction.h"
//#include "DmpSimRunAction.h"
#include "DmpSimTrackingAction.h"
#include "DmpSimAlgRunManager.h"

//-------------------------------------------------------------------
DmpSimAlgRunManager::DmpSimAlgRunManager()
 :DmpVAlg("Sim/Alg/RunManager"),
  fMacFile("VIS"),
  fPhyFactory(0),
  fPhyListName("QGSP_BIC"),
  fEventID(0),
  fBeamOnCondition(false)
{
  OptMap.insert(std::make_pair("Physics",0));
  OptMap.insert(std::make_pair("Gdml",1));
  OptMap.insert(std::make_pair("Nud/DeltaTime",2));
  OptMap.insert(std::make_pair("MacFile",3));
  fPhyFactory = new G4PhysListFactory();
  msgText = "";
}

//-------------------------------------------------------------------
DmpSimAlgRunManager::~DmpSimAlgRunManager(){
  delete fPhyFactory;
  DmpLogDebug<<DmpLogEndl;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <DmpEvtMCNudMSD.h>
void DmpSimAlgRunManager::Set(const std::string &type,const std::string &argv){
  if(OptMap.find(type) == OptMap.end()){
    DmpLogError<<" No argument type "<<type<<DmpLogEndl;
  }
  switch (OptMap[type]){
    case 0:
    {// Physics
      fPhyListName = argv;
      break;
    } 
    case 1:
    {// Gdml
      DmpSimDetector::SetGdml(argv);
      break;
    }
    case 2:
    {// Nud/DeltaTime
      DmpEvtMCNudMSD::SetDeltaTime(boost::lexical_cast<short>(argv));
      break;
    }
    case 3:
    {// MacFile
      fMacFile = argv;
      break;
    }
  }
}

//-------------------------------------------------------------------
#include "DmpCore.h"
#include <time.h>
#include "CLHEP/Random/Random.h"
#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#include <stdlib.h>     // getenv()
bool DmpSimAlgRunManager::Initialise(){
//-------------------------------------------------------------------
// set user actions
  physicsList = fPhyFactory->GetReferencePhysList(fPhyListName);
  kernel->SetPhysics(physicsList);
  userPrimaryGeneratorAction = new DmpSimPrimaryGeneratorAction();      // only Primary Generator is mandatory
  userDetector = new DmpSimDetector();
  //userRunAction = new DmpSimRunAction();
  userTrackingAction = new DmpSimTrackingAction();  eventManager->SetUserAction(userTrackingAction);
  G4RunManager::Initialize();
//-------------------------------------------------------------------
// set random seed
  G4long seed = time((time_t*)NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  //CLHEP::HepRandom::showEngineStatus(); 
//-------------------------------------------------------------------
// if not vis mode, do some prepare for this run. refer to G4RunManagr::BeamOn()
  if("VIS" == fMacFile){    // vis mode
    G4UImanager *uiMgr = G4UImanager::GetUIpointer();
#ifdef G4UI_USE
    char *dummyargv[20]={"visual"};
    G4UIExecutive *ui = new G4UIExecutive(1,dummyargv);
#ifdef G4VIS_USE
    G4VisExecutive *vis = new G4VisExecutive();
    vis->Initialize();
    G4String prefix = (G4String)getenv("DMPSWSYS")+"/share/Simulation/";
    uiMgr->ApplyCommand("/control/execute "+prefix+"DmpSimVis.mac");
#endif
    if (ui->IsGUI()){
      uiMgr->ApplyCommand("/control/execute "+prefix+"DmpSimGUI.mac");
    }
    ui->SessionStart();
    delete ui;
#endif
  }else{    // batch mode
    fBeamOnCondition = ConfirmBeamOnCondition();
    if(fBeamOnCondition){
      ConstructScoringWorlds();
      RunInitialization();
    }else{
      DmpLogError<<"G4RunManager::Initialize() failed"<<DmpLogEndl;
      return false;
    }
// *
// *  TODO:  check G4RunManager::InitializeEventLoop(the third argument right?)
// *
    InitializeEventLoop(gCore->GetMaxEventNumber(),fMacFile.c_str(),gCore->GetMaxEventNumber());
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpSimAlgRunManager::ProcessThisEvent(){
  if("VIS" == fMacFile){
    return true;
  }
  G4RunManager::ProcessOneEvent(fEventID);
  TerminateOneEvent();
  if(runAborted){
    return false;
  }
  ++fEventID;
  return true;
}

//-------------------------------------------------------------------
bool DmpSimAlgRunManager::Finalize(){
  if(fBeamOnCondition && "VIS" != fMacFile){
    TerminateEventLoop();
    RunTermination();
  }
  return true;
}


