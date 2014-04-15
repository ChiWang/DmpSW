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
  fPhyList(0),
  fPhyListName("QGSP_BIC")
{
  fDetector = new DmpSimDetector();     // NOT delete it in destructot, since G4RunManager will delete it 
}

//-------------------------------------------------------------------
DmpSimSvcBoot::~DmpSimSvcBoot(){
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
  fRunMgr = new G4RunManager();
  fPhyFactory = new G4PhysListFactory();
  fRunMgr->SetUserInitialization(fDetector);
  fRunMgr->SetUserInitialization(fPhyFactory->GetReferencePhysList(fPhyListName));
  fRunMgr->Initialize();
  fRunMgr->SetUserAction(new DmpSimPrimaryGeneratorAction);      // only Primary Generator is mandatory
  fRunMgr->SetUserAction(new DmpSimRunAction);
  fRunMgr->SetUserAction(new DmpSimEventAction);
  fRunMgr->SetUserAction(new DmpSimTrackingAction);
  return true;
}

//-------------------------------------------------------------------
bool DmpSimSvcBoot::Finalize(){
  delete fRunMgr;
  delete fPhyFactory;
  return true;
}


