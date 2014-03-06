/*
 *  $Id: DmpSimulationMain.cc, 2014-03-03 21:18:50 chi $
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

#include "DmpSimDataManager.h"

int main(int argc, char* argv[]){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
  G4RunManager *runManager = new G4RunManager();

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
  G4VisManager *visManager = new G4VisExecutive;
  visManager->Initialize();
#endif  

  // UI interface manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  if (argc!=1){   // batch mode
    G4String fileName = argv[1];
    UImanager->ApplyCommand("/control/execute " + fileName);
  }else{   // interactive mode : define UI session
#ifdef G4UI_USE
#ifdef DmpDebug
    G4String prefix = "./share";
#else
    G4String prefix = (G4String)getenv("DMPSWSYS")+"/share/TestRelease/Simulation";
#endif
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute "+prefix+"/vis.mac");
#endif
    if (ui->IsGUI()){
      UImanager->ApplyCommand("/control/execute "+prefix+"/gui.mac");
    }
    ui->SessionStart();
    delete ui;
#endif
  }

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
  DmpSimDataManager::Vanish();  // remove instance of DmpSimDataManager
  return 0;
}


