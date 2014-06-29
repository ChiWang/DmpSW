/*
 *  $Id: DmpSimAlg.cc, 2014-06-10 16:04:34 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 10/06/2014
*/

#include "DmpSimAlg.h"
#include "DmpSimRunManager.h"
#include "G4PhysListFactory.hh"
#include "DmpSimDetector.h"
#include "DmpSimPrimaryGeneratorAction.h"
#include "DmpSimTrackingAction.h"
#include "DmpCore.h"
#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

//-------------------------------------------------------------------
DmpSimAlg::DmpSimAlg()
 :DmpVAlg("Sim/Alg/RunManager"),
  fSimRunMgr(0),
  fPhyFactory(0),
  fMacFile("VIS"),
  fPhyListName("QGSP_BIC"),
  fEventID(0)
{
  fPhyFactory = new G4PhysListFactory();
  OptMap.insert(std::make_pair("Physics",0));
  OptMap.insert(std::make_pair("Gdml",1));
  OptMap.insert(std::make_pair("Nud/DeltaTime",2));
  OptMap.insert(std::make_pair("MacFile",3));
}

//-------------------------------------------------------------------
DmpSimAlg::~DmpSimAlg(){
  delete fSimRunMgr;
  delete fPhyFactory;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include "DmpEvtMCNudMSD.h"
void DmpSimAlg::Set(const std::string &type,const std::string &argv){
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
#include <stdlib.h>     // getenv()
bool DmpSimAlg::Initialize(){
// set random seed
  gCore->Set("Seed","Time");
// set G4 kernel
  fSimRunMgr = new DmpSimRunManager();
  fSimRunMgr->SetUserInitialization(fPhyFactory->GetReferencePhysList(fPhyListName));
  fSimRunMgr->SetUserAction(new DmpSimPrimaryGeneratorAction());      // only Primary Generator is mandatory
  fSimRunMgr->SetUserInitialization(new DmpSimDetector());
  fSimRunMgr->SetUserAction(new DmpSimTrackingAction());
  fSimRunMgr->Initialize();
// boot simulation
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
    // if not vis mode, do some prepare for this run. refer to G4RunManagr::BeamOn()
    if(fSimRunMgr->ConfirmBeamOnCondition()){
      fSimRunMgr->ConstructScoringWorlds();
      fSimRunMgr->RunInitialization();
      // *
      // *  TODO:  check G4RunManager::InitializeEventLoop(the third argument right?)
      // *
      fSimRunMgr->InitializeEventLoop(gCore->GetMaxEventNumber(),fMacFile.c_str(),gCore->GetMaxEventNumber());
    }else{
      DmpLogError<<"G4RunManager::Initialize() failed"<<DmpLogEndl;
      return false;
    }
  }
  return fIniStatus;
}

//-------------------------------------------------------------------
bool DmpSimAlg::ProcessThisEvent(){
  if("VIS" == fMacFile){
    return true;
  }
  if(fSimRunMgr->SimOneEvent(fEventID)){
    ++fEventID;
    return true;
  }
  return false;
}

//-------------------------------------------------------------------
bool DmpSimAlg::Finalize(){
  if("VIS" != fMacFile){
    fSimRunMgr->TerminateEventLoop();
    fSimRunMgr->RunTermination();
  }
  return true;
}
