/*
 *  $Id: DmpSimSvcBoot.cc, 2014-04-12 23:14:20 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 12/04/2014
*/

#include "G4RunManager.hh"
#include "G4PhysListFactory.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
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
  fPhyList(0),
  fVisMgr(0),
  fPhyListName("QGSP_BIC")
{
  fRunMgr = new G4RunManager();
  fPhyFactory = new G4PhysListFactory();
  fDetector = new DmpSimDetector();
#ifdef G4VIS_USE
  fVisMgr = new G4VisExecutive();
#endif
}

//-------------------------------------------------------------------
DmpSimSvcBoot::~DmpSimSvcBoot(){
  delete fRunMgr;
  delete fPhyFactory;
  delete fDetector;
#ifdef G4VIS_USE
  delete fVisMgr;
#endif
}

//-------------------------------------------------------------------
void DmpSimSvcBoot::Set(const std::string &type,const std::string &argv){
  if(type == "Physics"){
    fPhyListName = argv;
  }else if(type == "Satellite/Gdml"){
  //}else if(type.find("Satellite/Gdml") != std::string::npos){
    fDetector->SetSatGdml(argv);
  }
}

//-------------------------------------------------------------------
bool DmpSimSvcBoot::Initialize(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  fRunMgr->SetUserInitialization(fDetector);
  fRunMgr->SetUserInitialization(fPhyFactory->GetReferencePhysList(fPhyListName));
  fRunMgr->SetUserAction(new DmpSimPrimaryGeneratorAction);      // only Primary Generator is mandatory
  fRunMgr->SetUserAction(new DmpSimRunAction);
  fRunMgr->SetUserAction(new DmpSimEventAction);
  fRunMgr->SetUserAction(new DmpSimTrackingAction);
  fRunMgr->Initialize();
#ifdef G4VIS_USE
  // Visualization manager
  fVisMgr->Initialize();
#endif
  return true;
}

//-------------------------------------------------------------------
bool DmpSimSvcBoot::Finalize(){
  return true;
}


