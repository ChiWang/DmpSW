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
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#include "DmpSimEntrance.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpKernel.h"

//-------------------------------------------------------------------
void DmpCore::SimExecute(){
  std::string inData = ((DmpSimSvcDataMgr*)gKernel->ServiceManager()->Get("Sim/DataMgr"))->InputData();
  // UI interface manager
  G4UImanager *uiMgr = G4UImanager::GetUIpointer();
  if(inData == "no"){   // interactive mode: define UI session
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
  }else{
    uiMgr->ApplyCommand("/control/execute " + inData);        // batch mode
  }
}


