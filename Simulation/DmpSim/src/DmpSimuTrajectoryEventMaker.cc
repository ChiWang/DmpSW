// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimuTrajectoryEventMaker.hh"

#include "DmpG4RunManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectoryPoint.hh"
#include "G4VTrajectory.hh"
#include "G4Trajectory.hh"
#include "G4TransportationManager.hh"

#include "TTree.h"

DmpSimuTrajectoryEventMaker::DmpSimuTrajectoryEventMaker()
  :tree(0)


{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimuTrajectoryEventMaker::~DmpSimuTrajectoryEventMaker()
{
}

void DmpSimuTrajectoryEventMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree = aTree;
  dmpSimuTrajectoryEvent = new DmpEvtSimuTrajectory();
  tree->Branch("DmpEvtSimuTrajectory", "DmpEvtSimuTrajectory",  &dmpSimuTrajectoryEvent);

  // navigator to DAMPE geometry
  DmpG4RunManager* runManager  = (DmpG4RunManager*) G4RunManager::GetRunManager();
  dmpDetector = (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());
}

void DmpSimuTrajectoryEventMaker::beginEvent(const G4Event* evt)
{
  //set event number
  eventNumber = evt->GetEventID();
  dmpSimuTrajectoryEvent->Reset();
}

void DmpSimuTrajectoryEventMaker::FillStep(const G4Step* aStep)
{
}

