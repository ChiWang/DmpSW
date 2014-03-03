/*
 *  $Id: DmpSimulationMain.cc, 2014-03-03 21:18:50 chi $
 *  Author(s):
 *    X.Wu () 09/07/2013
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

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
#include "DmpSimSteppingAction.h"

#include "DmpSimDataManager.h"

int main(int argc, char* argv[]){
  G4RunManager *runManager = new G4RunManager();

  // Detector
  runManager->SetUserInitialization(new DmpSimDetectorConstruction);
 
  // Physics List
  G4PhysListFactory *physListFactory = new G4PhysListFactory();
  //G4VUserPhysicsList *physList = physListFactory->GetReferencePhysList("QGSP_BERT");
  G4VUserPhysicsList *physList = physListFactory->GetReferencePhysList("QGSP_BIC");
  runManager->SetUserInitialization(physList);

  // Initialize() only used for Detector and Physics
  runManager->Initialize();
  
  // Set user action classes
  runManager->SetUserAction(new DmpSimPrimaryGeneratorAction);      // only Primary Generator is mandatory
  runManager->SetUserAction(new DmpSimRunAction);
  runManager->SetUserAction(new DmpSimEventAction);
  runManager->SetUserAction(new DmpSimTrackingAction);
  runManager->SetUserAction(new DmpSimSteppingAction);

#ifdef G4VIS_USE
  // Visualization manager
  G4VisManager *visManager = new G4VisExecutive;
  visManager->Initialize();
#endif  

  // UI interface manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  if (argc!=1){   // batch mode
    G4String fileName = argv[1];
    UImanager->ApplyCommand("/control/execute" + fileName);
  }else{   // interactive mode : define UI session
#ifdef G4UI_USE
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute vis.mac");
#endif
    if (ui->IsGUI()){
      UImanager->ApplyCommand("/control/execute gui.mac");
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


