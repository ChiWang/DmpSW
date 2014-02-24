// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimuStkStepEventMaker.hh"
#include "G4UnitsTable.hh"

#include "G4TrajectoryContainer.hh"
#include "G4VTrajectoryPoint.hh"
#include "G4VTrajectory.hh"
#include "G4Trajectory.hh"
#include "G4VProcess.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "DmpG4RunManager.hh"

#include "DmpDetectorConstruction.hh"
//#include "DmpSimuBgoHit.hh"
#include "DmpSimuStkHit.hh"
#include "DmpSimuStkDigi.hh"
#include "DmpSimuStkDigitizer.hh"

#include "G4RunManager.hh"
#include "G4DigiManager.hh"
#include "G4Run.hh"

#include "TH1D.h"
#include "TTree.h"

DmpSimuStkStepEventMaker::DmpSimuStkStepEventMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event

}

DmpSimuStkStepEventMaker::~DmpSimuStkStepEventMaker()
{
}

void DmpSimuStkStepEventMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree = aTree;
  dmpStkStepEvent = new DmpEvtStkStep();
  tree->Branch("DmpEvtStkStep", "DmpEvtStkStep",  &dmpStkStepEvent);

  // navigator to DAMPE geometry
  DmpG4RunManager* runManager  = (DmpG4RunManager*) G4RunManager::GetRunManager();
  dmpDetector = (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());
}

void DmpSimuStkStepEventMaker::beginEvent(const G4Event* evt)
{
  //clear all ntuple data vectors here
  //set event number
  eventNumber = evt->GetEventID();

  is_pvtrack  = false;
  is_eletrack = false;
  is_postrack = false;
  is_backtrack= false;
  pvtrackID      = -1;
  eletrackID     = -1;
  postrackID     = -1;
  currentTrackID = -100;

  eDepositAcc_pvtrack = 0.;
  eDepositAcc_ele     = 0.;
  eDepositAcc_pos     = 0.;
  eDepositAcc_back    = 0.;

  dmpStkStepEvent->Reset();
}

void DmpSimuStkStepEventMaker::save()
{ 

}

