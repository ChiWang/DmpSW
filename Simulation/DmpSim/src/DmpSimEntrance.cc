/*
 *  $Id: DmpSimEntrance.cc, 2014-04-08 13:34:18 chi $
 *  Author(s):
 *    X.Wu () 09/07/2013
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifdef DmpDebug
#include <iostream>
#endif
#include <stdlib.h>     // getenv()
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "DmpSimDetectorConstruction.h"
#include "DmpSimPrimaryGeneratorAction.h"
#include "DmpSimRunAction.h"
#include "DmpSimEventAction.h"
#include "DmpSimTrackingAction.h"
#include "DmpSimEntrance.h"
#include "DmpSimSvcDataMgr.h"

G4RunManager *runManager = 0;
G4VisManager *visManager = 0;
//-------------------------------------------------------------------
void DmpCore::SimInitialize(){
  runManager = new G4RunManager();
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  // Detector
  runManager->SetUserInitialization(new DmpSimDetectorConstruction);
 
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  // Physics List
  G4PhysListFactory *physListFactory = new G4PhysListFactory();
  //G4VUserPhysicsList *physList = physListFactory->GetReferencePhysList("QGSP_BERT");
  G4VUserPhysicsList *physList = physListFactory->GetReferencePhysList("QGSP_BIC");
  runManager->SetUserInitialization(physList);

#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif

  // Initialize() only used for Detector and Physics
  runManager->Initialize();

#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  
  // Set user action classes
  runManager->SetUserAction(new DmpSimPrimaryGeneratorAction);      // only Primary Generator is mandatory
  runManager->SetUserAction(new DmpSimRunAction);
  runManager->SetUserAction(new DmpSimEventAction);
  runManager->SetUserAction(new DmpSimTrackingAction);
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
#ifdef G4VIS_USE
  // Visualization manager
  visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
}

//-------------------------------------------------------------------
void DmpCore::SimExecute(const std::string &inData){
  // UI interface manager
  gSimDataMgr->InputData(inData);
  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  if (inData == "visual"){
    // interactive mode : define UI session
#ifdef G4UI_USE
    char *dummyargv[20]={"visual"};
    G4UIExecutive *ui = new G4UIExecutive(1,dummyargv);
    G4String prefix = (G4String)getenv("DMPSWSYS")+"/share/Simulation/";
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute "+prefix+"DmpSimVis.mac");
#endif
    if (ui->IsGUI()){
      UImanager->ApplyCommand("/control/execute "+prefix+"DmpSimGUI.mac");
    }
    ui->SessionStart();
    delete ui;
#endif
  }else{
    UImanager->ApplyCommand("/control/execute " + inData);        // batch mode
  }
}

//-------------------------------------------------------------------
void DmpCore::SimClear(){
#ifdef G4VIS_USE
  if(visManager !=0 ){
    delete visManager;
    visManager = 0;
  }
#endif
  if(runManager !=0 ){
    delete runManager;
    runManager = 0;
  }
}