void DmpSimuTrajectoryEventMaker::FillEvent(const G4Event* evt)
{  
  

  G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
  G4Navigator* navigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();

  G4VTrajectory* trjPrimary = 0;
  for (G4int i=0; i<n_trajectories; i++) { 
    G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
    if(trj->GetParentID()==0) {
      trjPrimary = trj;
      continue;
    }
  }

  //dumpinmg some trajectories
 
  //G4cout << "Number of trajectories in this event =  " << n_trajectories << G4endl;
  G4VTrajectoryPoint* firstpoint = 0;
  G4VTrajectoryPoint*  lastpoint = 0;
  G4int nsteps = 0;
  G4VPhysicalVolume* firstvolume;
  G4VPhysicalVolume* lastvolume;
  /***
  for (G4int i=0; i<n_trajectories; i++) { 
    G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
    firstpoint  = trj->GetPoint(0);
    firstvolume = navigator->LocateGlobalPointAndSetup(firstpoint->GetPosition());
      
    //if(firstvolume->GetName() == "BGODetectorX" || firstvolume->GetName() == "BGODetectorY") {
    //  nsteps = trj->GetPointEntries();
    //lastpoint = trj->GetPoint(nsteps-1);
    //lastvolume = navigator->LocateGlobalPointAndSetup(lastpoint->GetPosition());
    //if(lastvolume->GetName() == "BGODetectorX" || lastvolume->GetName() == "BGODetectorY") continue;
    //if(lastvolume->GetName() == "World" && (lastpoint->GetPosition().z() < firstpoint->GetPosition().z()) ) continue;
    //}
      
    if(trj->GetParentID()==trjPrimary->GetTrackID() ) {
      G4cout << "   trajectory ID= " << trj->GetTrackID() << "  parent ID= " << trj->GetParentID() 
	     << "  PDG code= " << trj->GetPDGEncoding () << "  particle name= " << trj->GetParticleName () 
	     << "  charge= " << trj->GetCharge() <<  G4endl;
      G4cout << "       Initial momentum (MeV): " << trj->GetInitialMomentum().x() << " " <<  trj->GetInitialMomentum().y() 
	     << " " << trj->GetInitialMomentum().z() << G4endl;
      G4cout << "       Initial kinetic energy (MeV): " << ((G4Trajectory*) trj)->GetInitialKineticEnergy() << G4endl;
      G4cout << "       first step at " << firstpoint->GetPosition() << " in volume " << firstvolume->GetName() << G4endl;
      nsteps = trj->GetPointEntries();
      lastpoint  = trj->GetPoint(nsteps-1);
      lastvolume = navigator->LocateGlobalPointAndSetup(lastpoint->GetPosition());
      G4cout << "        last step at " << lastpoint->GetPosition() << " in volume " << lastvolume->GetName() << G4endl;
      //trj->ShowTrajectory();
      G4cout << G4endl;
      G4cout << G4endl;
    }
  }
  ***/

  dmpSimuTrajectoryEvent->pvtrj_trackID = -1;
  dmpSimuTrajectoryEvent->pvtrj_stop_vo = "";
  dmpSimuTrajectoryEvent->pvtrj_stop_x = 0;
  dmpSimuTrajectoryEvent->pvtrj_stop_y = 0;
  dmpSimuTrajectoryEvent->pvtrj_stop_z = 0;

  dmpSimuTrajectoryEvent->electron.trackID = -1;
  dmpSimuTrajectoryEvent->electron.parentID = -1;
  dmpSimuTrajectoryEvent->electron.stop_vo = "";
  dmpSimuTrajectoryEvent->electron.stop_x = 0;
  dmpSimuTrajectoryEvent->electron.stop_y = 0;
  dmpSimuTrajectoryEvent->electron.stop_z = 0;

  dmpSimuTrajectoryEvent->positron.trackID = -1;
  dmpSimuTrajectoryEvent->positron.parentID = -1;
  dmpSimuTrajectoryEvent->positron.stop_vo = "";
  dmpSimuTrajectoryEvent->positron.stop_x = 0;
  dmpSimuTrajectoryEvent->positron.stop_y = 0;
  dmpSimuTrajectoryEvent->positron.stop_z = 0;

  dmpSimuTrajectoryEvent->sec_n = 0;

  if(trjPrimary) {
    G4String stopAt = navigator->LocateGlobalPointAndSetup(trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())->GetName();
    G4int vindex = dmpDetector->getDetectorIndex(stopAt);
    /*
    G4int vindex = -1;
    if(dmpDetector->isWorldVolume(stopAt)) vindex = 0;                                            // if(stopAt == "World") vindex = 0;
    else if(dmpDetector->GetBgoDetectorDescription()->isVolumeBgoBar(stopAt))         vindex = 1; // else if(stopAt == "BGODetectorX" || stopAt == "BGODetectorY" )   vindex = 1;
    else if(dmpDetector->GetStkDetectorDescription()->isVolumeConverter(stopAt))      vindex = 2; // else if(stopAt == "Converter")      vindex = 2;
    else if(dmpDetector->GetStkDetectorDescription()->isVolumeThickConverter(stopAt)) vindex = 3; //else if(stopAt == "ThickConverter") vindex = 3;
    else if(dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTile(stopAt))  vindex = 4; //else if(stopAt == "Active Tile X" || stopAt == "Active Tile Y")  vindex = 4;
    */
    //else if(stopAt == "Plane")          vindex = 5;
    //else if(stopAt == "STKDetectorX"  || stopAt == "STKDetectorY")   vindex  = 6;
    //else if(stopAt == "STK")            vindex = 7;
    //else if(stopAt == "PSD")            vindex = 8;
    //else if(stopAt == "Payload")        vindex = 9;
    //else if(stopAt == "PlaneThinW")       vindex = 10;


    
    dmpSimuTrajectoryEvent->pvtrj_trackID = trjPrimary->GetTrackID();
    dmpSimuTrajectoryEvent->pvtrj_stop_index = vindex;
    dmpSimuTrajectoryEvent->pvtrj_stop_vo    = stopAt;
    dmpSimuTrajectoryEvent->pvtrj_stop_x = trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition().x();
    dmpSimuTrajectoryEvent->pvtrj_stop_y = trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition().y();
    dmpSimuTrajectoryEvent->pvtrj_stop_z = trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition().z();

    G4VTrajectory* trjEle = 0;
    G4VTrajectory* trjPos = 0;
    for (G4int i=0; i<n_trajectories; i++) { 
      G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
      if(trj->GetParentID()==trjPrimary->GetTrackID() && trjPrimary->GetPDGEncoding()==22) {
	if( trj->GetPoint(0)->GetPosition() ==trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition()) {
	  if(trj->GetPDGEncoding()==11)  trjEle = trj;
	  if(trj->GetPDGEncoding()==-11) trjPos = trj;
	}
      }
    }
    //G4cout << "   primary particle stops at : " << tt_pvtrj_stop_x << " " << tt_pvtrj_stop_y << " " << tt_pvtrj_stop_z << ", volume: " << tt_pvtrj_stop_vo  << G4endl;

    if(trjEle) {
      dmpSimuTrajectoryEvent->electron.px   = trjEle->GetInitialMomentum().x();
      dmpSimuTrajectoryEvent->electron.py   = trjEle->GetInitialMomentum().y();
      dmpSimuTrajectoryEvent->electron.pz   = trjEle->GetInitialMomentum().z();
      dmpSimuTrajectoryEvent->electron.ekin = ((G4Trajectory*) trjEle)->GetInitialKineticEnergy();
      //check starting point
      if( trjEle->GetPoint(0)->GetPosition() !=trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())
	G4cout << "WARNING from HistoManager: Event " << evt->GetEventID() << " conversion position not matching for electron!!!! " << trjEle->GetPoint(0)->GetPosition() << " " << trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition() << G4endl;

      G4String stopAt = navigator->LocateGlobalPointAndSetup(trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition())->GetName();
      G4int vindex = dmpDetector->getDetectorIndex(stopAt);
      /*
      G4int vindex = -1;
      if(dmpDetector->isWorldVolume(stopAt)) vindex = 0;                                            // if(stopAt == "World") vindex = 0;
      else if(dmpDetector->GetBgoDetectorDescription()->isVolumeBgoBar(stopAt))         vindex = 1; // else if(stopAt == "BGODetectorX" || stopAt == "BGODetectorY" )   vindex = 1;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeConverter(stopAt))      vindex = 2; // else if(stopAt == "Converter")      vindex = 2;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeThickConverter(stopAt)) vindex = 3; //else if(stopAt == "ThickConverter") vindex = 3;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTile(stopAt))  vindex = 4; //else if(stopAt == "Active Tile X" || stopAt == "Active Tile Y")  vindex = 4;
      */
      //else if(stopAt == "Plane")          vindex = 5;
      //else if(stopAt == "STKDetectorX"  || stopAt == "STKDetectorY")   vindex  = 6;
      //else if(stopAt == "STK")            vindex = 7;
      //else if(stopAt == "PSD")            vindex = 8;
      //else if(stopAt == "Payload")        vindex = 9;
      //else if(stopAt == "PlaneThinW")       vindex = 10;
      //else if(stopAt == "PlaneThickW")    vindex = 11;

      dmpSimuTrajectoryEvent->electron.trackID  = trjEle->GetTrackID();
      dmpSimuTrajectoryEvent->electron.parentID = trjEle->GetParentID();
      dmpSimuTrajectoryEvent->electron.stop_index = vindex;
      dmpSimuTrajectoryEvent->electron.stop_vo = stopAt;
      dmpSimuTrajectoryEvent->electron.stop_x = trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition().x();
      dmpSimuTrajectoryEvent->electron.stop_y = trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition().y();
      dmpSimuTrajectoryEvent->electron.stop_z = trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition().z();

    }

    if(trjPos) {
      dmpSimuTrajectoryEvent->positron.px   = trjPos->GetInitialMomentum().x();
      dmpSimuTrajectoryEvent->positron.py   = trjPos->GetInitialMomentum().y();
      dmpSimuTrajectoryEvent->positron.pz   = trjPos->GetInitialMomentum().z();
      dmpSimuTrajectoryEvent->positron.ekin = ((G4Trajectory*) trjPos)->GetInitialKineticEnergy();
      if( trjPos->GetPoint(0)->GetPosition() !=trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())
	G4cout << "WARNING from HistoManager: Event " << evt->GetEventID() << " conversion position not matching for positron!!!! " << trjPos->GetPoint(0)->GetPosition() << " " << trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition() << G4endl;

      G4String stopAt = navigator->LocateGlobalPointAndSetup(trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition())->GetName();
      G4int vindex= dmpDetector->getDetectorIndex(stopAt);
      /*
      G4int vindex = -1;
      if(dmpDetector->isWorldVolume(stopAt)) vindex = 0;
      else if(dmpDetector->GetBgoDetectorDescription()->isVolumeBgoBar(stopAt))         vindex = 1;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeConverter(stopAt))      vindex = 2;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeThickConverter(stopAt)) vindex = 3;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTile(stopAt))  vindex = 4;
      */
      /*
      if(stopAt == "World") vindex = 0; 
      else if(stopAt == "BGODetectorX" || stopAt == "BGODetectorY" )   vindex = 1; 
      else if(stopAt == "Converter")      vindex = 2; 
      else if(stopAt == "ThickConverter") vindex = 3; 
      else if(stopAt == "Active Tile X" || stopAt == "Active Tile Y")  vindex = 4; 
      else if(stopAt == "Plane")          vindex = 5; 
      else if(stopAt == "STKDetectorX"  || stopAt == "STKDetectorY")   vindex  = 6; 
      else if(stopAt == "STK")            vindex = 7; 
      else if(stopAt == "PSD")            vindex = 8; 
      else if(stopAt == "Payload")        vindex = 9; 
      else if(stopAt == "PlaneThinW")       vindex = 10; 
      else if(stopAt == "PlaneThickW")    vindex = 11;
      */

      dmpSimuTrajectoryEvent->positron.trackID = trjPos->GetTrackID();
      dmpSimuTrajectoryEvent->positron.parentID = trjPos->GetParentID();
      dmpSimuTrajectoryEvent->positron.stop_index = vindex;
      dmpSimuTrajectoryEvent->positron.stop_vo = stopAt;
      dmpSimuTrajectoryEvent->positron.stop_x = trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition().x();
      dmpSimuTrajectoryEvent->positron.stop_y = trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition().y();
      dmpSimuTrajectoryEvent->positron.stop_z = trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition().z();
    }

    for (G4int i=0; i<n_trajectories; i++) { 
      G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
      if(trj->GetParentID()==trjPrimary->GetTrackID() ) {
	if(dmpSimuTrajectoryEvent->pvtrj_stop_x == trj->GetPoint(0)->GetPosition().x() &&
	   dmpSimuTrajectoryEvent->pvtrj_stop_y == trj->GetPoint(0)->GetPosition().y() &&
	   dmpSimuTrajectoryEvent->pvtrj_stop_z == trj->GetPoint(0)->GetPosition().z() ){
	     /***
      firstvolume = navigator->LocateGlobalPointAndSetup(trj->GetPoint(0)->GetPosition());
      G4cout << "   trajectory ID= " << trj->GetTrackID() << "  parent ID= " << trj->GetParentID() 
	     << "  PDG code= " << trj->GetPDGEncoding () << "  particle name= " << trj->GetParticleName () 
	     << "  charge= " << trj->GetCharge() <<  G4endl;
      G4cout << "       Initial momentum (MeV): " << trj->GetInitialMomentum().x() << " " <<  trj->GetInitialMomentum().y() 
	     << " " << trj->GetInitialMomentum().z() << G4endl;
      G4cout << "       Initial kinetic energy (MeV): " << ((G4Trajectory*) trj)->GetInitialKineticEnergy() << G4endl;
      G4cout << "       first step at " << trj->GetPoint(0)->GetPosition() << " in volume " << firstvolume->GetName() << G4endl;
     
      lastpoint  = trj->GetPoint(trj->GetPointEntries()-1);
      lastvolume = navigator->LocateGlobalPointAndSetup(lastpoint->GetPosition());
      G4cout << "        last step at " << lastpoint->GetPosition() << " in volume " << lastvolume->GetName() << G4endl;
      //trj->ShowTrajectory();
      G4cout << G4endl;
      G4cout << G4endl;
	     ***/
	     /***
	  tt_sec_px    -> push_back( trj->GetInitialMomentum().x() );
	  tt_sec_py    -> push_back( trj->GetInitialMomentum().y() );
	  tt_sec_pz    -> push_back( trj->GetInitialMomentum().z() );
	  tt_sec_ekin  -> push_back( ((G4Trajectory*) trj)->GetInitialKineticEnergy() );
	  if( trj->GetPoint(0)->GetPosition() !=trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())
	    G4cout << "WARNING from HistoManager: Event " << evt->GetEventID() << " conversion position not matching for secondary!!!! " << trj->GetPoint(0)->GetPosition() << " " << trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition() << G4endl;
	  
	  G4String stopAt = navigator->LocateGlobalPointAndSetup(trj->GetPoint(trj->GetPointEntries()-1)->GetPosition())->GetName();
	  G4int vindex = -1;
	  if(stopAt == "World") vindex = 0; 
	  else if(stopAt == "BGODetectorX" || stopAt == "BGODetectorY" )   vindex = 1; 
	  else if(stopAt == "Converter")      vindex = 2; 
	  else if(stopAt == "ThickConverter") vindex = 3; 
	  else if(stopAt == "Active Tile X" || stopAt == "Active Tile Y")  vindex = 4; 
	  else if(stopAt == "Plane")          vindex = 5; 
	  else if(stopAt == "STKDetectorX"  || stopAt == "STKDetectorY")   vindex  = 6; 
	  else if(stopAt == "STK")            vindex = 7; 
	  else if(stopAt == "PSD")            vindex = 8; 
	  else if(stopAt == "Payload")        vindex = 9; 
	  else if(stopAt == "PlaneThinW")     vindex = 10; 
	  else if(stopAt == "PlaneThickW")    vindex = 11; 
	  
	  tt_sec_trackID     -> push_back( trj->GetTrackID() );
	  tt_sec_parentID    -> push_back( trj->GetParentID() );
	  tt_sec_stop_index  -> push_back( vindex );
	  tt_sec_stop_vo  -> push_back( stopAt );
	  tt_sec_stop_x   -> push_back( trj->GetPoint(trj->GetPointEntries()-1)->GetPosition().x() );
	  tt_sec_stop_y   -> push_back( trj->GetPoint(trj->GetPointEntries()-1)->GetPosition().y() );
	  tt_sec_stop_z   -> push_back( trj->GetPoint(trj->GetPointEntries()-1)->GetPosition().z() );
	  tt_sec_charge   -> push_back( trj->GetCharge() );
	  tt_sec_pdg      -> push_back( trj->GetPDGEncoding () );
	     ***/
	     ++dmpSimuTrajectoryEvent->sec_n;
	}
      }
    } 
    //G4cout << "   number of secondaries : " << tt_sec_n << G4endl;
  }


}






