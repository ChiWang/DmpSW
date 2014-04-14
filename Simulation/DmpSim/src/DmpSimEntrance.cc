/*
 *  $Id: DmpSimEntrance.cc, 2014-04-12 23:38:59 chi $
 *  Author(s):
 *    X.Wu () 09/07/2013
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include <stdlib.h>     // getenv()
#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
#include "DmpSimEntrance.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpServiceManager.h"

//-------------------------------------------------------------------
void DmpCore::SimExecute(const std::string &inData){
  ((DmpSimSvcDataMgr*)gDmpSvcMgr->Get("Sim/DataMgr"))->InputData(inData);
  // UI interface manager
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