void DmpSimuStkStepEventMaker::FillStep(const G4Step* aStep)
{
  //fill stepping info here
  G4bool sel = false;
  //only stepping through primary charged paticles or e+/e- paire from primary photon conversion
  if (aStep->GetTrack()->GetParentID()==0) {    
    if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.) sel = true;

    G4int trackID = aStep->GetTrack()->GetTrackID();
    if(trackID != currentTrackID) {
      pvtrackID      = trackID;
      currentTrackID = trackID;
      if(eventNumber == debugEvent || debugEvent == -1) G4cout << "   primary track ID set to " << pvtrackID <<  G4endl;
      /***
      if(sel) {
	tt_stepping_trackID    -> push_back( trackID );
	tt_stepping_trackPDG   -> push_back( aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() );
	tt_stepping_parentID   -> push_back( aStep->GetTrack()->GetParentID() );
	++tt_stepping_ntracks;
      }
      ***/
    }
    eDepositAcc_pvtrack += aStep->GetTotalEnergyDeposit(); 
    is_pvtrack  = true;
    is_eletrack = false;
    is_postrack = false;
    is_backtrack= false;
    
  }
  else if (aStep->GetPreStepPoint()->GetMomentum().z()<0) {  // new coordinate system (".. .z()>0" in the old one...)
    sel = true;
    is_pvtrack  = false;
    is_eletrack = false;
    is_postrack = false;
    is_backtrack= true;
    G4int trackID = aStep->GetTrack()->GetTrackID();
    if(trackID != currentTrackID) {
      currentTrackID = trackID;
      /***
      tt_stepping_trackID    -> push_back( trackID );
      tt_stepping_trackPDG   -> push_back( aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() );
      tt_stepping_parentID   -> push_back( aStep->GetTrack()->GetParentID() );
      ++tt_stepping_ntracks;
      ***/
    }
    eDepositAcc_back += aStep->GetTotalEnergyDeposit(); 

  }
  else if (aStep->GetTrack()->GetParentID()==pvtrackID && aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.) {
    sel = true;
    is_pvtrack  = false;
    is_backtrack= false;
    G4int trackID = aStep->GetTrack()->GetTrackID();
    if(trackID != currentTrackID) {
      currentTrackID = trackID;
      /***
      tt_stepping_trackID    -> push_back( trackID );
      tt_stepping_trackPDG   -> push_back( aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() );
      tt_stepping_parentID   -> push_back( aStep->GetTrack()->GetParentID() );
      ++tt_stepping_ntracks;
      ***/
    }
    if(aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() == 11) {
       is_eletrack = true;
       is_postrack = false;
       eDepositAcc_ele += aStep->GetTotalEnergyDeposit(); 
    }
    else if(aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() == -11) {
      is_eletrack = false;
      is_postrack = true;
      eDepositAcc_pos += aStep->GetTotalEnergyDeposit(); 
    }
 
  }
  else {
    is_pvtrack   = false;
    is_eletrack  = false;
    is_postrack  = false;
    is_backtrack = false;
  } 

  if(!is_pvtrack && !is_eletrack && !is_postrack && !is_backtrack) return;

  //return if particle goes out to World 
  if(aStep->GetTrack()->GetCurrentStepNumber() !=1 &&
     dmpDetector->isWorldVolume(aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName())) return;
     //aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "World" ) return;

  if(is_backtrack && 
     //aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "World" ) return;
     dmpDetector->isWorldVolume(aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName())) return;
  //
  if(!aStep->GetTrack()->GetNextVolume()) return; 

  G4StepPoint* point1 = aStep->GetPreStepPoint();
  G4StepPoint* point2 = aStep->GetPostStepPoint();
  if(eventNumber == debugEvent || debugEvent == -1) {
    G4cout << " new step:  current track ID= " << currentTrackID  << ", step number = " 
	   << aStep->GetTrack()->GetCurrentStepNumber() << G4endl;
    G4cout << "       prestep  at " << aStep->GetPreStepPoint()->GetPosition()  << " in volume " 
	   << aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()  << G4endl;
    G4cout << "      poststep  at " << aStep->GetPostStepPoint()->GetPosition() << " in volume " 
	     << aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() << G4endl;
    G4String thisProc  = "U Limit";
    G4String nextProc  = "U Limit";
    if(point1->GetProcessDefinedStep() !=0) thisProc  = point1->GetProcessDefinedStep()->GetProcessName();
    if(point2->GetProcessDefinedStep() !=0) nextProc  = point2->GetProcessDefinedStep()->GetProcessName();
    G4cout << "       this process: " << thisProc << "    next process: " << nextProc << G4endl;
  }
  if(sel) {
    G4ThreeVector pos1  = point1->GetPosition();
    G4ThreeVector pos2  = point2->GetPosition();
    G4TouchableHandle touch1 = point1->GetTouchableHandle();
    G4TouchableHandle touch2 = point2->GetTouchableHandle();
    G4String thisVolume  = touch1->GetVolume()->GetName();
    G4String nextVolume  = touch2->GetVolume()->GetName();

    //only keep steps outside the calorimeter
    if(!(dmpDetector->GetBgoDetectorDescription()->isVolumeInsideCalorimeter(thisVolume))){
    //if(thisVolume != "BGODetectorX" && thisVolume != "BGODetectorY" &&
    //   thisVolume != "BGOLayerX"    && thisVolume != "BGOLayerY"    && thisVolume != "Payload" ) {

      G4Track* track         = aStep->GetTrack();
      G4int stepNumber = track->GetCurrentStepNumber();
      G4bool enterVolume = (point1->GetStepStatus() == fGeomBoundary);
      G4bool leaveVolume = (point2->GetStepStatus() == fGeomBoundary);

      G4int vindex = dmpDetector->getDetectorIndex(thisVolume);
      /*
      G4int vindex = -1;
      if(dmpDetector->isWorldVolume(thisVolume)) vindex = 0;
      else if(dmpDetector->GetBgoDetectorDescription()->isVolumeBgoBar(thisVolume))         vindex = 1;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeConverter(thisVolume))      vindex = 2;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeThickConverter(thisVolume)) vindex = 3;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTile(thisVolume))  vindex = 4;
      */
      /*
      if(thisVolume == "World") vindex = 0; 
      else if(thisVolume == "BGODetectorX" || thisVolume == "BGODetectorY" )   vindex = 1; 
      else if(thisVolume == "BGOLayerX"    || thisVolume == "BGOLayerY"    )   vindex = 1; 
      else if(thisVolume == "Converter")      vindex = 2; 
      else if(thisVolume == "ThickConverter") vindex = 3; 
      else if(thisVolume == "Active Tile X" || thisVolume == "Active Tile Y")  vindex = 4; 
      else if(thisVolume == "Plane")          vindex = 5; 
      else if(thisVolume == "STKDetectorX"  || thisVolume == "STKDetectorY")   vindex  = 6; 
      else if(thisVolume == "STK")            vindex = 7; 
      else if(thisVolume == "PSD")            vindex = 8; 
      else if(thisVolume == "Payload")        vindex = 9; 
      else if(thisVolume == "PlaneThinW")     vindex = 10; 
      else if(thisVolume == "PlaneThickW")    vindex = 11;
      */


      G4int vindexN = dmpDetector->getDetectorIndex(nextVolume);
      /*
      G4int vindexN = -1;
      if(dmpDetector->isWorldVolume(nextVolume)) vindex = 0;
      else if(dmpDetector->GetBgoDetectorDescription()->isVolumeBgoBar(nextVolume))         vindex = 1;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeConverter(nextVolume))      vindex = 2;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeThickConverter(nextVolume)) vindex = 3;
      else if(dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTile(nextVolume))  vindex = 4;
      */
      /*
      if(nextVolume == "World") vindexN = 0; 
      else if(nextVolume == "BGODetectorX" || nextVolume == "BGODetectorY" )   vindexN = 1; 
      else if(nextVolume == "BGOLayerX"    || nextVolume == "BGOLayerY"    )   vindexN = 1; 
      else if(nextVolume == "Converter")      vindexN = 2; 
      else if(nextVolume == "ThickConverter") vindexN = 3; 
      else if(nextVolume == "Active Tile X" || nextVolume == "Active Tile Y")  vindexN = 4; 
      else if(nextVolume == "Plane")          vindexN = 5; 
      else if(nextVolume == "STKDetectorX"  || nextVolume == "STKDetectorY")   vindexN  = 6; 
      else if(nextVolume == "STK")            vindexN = 7; 
      else if(nextVolume == "PSD")            vindexN = 8; 
      else if(nextVolume == "Payload")        vindexN = 9; 
      else if(nextVolume == "PlaneThinW")     vindexN = 10; 
      else if(nextVolume == "PlaneThickW")    vindexN = 11;
      */

      if(eventNumber == debugEvent || debugEvent == -1) {
	//G4int thisVolumeCopy = touch1->GetCopyNumber();
	//G4int nextVolumeCopy = touch2->GetCopyNumber();
	//G4double kinEnergy     = track->GetKineticEnergy();
	//G4double globalTime    = track->GetGlobalTime();
	G4int trackID = track->GetTrackID();
     
	G4cout << "   track ID= " << trackID << "  step number= " << stepNumber 
	       << ",  step length= " << aStep->GetStepLength() << ",  track length= " << track->GetTrackLength() << G4endl;
	G4cout << ",  energy depo= " << aStep->GetTotalEnergyDeposit();
	//if(thisVolume == "Converter" || thisVolume == "ThickConverter" ) {
	if(dmpDetector->GetStkDetectorDescription()->isVolumeConverter(thisVolume)||
	   dmpDetector->GetStkDetectorDescription()->isVolumeThickConverter(thisVolume)) {

	  if(is_pvtrack) {G4cout << " accumulated edep= " << eDepositAcc_pvtrack;}
	  else if(is_eletrack) {G4cout << " accumulated edep= " << eDepositAcc_ele;}
	  else if(is_postrack) {G4cout << " accumulated edep= " << eDepositAcc_pos;}
	  else if(is_backtrack) {G4cout << " accumulated edep= " << eDepositAcc_back;}
	  if( stepNumber==1 || leaveVolume) {G4cout << " SELECTED!" <<  G4endl;}
	  else  {G4cout <<  G4endl;}
	  G4String thisProc  = "Uset Limit";
	  G4String nextProc  = "Uset Limit";
	  if(point1->GetProcessDefinedStep() !=0) thisProc  = point1->GetProcessDefinedStep()->GetProcessName();
	  if(point2->GetProcessDefinedStep() !=0) nextProc  = point2->GetProcessDefinedStep()->GetProcessName();
	  G4cout << "       this process: " << thisProc << "    next process: " << nextProc << G4endl;
	  G4cout << "       point1 momentum (MeV): " <<point1->GetMomentum() << G4endl;
	  G4cout << "       point2 momentum (MeV): " <<point2->GetMomentum() << G4endl;
	  //G4cout << "       track  momentum (MeV): " << track->GetMomentum() << "   kinetic energy (MeV): " << kinEnergy << G4endl;
	  G4cout << "       prestep  at " << pos1 << " in volume " << thisVolume  << "    enter = " << enterVolume  << G4endl;
	  G4cout << "       poststep at " << pos2 << " in volume " << nextVolume  << "    leave = " << leaveVolume  << G4endl;
	}
      }
    
      //bool volSel = (thisVolume == "Active Tile X" || thisVolume == "Active Tile Y" || thisVolume == "PSD" );
      bool volSel = (dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTile(thisVolume)|| dmpDetector->GetPsdDetectorDescription()->isVolumeInPSD(thisVolume) );
      if(is_backtrack && volSel)   {
	/***	
	if(stepNumber == 1  || nextVolume=="Payload" || (aStep->GetTotalEnergyDeposit()>0 && leaveVolume) ) {
	  if(eventNumber == debugEvent || debugEvent == -1) {
	    G4int trackID = track->GetTrackID();
	    G4cout << "   track ID= " << trackID << "  step number= " << stepNumber 
		   << ",  step length= " << aStep->GetStepLength() << ",  track length= " << track->GetTrackLength() << G4endl;
	    G4cout << ",  energy depo= " << aStep->GetTotalEnergyDeposit();
	    {G4cout << " accumulated edep= " << eDepositAcc_back;}
	    if( stepNumber==1 || leaveVolume) {G4cout << " SELECTED!" <<  G4endl;}
	    else  {G4cout <<  G4endl;}
	    G4String thisProc  = "Uset Limit";
	    G4String nextProc  = "Uset Limit";
	    if(point1->GetProcessDefinedStep() !=0) thisProc  = point1->GetProcessDefinedStep()->GetProcessName();
	    if(point2->GetProcessDefinedStep() !=0) nextProc  = point2->GetProcessDefinedStep()->GetProcessName();
	    G4cout << "       this process: " << thisProc << "    next process: " << nextProc << G4endl;
	    G4cout << "       point1 momentum (MeV): " <<point1->GetMomentum().x() << " " << point1->GetMomentum().y() << " " << point1->GetMomentum().z() << G4endl;
	    G4cout << "       point2 momentum (MeV): " <<point2->GetMomentum().x() << " " << point2->GetMomentum().y() << " " << point2->GetMomentum().z() << G4endl;
	    G4cout << "       prestep  at " << pos1 << " in volume " << thisVolume  << "    enter = " << enterVolume  << G4endl;
	    G4cout << "       poststep at " << pos2 << " in volume " << nextVolume  << "    leave = " << leaveVolume  << G4endl;
	    G4cout << "       PDG code    " <<aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() << G4endl;
	  }
	}
	
	if(stepNumber == 1) {
	  tt_step_back_trackID -> push_back(  aStep->GetTrack()->GetTrackID() );
	  tt_step_back_pdg     -> push_back(  aStep->GetTrack()->GetDynamicParticle()->GetPDGcode()  );
	  tt_step_back_px      -> push_back(  point1->GetMomentum().x()  );
	  tt_step_back_py      -> push_back(  point1->GetMomentum().y()  );
	  tt_step_back_pz      -> push_back(  point1->GetMomentum().z()  );
	  tt_step_back_ekin    -> push_back(  point1->GetKineticEnergy() );
	  tt_step_back_x       -> push_back(  point1->GetPosition().x()  );
	  tt_step_back_y       -> push_back(  point1->GetPosition().y()  );
	  tt_step_back_z       -> push_back(  point1->GetPosition().z()  );
	  tt_step_back_stepNumber    -> push_back( stepNumber-1 );
	  tt_step_back_isEntering    -> push_back( enterVolume  );
	  tt_step_back_thisVolume    -> push_back( thisVolume   );
	  tt_step_back_nextVolume    -> push_back( thisVolume   ); //on purpose
	  tt_step_back_thisIndex     -> push_back( vindex       );
	  tt_step_back_nextIndex     -> push_back( vindex       ); //on purpose
	  tt_step_back_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_back_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_back_energyDeposit -> push_back( eDepositAcc_back );	 
	  ++tt_back_nsteps;
	}
	***/
	//filling steps that leaves the volume and has deposited energy 
	if(leaveVolume) {
	  //if(aStep->GetTotalEnergyDeposit()>0 || nextVolume=="Payload") {
	  if(aStep->GetTotalEnergyDeposit()>0) {
	    DmpStkStep* backstep = new DmpStkStep();

	    backstep->step_trackID =  aStep->GetTrack()->GetTrackID();
	    backstep->step_pdg  = aStep->GetTrack()->GetDynamicParticle()->GetPDGcode();
	    backstep->step_px   = point2->GetMomentum().x();
	    backstep->step_py   = point2->GetMomentum().y();
	    backstep->step_pz   = point2->GetMomentum().z();
	    backstep->step_ekin = point2->GetKineticEnergy();
	    backstep->step_x    = point2->GetPosition().x();
	    backstep->step_y    = point2->GetPosition().y();
	    backstep->step_z    = point2->GetPosition().z();
	    backstep->step_stepNumber = stepNumber;
	    backstep->step_isEntering = enterVolume;
	    backstep->step_thisVolume = thisVolume;
	    backstep->step_nextVolume = nextVolume;
	    backstep->step_thisIndex = vindex;
	    backstep->step_nextIndex = vindexN;
	    backstep->step_stepLength  = aStep->GetStepLength();
	    backstep->step_trackLength = track->GetTrackLength();
	    backstep->step_energyDeposit = eDepositAcc_back;

	    ++dmpStkStepEvent->back_nsteps;
	    dmpStkStepEvent->back_steps.push_back(*backstep);
	  }
	}
 
      }

      if(is_pvtrack && volSel)   {
	//if(eventNumber == debugEvent || debugEvent == -1) G4cout << "pvtrack   track ID= " << currentTrackID << "  step number= " << stepNumber << G4endl;
	//filling step 0 (point 1 of step 1)
	if(stepNumber == 1) {
	  DmpStkStep* pvtrack_step = new DmpStkStep();

	  pvtrack_step->step_px   = point1->GetMomentum().x();
	  pvtrack_step->step_py   = point1->GetMomentum().y();
	  pvtrack_step->step_pz   = point1->GetMomentum().z();
	  pvtrack_step->step_ekin = point1->GetKineticEnergy();
	  pvtrack_step->step_x    = point1->GetPosition().x();
	  pvtrack_step->step_y    = point1->GetPosition().y();
	  pvtrack_step->step_z    =  point1->GetPosition().z();
	  pvtrack_step->step_stepNumber    = stepNumber-1;
	  pvtrack_step->step_isEntering    = enterVolume;
	  pvtrack_step->step_thisVolume    = thisVolume;
	  pvtrack_step->step_nextVolume    = thisVolume; //on purpose
	  pvtrack_step->step_thisIndex     = vindex;
	  pvtrack_step->step_nextIndex     = vindex; //on purpose
	  pvtrack_step->step_stepLength    = aStep->GetStepLength();
	  pvtrack_step->step_trackLength   = track->GetTrackLength();
	  pvtrack_step->step_energyDeposit = eDepositAcc_pvtrack;

	  ++dmpStkStepEvent->pvtrack_nsteps;
	  dmpStkStepEvent->pvtrack_steps.push_back(*pvtrack_step);

	}
	//filling steps that leaves the volume
	if(leaveVolume) {
	  DmpStkStep* pvtrack_step = new DmpStkStep();

	  pvtrack_step->step_px   = point2->GetMomentum().x();
	  pvtrack_step->step_py   = point2->GetMomentum().y();
	  pvtrack_step->step_pz   = point2->GetMomentum().z();
	  pvtrack_step->step_ekin = point2->GetKineticEnergy();
	  pvtrack_step->step_x    = point2->GetPosition().x();
	  pvtrack_step->step_y    = point2->GetPosition().y();
	  pvtrack_step->step_z    = point2->GetPosition().z();
	  pvtrack_step->step_stepNumber    = stepNumber;
	  pvtrack_step->step_isEntering    = enterVolume;
	  pvtrack_step->step_thisVolume    = thisVolume;
	  pvtrack_step->step_nextVolume    = nextVolume;
	  pvtrack_step->step_thisIndex     = vindex;
	  pvtrack_step->step_nextIndex     = vindexN;
	  pvtrack_step->step_stepLength    = aStep->GetStepLength();
	  pvtrack_step->step_trackLength   = track->GetTrackLength();
	  pvtrack_step->step_energyDeposit = eDepositAcc_pvtrack;

	  ++dmpStkStepEvent->pvtrack_nsteps;
	  dmpStkStepEvent->pvtrack_steps.push_back(*pvtrack_step);
	}
      }

      if(is_eletrack && volSel)  {
	//if(eventNumber == debugEvent || debugEvent == -1) G4cout << "eletrack   track ID= " << currentTrackID << "  step number= " << stepNumber << G4endl;
 	//filling step 0 (point 1 of step 1)
	if(stepNumber == 1) {
	  DmpStkStep* electron_step = new DmpStkStep();

	  electron_step->step_px   = point1->GetMomentum().x();
	  electron_step->step_py   = point1->GetMomentum().y();
	  electron_step->step_pz   = point1->GetMomentum().z();
	  electron_step->step_ekin = point1->GetKineticEnergy();
	  electron_step->step_x    = point1->GetPosition().x();
	  electron_step->step_y    = point1->GetPosition().y();
	  electron_step->step_z    = point1->GetPosition().z();
	  electron_step->step_stepNumber    = stepNumber-1;
	  electron_step->step_isEntering    = enterVolume;
	  electron_step->step_thisVolume    = thisVolume;
	  electron_step->step_nextVolume    = thisVolume; //on purpose
	  electron_step->step_thisIndex     = vindex;
	  electron_step->step_nextIndex     = vindex; //on purpose
	  electron_step->step_stepLength    = aStep->GetStepLength();
	  electron_step->step_trackLength   = track->GetTrackLength();
	  electron_step->step_energyDeposit = eDepositAcc_ele;
	  electron_step->step_pdg = 11;

	  ++dmpStkStepEvent->ele_nsteps;
	  dmpStkStepEvent->electron_steps.push_back(*electron_step);

	}
	//filling steps that leaves the volume
	if(leaveVolume) {
	  DmpStkStep* electron_step = new DmpStkStep();

	  electron_step->step_px   = point2->GetMomentum().x();
	  electron_step->step_py   = point2->GetMomentum().y();
	  electron_step->step_pz   = point2->GetMomentum().z();
	  electron_step->step_ekin = point2->GetKineticEnergy();
	  electron_step->step_x    = point2->GetPosition().x();
	  electron_step->step_y    = point2->GetPosition().y();
	  electron_step->step_z    = point2->GetPosition().z();
	  electron_step->step_stepNumber    = stepNumber;
	  electron_step->step_isEntering    = enterVolume;
	  electron_step->step_thisVolume    = thisVolume;
	  electron_step->step_nextVolume    = nextVolume;
	  electron_step->step_thisIndex     = vindex;
	  electron_step->step_nextIndex     = vindexN;
	  electron_step->step_stepLength    = aStep->GetStepLength();
	  electron_step->step_trackLength   = track->GetTrackLength();
	  electron_step->step_energyDeposit = eDepositAcc_ele;
	  electron_step->step_pdg = 11;

	  ++dmpStkStepEvent->ele_nsteps;
	  dmpStkStepEvent->electron_steps.push_back(*electron_step);
	}
      }
      if(is_postrack && volSel)  {
	//if(eventNumber == debugEvent || debugEvent == -1) G4cout << "postrack   track ID= " << currentTrackID << "  step number= " << stepNumber << G4endl;
	//filling step 0 (point 1 of step 1)
	if(stepNumber == 1) {
	  DmpStkStep* positron_step = new DmpStkStep();

	  positron_step->step_px   = point1->GetMomentum().x();
	  positron_step->step_py   = point1->GetMomentum().y();
	  positron_step->step_pz   = point1->GetMomentum().z();
	  positron_step->step_ekin = point1->GetKineticEnergy();
	  positron_step->step_x    = point1->GetPosition().x();
	  positron_step->step_y    = point1->GetPosition().y();
	  positron_step->step_z    = point1->GetPosition().z();
	  positron_step->step_stepNumber    = stepNumber-1;
	  positron_step->step_isEntering    = enterVolume;
	  positron_step->step_thisVolume    = thisVolume;
	  positron_step->step_nextVolume    = thisVolume; //on purpose
	  positron_step->step_thisIndex     = vindex;
	  positron_step->step_nextIndex     = vindex; //on purpose
	  positron_step->step_stepLength    = aStep->GetStepLength();
	  positron_step->step_trackLength   = track->GetTrackLength();
	  positron_step->step_energyDeposit = eDepositAcc_pos;
	  positron_step->step_pdg = -11;

	  ++dmpStkStepEvent->pos_nsteps;
	  dmpStkStepEvent->positron_steps.push_back(*positron_step);
	}
	//filling steps that leaves the volume
	if(leaveVolume) {
	  DmpStkStep* positron_step = new DmpStkStep();

	  positron_step->step_px   = point2->GetMomentum().x();
	  positron_step->step_py   = point2->GetMomentum().y();
	  positron_step->step_pz   = point2->GetMomentum().z();
	  positron_step->step_ekin = point2->GetKineticEnergy();
	  positron_step->step_x    = point2->GetPosition().x();
	  positron_step->step_y    = point2->GetPosition().y();
	  positron_step->step_z    = point2->GetPosition().z();
	  positron_step->step_stepNumber    = stepNumber;
	  positron_step->step_isEntering    = enterVolume;
	  positron_step->step_thisVolume    = thisVolume;
	  positron_step->step_nextVolume    = nextVolume;
	  positron_step->step_thisIndex     = vindex;
	  positron_step->step_nextIndex     = vindexN;
	  positron_step->step_stepLength    = aStep->GetStepLength();
	  positron_step->step_trackLength   = track->GetTrackLength();
	  positron_step->step_energyDeposit = eDepositAcc_pos;
	  positron_step->step_pdg = -11;

      ++dmpStkStepEvent->pos_nsteps;
      dmpStkStepEvent->positron_steps.push_back(*positron_step);

	}
      }

    }
  }

}







