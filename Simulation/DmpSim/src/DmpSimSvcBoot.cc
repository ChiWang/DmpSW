/*
 *  $Id: DmpSimSvcBoot.cc, 2014-04-15 21:27:23 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 12/04/2014
*/

#include "G4RunManager.hh"
#include "G4PhysListFactory.hh"
#include "DmpSimDetector.h"
#include "DmpSimPrimaryGeneratorAction.h"
#include "DmpSimRunAction.h"
#include "DmpSimEventAction.h"
#include "DmpSimTrackingAction.h"
#include "DmpSimSvcBoot.h"

//-------------------------------------------------------------------
DmpSimSvcBoot::DmpSimSvcBoot()
 :DmpVSvc("Sim/Boot"),
  fRunMgr(0),
  fDetector(0),
  fPhyFactory(0),
  fPhyListName("QGSP_BIC")
{
  fDetector = new DmpSimDetector(); // must create it at here, since will set option before Initialize(). Do NOT "delete fDetector" in destructor, fRunMgr will delete it
}

//-------------------------------------------------------------------
DmpSimSvcBoot::~DmpSimSvcBoot(){
}

//-------------------------------------------------------------------
void DmpSimSvcBoot::Set(const std::string &type,const std::string &argv){
  if(type == "Physics"){
    fPhyListName = argv;
  }else if(type == "Gdml"){
    fDetector->SetGdml(argv);
  }
}

//-------------------------------------------------------------------
bool DmpSimSvcBoot::Initialize(){
  fRunMgr = new G4RunManager();
  fPhyFactory = new G4PhysListFactory();
  // NOT delete them in destructor, since G4RunManager will delete them
  fRunMgr->SetUserInitialization(fDetector);
  fRunMgr->SetUserInitialization(fPhyFactory->GetReferencePhysList(fPhyListName));
  fRunMgr->Initialize();
  fPriGen = new DmpSimPrimaryGeneratorAction();
  if(not fPriGen->Initialize()) return false;
  fRunAct = new DmpSimRunAction();
  if(not fRunAct->Initialize()) return false;
  fEvtAct = new DmpSimEventAction();
  if(not fEvtAct->Initialize()) return false;
  fTrcAct = new DmpSimTrackingAction();
  fRunMgr->SetUserAction(fPriGen);      // only Primary Generator is mandatory
  fRunMgr->SetUserAction(fRunAct);
  fRunMgr->SetUserAction(fEvtAct);
  fRunMgr->SetUserAction(fTrcAct);
  return true;
}

//-------------------------------------------------------------------
bool DmpSimSvcBoot::Finalize(){
  delete fRunMgr;
  delete fPhyFactory;
  return true;
}


