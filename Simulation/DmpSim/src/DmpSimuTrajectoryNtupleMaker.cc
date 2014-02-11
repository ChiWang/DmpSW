// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimuTrajectoryNtupleMaker.hh"

#include "G4TrajectoryContainer.hh"
#include "G4VTrajectoryPoint.hh"
#include "G4VTrajectory.hh"
#include "G4Trajectory.hh"
#include "G4TransportationManager.hh"
#include "G4Event.hh"
#include "G4Run.hh"

#include "TTree.h"

DmpSimuTrajectoryNtupleMaker::DmpSimuTrajectoryNtupleMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  //debugEvent = -100; //-100 no event
}

DmpSimuTrajectoryNtupleMaker::~DmpSimuTrajectoryNtupleMaker()
{
}

void DmpSimuTrajectoryNtupleMaker::book(const G4Run* aRun, TTree* aTree)
{
  tree = aTree;
 //book ntuple branches and define ntuple data vectors here 
 tree->Branch("tt_pvtrj_trackID",    &tt_pvtrj_trackID);
 tree->Branch("tt_pvtrj_stop_vo",    &tt_pvtrj_stop_vo);
 tree->Branch("tt_pvtrj_stop_index", &tt_pvtrj_stop_index);
 tree->Branch("tt_pvtrj_stop_x", &tt_pvtrj_stop_x);
 tree->Branch("tt_pvtrj_stop_y", &tt_pvtrj_stop_y);
 tree->Branch("tt_pvtrj_stop_z", &tt_pvtrj_stop_z);

 tree->Branch("tt_ele_px",  &tt_ele_px  );
 tree->Branch("tt_ele_py",  &tt_ele_py  );
 tree->Branch("tt_ele_pz",  &tt_ele_pz  );
 tree->Branch("tt_ele_ekin",&tt_ele_ekin);
 tree->Branch("tt_ele_trackID",    &tt_ele_trackID);
 tree->Branch("tt_ele_parentID",   &tt_ele_parentID);
 tree->Branch("tt_ele_stop_vo",    &tt_ele_stop_vo);
 tree->Branch("tt_ele_stop_index", &tt_ele_stop_index);
 tree->Branch("tt_ele_stop_x",  &tt_ele_stop_x);
 tree->Branch("tt_ele_stop_y",  &tt_ele_stop_y);
 tree->Branch("tt_ele_stop_z",  &tt_ele_stop_z);

 tree->Branch("tt_pos_px",  &tt_pos_px  );
 tree->Branch("tt_pos_py",  &tt_pos_py  );
 tree->Branch("tt_pos_pz",  &tt_pos_pz  );
 tree->Branch("tt_pos_ekin",&tt_pos_ekin);
 tree->Branch("tt_pos_trackID",    &tt_pos_trackID);
 tree->Branch("tt_pos_parentID",   &tt_pos_parentID);
 tree->Branch("tt_pos_stop_vo",    &tt_pos_stop_vo);
 tree->Branch("tt_pos_stop_index", &tt_pos_stop_index);
 tree->Branch("tt_pos_stop_x",  &tt_pos_stop_x);
 tree->Branch("tt_pos_stop_y",  &tt_pos_stop_y);
 tree->Branch("tt_pos_stop_z",  &tt_pos_stop_z);

 tt_sec_n = 0;

 //tt_sec_px     = new std::vector<double>();
 //tt_sec_py     = new std::vector<double>();
 //tt_sec_pz     = new std::vector<double>();
 //tt_sec_ekin   = new std::vector<double>();
 //tt_sec_stop_x = new std::vector<double>();
 //tt_sec_stop_y = new std::vector<double>();
 //tt_sec_stop_z = new std::vector<double>();
 //tt_sec_trackID    = new std::vector<int>();
 //tt_sec_parentID   = new std::vector<int>();
 //tt_sec_stop_index = new std::vector<int>();
 //tt_sec_stop_vo    = new std::vector<std::string>();
 //tt_sec_charge     = new std::vector<int>();
 //tt_sec_pdg        = new std::vector<int>();

 tree->Branch("tt_sec_n",      &tt_sec_n,   "tt_sec_n/i"  );
 /***
 tree->Branch("tt_sec_px",       &tt_sec_px);
 tree->Branch("tt_sec_py",       &tt_sec_py);
 tree->Branch("tt_sec_pz",       &tt_sec_pz);
 tree->Branch("tt_sec_ekin",     &tt_sec_ekin);
 tree->Branch("tt_sec_stop_x",   &tt_sec_stop_x);
 tree->Branch("tt_sec_stop_y",   &tt_sec_stop_y);
 tree->Branch("tt_sec_stop_z",   &tt_sec_stop_z);
 tree->Branch("tt_sec_trackID",    &tt_sec_trackID);
 tree->Branch("tt_sec_parentID",   &tt_sec_parentID);
 tree->Branch("tt_sec_stop_index", &tt_sec_stop_index);
 tree->Branch("tt_sec_stop_vo",    &tt_sec_stop_vo);
 tree->Branch("tt_sec_charge",     &tt_sec_charge);
 tree->Branch("tt_sec_pdg",        &tt_sec_pdg);
 ***/
}

