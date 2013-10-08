// $Id: DmpSim.cc,v 1.00 2013-07-09 17:42:50 xin Exp $
//
// 
// ------------------------------------------------------------
//      GEANT 4 main program
//      DPNC U. Geneva Switzerland
//
//
//      ------------ DmpSim main program ------
//           by X.Wu, (9 July 2013)
//  09.07.13 X.Wu: DAMPE detector simulation executable based on GammaRayTel 
//                     
// ************************************************************

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "DmpSimRootNtupleManager.hh"

//#include "DmpSimPhysicsList.hh"

#include "DmpSimDetectorConstruction.hh"
#include "DmpSimPrimaryGeneratorAction.hh"
#include "DmpSimRunAction.hh"
#include "DmpSimTrackingAction.hh"
#include "DmpSimSteppingAction.hh"
#include "DmpSimEventAction.hh"

//#include "QGSP_BIC.hh"
#include "QGSP_BERT.hh"


// This is the main function 
int main(int argc, char** argv)
{
  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;
  
  // set an ROOT ntuple manager
  DmpSimRootNtupleManager*  ntupleMgr = new DmpSimRootNtupleManager();
  
  // Set mandatory user initialization classes
  DmpSimDetectorConstruction* detector = new DmpSimDetectorConstruction;
  runManager->SetUserInitialization(detector);
 
  // DmpSimPhysicsList to be implemented   
  //runManager->SetUserInitialization(new DmpSimPhysicsList);
  runManager->SetUserInitialization(new QGSP_BERT);
  //runManager->SetUserInitialization(new QGSP_BIC);

  
  // Set mandatory user action classes
  runManager->SetUserAction(new DmpSimPrimaryGeneratorAction);

  // Set optional user action classes
  DmpSimRunAction* runAction = new DmpSimRunAction(ntupleMgr);
  runManager->SetUserAction(runAction);
  
  DmpSimEventAction* eventAction = new DmpSimEventAction(ntupleMgr);
  runManager->SetUserAction(eventAction);
  
  DmpSimTrackingAction* tracking_action = new DmpSimTrackingAction();
  runManager->SetUserAction(tracking_action);
  
  DmpSimSteppingAction* stepping_action = new DmpSimSteppingAction(ntupleMgr);
  runManager->SetUserAction(stepping_action);


  // Initialize G4 kernel
  //   //
  //runManager->Initialize();
       

  // Set visualization (not tested)
#ifdef G4VIS_USE
  // Visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif  
  

  // Get the pointer to the UI manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();


  if (argc!=1)   // batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);

    }
  else
    {  // interactive mode : define UI session
#ifdef G4UI_USE
      G4UIExecutive* ui = new G4UIExecutive(argc, argv);
      //UImanager->ApplyCommand("/control/execute g4.ini");
#ifdef G4VIS_USE
      //UImanager->ApplyCommand("/control/execute vis.mac");
#endif
      if (ui->IsGUI())
        UImanager->ApplyCommand("/control/execute g4.ini");
	printf("Please use the \"/control/execute g4.mac\" to initial the run.\n");
      ui->SessionStart();
      delete ui;
#endif
    }



  // Job termination
  delete ntupleMgr;       
         
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
  return 0;
}