void DmpSimuTrajectoryNtupleMaker::beginEvent(const G4Event* evt)
{
  //set event number
  eventNumber = evt->GetEventID();
 //clear all ntuple data vectors here
 tt_sec_n = 0;

 //tt_sec_px      -> clear();
 //tt_sec_py      -> clear();
 //tt_sec_pz      -> clear();
 //tt_sec_ekin    -> clear();
 //tt_sec_stop_x  -> clear();
 //tt_sec_stop_y  -> clear();
 //tt_sec_stop_z  -> clear();
 //tt_sec_trackID     -> clear();
 //tt_sec_parentID    -> clear();
 //tt_sec_stop_index  -> clear();
 //tt_sec_stop_vo     -> clear();
 //tt_sec_charge      -> clear();
 //tt_sec_pdg         -> clear();       
}

void DmpSimuTrajectoryNtupleMaker::FillEvent(const G4Event* evt)
{
  G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
  G4int n_trajectories = trajectoryContainer->entries();
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
  tt_pvtrj_trackID = -1;
  tt_pvtrj_stop_vo = "";
  tt_pvtrj_stop_x = 0;
  tt_pvtrj_stop_y = 0;
  tt_pvtrj_stop_z = 0;

  tt_ele_trackID = -1;
  tt_ele_parentID = -1;
  tt_ele_stop_vo = "";
  tt_ele_stop_x = 0;
  tt_ele_stop_y = 0;
  tt_ele_stop_z = 0;

  tt_pos_trackID = -1;
  tt_pos_parentID = -1;
  tt_pos_stop_vo = "";
  tt_pos_stop_x = 0;
  tt_pos_stop_y = 0;
  tt_pos_stop_z = 0;

  tt_sec_n = 0;

  if(trjPrimary) {
    G4String stopAt = navigator->LocateGlobalPointAndSetup(trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())->GetName();
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
    else if(stopAt == "PlaneThinW")       vindex = 10; 
    else if(stopAt == "PlaneThickW")    vindex = 11; 

    tt_pvtrj_trackID = trjPrimary->GetTrackID();
    tt_pvtrj_stop_index = vindex;
    tt_pvtrj_stop_vo    = stopAt;
    tt_pvtrj_stop_x = trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition().x();
    tt_pvtrj_stop_y = trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition().y();
    tt_pvtrj_stop_z = trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition().z();

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
      tt_ele_px   = trjEle->GetInitialMomentum().x();
      tt_ele_py   = trjEle->GetInitialMomentum().y();
      tt_ele_pz   = trjEle->GetInitialMomentum().z();
      tt_ele_ekin = ((G4Trajectory*) trjEle)->GetInitialKineticEnergy();
      //check starting point
      if( trjEle->GetPoint(0)->GetPosition() !=trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())
	G4cout << "WARNING from HistoManager: Event " << evt->GetEventID() << " conversion position not matching for electron!!!! " << trjEle->GetPoint(0)->GetPosition() << " " << trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition() << G4endl;

      G4String stopAt = navigator->LocateGlobalPointAndSetup(trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition())->GetName();
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
      else if(stopAt == "PlaneThinW")       vindex = 10; 
      else if(stopAt == "PlaneThickW")    vindex = 11; 

      tt_ele_trackID  = trjEle->GetTrackID();
      tt_ele_parentID = trjEle->GetParentID();
      tt_ele_stop_index = vindex;
      tt_ele_stop_vo = stopAt;
      tt_ele_stop_x = trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition().x();
      tt_ele_stop_y = trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition().y();
      tt_ele_stop_z = trjEle->GetPoint(trjEle->GetPointEntries()-1)->GetPosition().z();

    }

    if(trjPos) {
      tt_pos_px   = trjPos->GetInitialMomentum().x();
      tt_pos_py   = trjPos->GetInitialMomentum().y();
      tt_pos_pz   = trjPos->GetInitialMomentum().z();
      tt_pos_ekin = ((G4Trajectory*) trjPos)->GetInitialKineticEnergy();
      if( trjPos->GetPoint(0)->GetPosition() !=trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition())
	G4cout << "WARNING from HistoManager: Event " << evt->GetEventID() << " conversion position not matching for positron!!!! " << trjPos->GetPoint(0)->GetPosition() << " " << trjPrimary->GetPoint(trjPrimary->GetPointEntries()-1)->GetPosition() << G4endl;

      G4String stopAt = navigator->LocateGlobalPointAndSetup(trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition())->GetName();
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
      else if(stopAt == "PlaneThinW")       vindex = 10; 
      else if(stopAt == "PlaneThickW")    vindex = 11; 

      tt_pos_trackID = trjPos->GetTrackID();
      tt_pos_parentID = trjPos->GetParentID();
      tt_pos_stop_index = vindex;
      tt_pos_stop_vo = stopAt;
      tt_pos_stop_x = trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition().x();
      tt_pos_stop_y = trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition().y();
      tt_pos_stop_z = trjPos->GetPoint(trjPos->GetPointEntries()-1)->GetPosition().z();
    }

    for (G4int i=0; i<n_trajectories; i++) { 
      G4VTrajectory* trj = ((*(evt->GetTrajectoryContainer()))[i]);
      if(trj->GetParentID()==trjPrimary->GetTrackID() ) {
	if(tt_pvtrj_stop_x == trj->GetPoint(0)->GetPosition().x() && 
	   tt_pvtrj_stop_y == trj->GetPoint(0)->GetPosition().y() && 
	   tt_pvtrj_stop_z == trj->GetPoint(0)->GetPosition().z() ){
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
	     ++tt_sec_n;
	}
      }
    } 
    //G4cout << "   number of secondaries : " << tt_sec_n << G4endl;
  }


}

