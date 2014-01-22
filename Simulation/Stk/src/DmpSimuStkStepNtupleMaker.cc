// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimuStkStepNtupleMaker.hh"
#include "G4UnitsTable.hh"

#include "G4TrajectoryContainer.hh"
#include "G4VTrajectoryPoint.hh"
#include "G4VTrajectory.hh"
#include "G4Trajectory.hh"
#include "G4VProcess.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"

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

DmpSimuStkStepNtupleMaker::DmpSimuStkStepNtupleMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event

}

DmpSimuStkStepNtupleMaker::~DmpSimuStkStepNtupleMaker()
{
}

void DmpSimuStkStepNtupleMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree = aTree;

 //book ntuple branches and define ntuple data vectors here 

 tt_stepping_ntracks = 0;
 tt_stepping_trackID        = new std::vector<int>();
 tt_stepping_trackPDG       = new std::vector<int>();
 tt_stepping_parentID       = new std::vector<int>();
 /***
 tree->Branch("tt_stepping_ntracks",  &tt_stepping_ntracks, "tt_stepping_ntracks/i");
 tree->Branch("tt_stepping_trackID",  &tt_stepping_trackID);
 tree->Branch("tt_stepping_trackPDG", &tt_stepping_trackPDG);
 tree->Branch("tt_stepping_parentID", &tt_stepping_parentID);
 ***/

 tt_pvtrack_nsteps = 0;    
 tt_step_pvtrack_px       = new std::vector<double>();
 tt_step_pvtrack_py       = new std::vector<double>();
 tt_step_pvtrack_pz       = new std::vector<double>();
 tt_step_pvtrack_ekin     = new std::vector<double>();
 tt_step_pvtrack_x        = new std::vector<double>();
 tt_step_pvtrack_y        = new std::vector<double>();
 tt_step_pvtrack_z        = new std::vector<double>();
 tt_step_pvtrack_stepLength       = new std::vector<double>();
 tt_step_pvtrack_trackLength      = new std::vector<double>();
 tt_step_pvtrack_energyDeposit    = new std::vector<double>();
 tt_step_pvtrack_stepNumber       = new std::vector<int>();
 tt_step_pvtrack_isEntering       = new std::vector<G4bool>();
 tt_step_pvtrack_thisVolume       = new std::vector<std::string>();
 tt_step_pvtrack_nextVolume       = new std::vector<std::string>();
 tt_step_pvtrack_thisIndex        = new std::vector<int>();
 tt_step_pvtrack_nextIndex        = new std::vector<int>();

 tree->Branch("tt_pvtrack_nsteps",         &tt_pvtrack_nsteps, "tt_pvtrack_nsteps/i"  );
 tree->Branch("tt_step_pvtrack_px",        &tt_step_pvtrack_px);
 tree->Branch("tt_step_pvtrack_py",        &tt_step_pvtrack_py);
 tree->Branch("tt_step_pvtrack_pz",        &tt_step_pvtrack_pz);
 tree->Branch("tt_step_pvtrack_ekin",      &tt_step_pvtrack_ekin);
 tree->Branch("tt_step_pvtrack_x",         &tt_step_pvtrack_x);
 tree->Branch("tt_step_pvtrack_y",         &tt_step_pvtrack_y);
 tree->Branch("tt_step_pvtrack_z",         &tt_step_pvtrack_z);
 tree->Branch("tt_step_pvtrack_stepLength",    &tt_step_pvtrack_stepLength);
 tree->Branch("tt_step_pvtrack_trackLength",   &tt_step_pvtrack_trackLength);
 tree->Branch("tt_step_pvtrack_energyDeposit", &tt_step_pvtrack_energyDeposit);
 tree->Branch("tt_step_pvtrack_stepNumber",    &tt_step_pvtrack_stepNumber);
 tree->Branch("tt_step_pvtrack_isEntering",    &tt_step_pvtrack_isEntering);
 tree->Branch("tt_step_pvtrack_thisVolume",    &tt_step_pvtrack_thisVolume);
 tree->Branch("tt_step_pvtrack_nextVolume",    &tt_step_pvtrack_nextVolume);
 tree->Branch("tt_step_pvtrack_thisIndex",     &tt_step_pvtrack_thisIndex);
 tree->Branch("tt_step_pvtrack_nextIndex",     &tt_step_pvtrack_nextIndex);

 tt_back_nsteps = 0;    
 tt_step_back_trackID  = new std::vector<int>();
 tt_step_back_pdg      = new std::vector<int>();
 tt_step_back_px       = new std::vector<double>();
 tt_step_back_py       = new std::vector<double>();
 tt_step_back_pz       = new std::vector<double>();
 tt_step_back_ekin     = new std::vector<double>();
 tt_step_back_x        = new std::vector<double>();
 tt_step_back_y        = new std::vector<double>();
 tt_step_back_z        = new std::vector<double>();
 tt_step_back_stepLength       = new std::vector<double>();
 tt_step_back_trackLength      = new std::vector<double>();
 tt_step_back_energyDeposit    = new std::vector<double>();
 tt_step_back_stepNumber       = new std::vector<int>();
 tt_step_back_isEntering       = new std::vector<G4bool>();
 tt_step_back_thisVolume       = new std::vector<std::string>();
 tt_step_back_nextVolume       = new std::vector<std::string>();
 tt_step_back_thisIndex        = new std::vector<int>();
 tt_step_back_nextIndex        = new std::vector<int>();

 tree->Branch("tt_back_nsteps",    &tt_back_nsteps,   "tt_back_nsteps/i"  );
 tree->Branch("tt_step_back_trackID",   &tt_step_back_trackID);
 tree->Branch("tt_step_back_pdg",       &tt_step_back_pdg);
 tree->Branch("tt_step_back_px",        &tt_step_back_px);
 tree->Branch("tt_step_back_py",        &tt_step_back_py);
 tree->Branch("tt_step_back_pz",        &tt_step_back_pz);
 tree->Branch("tt_step_back_ekin",      &tt_step_back_ekin);
 tree->Branch("tt_step_back_x",         &tt_step_back_x);
 tree->Branch("tt_step_back_y",         &tt_step_back_y);
 tree->Branch("tt_step_back_z",         &tt_step_back_z);
 tree->Branch("tt_step_back_stepLength",    &tt_step_back_stepLength);
 tree->Branch("tt_step_back_trackLength",   &tt_step_back_trackLength);
 tree->Branch("tt_step_back_energyDeposit", &tt_step_back_energyDeposit);
 tree->Branch("tt_step_back_stepNumber",    &tt_step_back_stepNumber);
 tree->Branch("tt_step_back_isEntering",    &tt_step_back_isEntering);
 tree->Branch("tt_step_back_thisVolume",    &tt_step_back_thisVolume);
 tree->Branch("tt_step_back_nextVolume",    &tt_step_back_nextVolume);
 tree->Branch("tt_step_back_thisIndex",     &tt_step_back_thisIndex);
 tree->Branch("tt_step_back_nextIndex",     &tt_step_back_nextIndex);

 tt_ele_nsteps = 0;    
 tt_step_ele_px       = new std::vector<double>();
 tt_step_ele_py       = new std::vector<double>();
 tt_step_ele_pz       = new std::vector<double>();
 tt_step_ele_ekin     = new std::vector<double>();
 tt_step_ele_x        = new std::vector<double>();
 tt_step_ele_y        = new std::vector<double>();
 tt_step_ele_z        = new std::vector<double>();
 tt_step_ele_stepLength       = new std::vector<double>();
 tt_step_ele_trackLength      = new std::vector<double>();
 tt_step_ele_energyDeposit    = new std::vector<double>();
 tt_step_ele_stepNumber       = new std::vector<int>();
 tt_step_ele_isEntering       = new std::vector<G4bool>();
 tt_step_ele_thisVolume       = new std::vector<std::string>();
 tt_step_ele_nextVolume       = new std::vector<std::string>();
 tt_step_ele_thisIndex        = new std::vector<int>();
 tt_step_ele_nextIndex        = new std::vector<int>();

 tree->Branch("tt_ele_nsteps",    &tt_ele_nsteps,   "tt_ele_nsteps/i"  );
 tree->Branch("tt_step_ele_px",        &tt_step_ele_px);
 tree->Branch("tt_step_ele_py",        &tt_step_ele_py);
 tree->Branch("tt_step_ele_pz",        &tt_step_ele_pz);
 tree->Branch("tt_step_ele_ekin",      &tt_step_ele_ekin);
 tree->Branch("tt_step_ele_x",         &tt_step_ele_x);
 tree->Branch("tt_step_ele_y",         &tt_step_ele_y);
 tree->Branch("tt_step_ele_z",         &tt_step_ele_z);
 //tree->Branch("tt_step_ele_stepLength",    &tt_step_ele_stepLength);
 //tree->Branch("tt_step_ele_trackLength",   &tt_step_ele_trackLength);
 tree->Branch("tt_step_ele_energyDeposit", &tt_step_ele_energyDeposit);
 tree->Branch("tt_step_ele_stepNumber",    &tt_step_ele_stepNumber);
 tree->Branch("tt_step_ele_isEntering",    &tt_step_ele_isEntering);
 tree->Branch("tt_step_ele_thisVolume",    &tt_step_ele_thisVolume);
 tree->Branch("tt_step_ele_nextVolume",    &tt_step_ele_nextVolume);
 tree->Branch("tt_step_ele_thisIndex",     &tt_step_ele_thisIndex);
 tree->Branch("tt_step_ele_nextIndex",     &tt_step_ele_nextIndex);

 tt_pos_nsteps = 0;    
 tt_step_pos_px       = new std::vector<double>();
 tt_step_pos_py       = new std::vector<double>();
 tt_step_pos_pz       = new std::vector<double>();
 tt_step_pos_ekin     = new std::vector<double>();
 tt_step_pos_x        = new std::vector<double>();
 tt_step_pos_y        = new std::vector<double>();
 tt_step_pos_z        = new std::vector<double>();
 tt_step_pos_stepLength       = new std::vector<double>();
 tt_step_pos_trackLength      = new std::vector<double>();
 tt_step_pos_energyDeposit    = new std::vector<double>();
 tt_step_pos_stepNumber       = new std::vector<int>();
 tt_step_pos_isEntering       = new std::vector<G4bool>();
 tt_step_pos_thisVolume       = new std::vector<std::string>();
 tt_step_pos_nextVolume       = new std::vector<std::string>();
 tt_step_pos_thisIndex        = new std::vector<int>();
 tt_step_pos_nextIndex        = new std::vector<int>();

 tree->Branch("tt_pos_nsteps",    &tt_pos_nsteps,   "tt_pos_nsteps/i"  );
 tree->Branch("tt_step_pos_px",        &tt_step_pos_px);
 tree->Branch("tt_step_pos_py",        &tt_step_pos_py);
 tree->Branch("tt_step_pos_pz",        &tt_step_pos_pz);
 tree->Branch("tt_step_pos_ekin",      &tt_step_pos_ekin);
 tree->Branch("tt_step_pos_x",         &tt_step_pos_x);
 tree->Branch("tt_step_pos_y",         &tt_step_pos_y);
 tree->Branch("tt_step_pos_z",         &tt_step_pos_z);
 tree->Branch("tt_step_pos_stepLength",    &tt_step_pos_stepLength);
 tree->Branch("tt_step_pos_trackLength",   &tt_step_pos_trackLength);
 tree->Branch("tt_step_pos_energyDeposit", &tt_step_pos_energyDeposit);
 tree->Branch("tt_step_pos_stepNumber",    &tt_step_pos_stepNumber);
 tree->Branch("tt_step_pos_isEntering",    &tt_step_pos_isEntering);
 tree->Branch("tt_step_pos_thisVolume",    &tt_step_pos_thisVolume);
 tree->Branch("tt_step_pos_nextVolume",    &tt_step_pos_nextVolume);
 tree->Branch("tt_step_pos_thisIndex",     &tt_step_pos_thisIndex);
 tree->Branch("tt_step_pos_nextIndex",     &tt_step_pos_nextIndex);

}

void DmpSimuStkStepNtupleMaker::beginEvent(const G4Event* evt)
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

  tt_stepping_ntracks = 0;
  tt_stepping_trackID  -> clear();
  tt_stepping_trackPDG -> clear();
  tt_stepping_parentID -> clear();

  tt_pvtrack_nsteps   = 0;
  tt_step_pvtrack_px            -> clear();
  tt_step_pvtrack_py            -> clear();
  tt_step_pvtrack_pz            -> clear();
  tt_step_pvtrack_ekin          -> clear();
  tt_step_pvtrack_x             -> clear();
  tt_step_pvtrack_y             -> clear();
  tt_step_pvtrack_z             -> clear();
  tt_step_pvtrack_stepNumber    -> clear();
  tt_step_pvtrack_isEntering    -> clear();
  tt_step_pvtrack_thisVolume    -> clear();
  tt_step_pvtrack_nextVolume    -> clear();
  tt_step_pvtrack_thisIndex     -> clear();
  tt_step_pvtrack_nextIndex     -> clear();
  tt_step_pvtrack_stepLength    -> clear();
  tt_step_pvtrack_trackLength   -> clear();
  tt_step_pvtrack_energyDeposit -> clear();

  tt_back_nsteps       = 0;
  tt_step_back_trackID       -> clear();
  tt_step_back_pdg           -> clear();
  tt_step_back_px            -> clear();
  tt_step_back_py            -> clear();
  tt_step_back_pz            -> clear();
  tt_step_back_ekin          -> clear();
  tt_step_back_x             -> clear();
  tt_step_back_y             -> clear();
  tt_step_back_z             -> clear();
  tt_step_back_stepNumber    -> clear();
  tt_step_back_isEntering    -> clear();
  tt_step_back_thisVolume    -> clear();
  tt_step_back_nextVolume    -> clear();
  tt_step_back_thisIndex     -> clear();
  tt_step_back_nextIndex     -> clear();
  tt_step_back_stepLength    -> clear();
  tt_step_back_trackLength   -> clear();
  tt_step_back_energyDeposit -> clear();

  tt_ele_nsteps       = 0;
  tt_step_ele_px            -> clear();
  tt_step_ele_py            -> clear();
  tt_step_ele_pz            -> clear();
  tt_step_ele_ekin          -> clear();
  tt_step_ele_x             -> clear();
  tt_step_ele_y             -> clear();
  tt_step_ele_z             -> clear();
  tt_step_ele_stepNumber    -> clear();
  tt_step_ele_isEntering    -> clear();
  tt_step_ele_thisVolume    -> clear();
  tt_step_ele_nextVolume    -> clear();
  tt_step_ele_thisIndex     -> clear();
  tt_step_ele_nextIndex     -> clear();
  tt_step_ele_stepLength    -> clear();
  tt_step_ele_trackLength   -> clear();
  tt_step_ele_energyDeposit -> clear();

  tt_pos_nsteps       = 0;
  tt_step_pos_px            -> clear();
  tt_step_pos_py            -> clear();
  tt_step_pos_pz            -> clear();
  tt_step_pos_ekin          -> clear();
  tt_step_pos_x             -> clear();
  tt_step_pos_y             -> clear();
  tt_step_pos_z             -> clear();
  tt_step_pos_stepNumber    -> clear();
  tt_step_pos_isEntering    -> clear();
  tt_step_pos_thisVolume    -> clear();
  tt_step_pos_nextVolume    -> clear();
  tt_step_pos_thisIndex     -> clear();
  tt_step_pos_nextIndex     -> clear();
  tt_step_pos_stepLength    -> clear();
  tt_step_pos_trackLength   -> clear();
  tt_step_pos_energyDeposit -> clear();


}

void DmpSimuStkStepNtupleMaker::save()
{ 

}

void DmpSimuStkStepNtupleMaker::FillStep(const G4Step* aStep)
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
  else if (aStep->GetPreStepPoint()->GetMomentum().z()>0) {
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
     aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "World" ) return;
  if(is_backtrack && 
     aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "World" ) return;
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
    if(thisVolume != "BGODetectorX" && thisVolume != "BGODetectorY" && 
       thisVolume != "BGOLayerX"    && thisVolume != "BGOLayerY"    && thisVolume != "Payload" ) {
      G4Track* track         = aStep->GetTrack();
      G4int stepNumber = track->GetCurrentStepNumber();
      G4bool enterVolume = (point1->GetStepStatus() == fGeomBoundary);
      G4bool leaveVolume = (point2->GetStepStatus() == fGeomBoundary);

      G4int vindex = -1;
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

      G4int vindexN = -1;
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

      if(eventNumber == debugEvent || debugEvent == -1) {
	//G4int thisVolumeCopy = touch1->GetCopyNumber();
	//G4int nextVolumeCopy = touch2->GetCopyNumber();
	//G4double kinEnergy     = track->GetKineticEnergy();
	//G4double globalTime    = track->GetGlobalTime();
	G4int trackID = track->GetTrackID();
     
	G4cout << "   track ID= " << trackID << "  step number= " << stepNumber 
	       << ",  step length= " << aStep->GetStepLength() << ",  track length= " << track->GetTrackLength() << G4endl;
	G4cout << ",  energy depo= " << aStep->GetTotalEnergyDeposit();
	if(thisVolume == "Converter" || thisVolume == "ThickConverter" ) {
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
    
      bool volSel = (thisVolume == "Active Tile X" || thisVolume == "Active Tile Y" || thisVolume == "PSD" ); 
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
	    tt_step_back_trackID -> push_back(  aStep->GetTrack()->GetTrackID() );
	    tt_step_back_pdg     -> push_back(  aStep->GetTrack()->GetDynamicParticle()->GetPDGcode()  );
	    tt_step_back_px      -> push_back(  point2->GetMomentum().x()  );
	    tt_step_back_py      -> push_back(  point2->GetMomentum().y()  );
	    tt_step_back_pz      -> push_back(  point2->GetMomentum().z()  );
	    tt_step_back_ekin    -> push_back(  point2->GetKineticEnergy() );
	    tt_step_back_x       -> push_back(  point2->GetPosition().x()  );
	    tt_step_back_y       -> push_back(  point2->GetPosition().y()  );
	    tt_step_back_z       -> push_back(  point2->GetPosition().z()  );
	    tt_step_back_stepNumber    -> push_back( stepNumber  );
	    tt_step_back_isEntering    -> push_back( enterVolume );
	    tt_step_back_thisVolume    -> push_back( thisVolume  );
	    tt_step_back_nextVolume    -> push_back( nextVolume  );	  
	    tt_step_back_thisIndex     -> push_back( vindex       );
	    tt_step_back_nextIndex     -> push_back( vindexN       );
	    tt_step_back_stepLength    -> push_back( aStep->GetStepLength()  );
	    tt_step_back_trackLength   -> push_back( track->GetTrackLength() );
	    tt_step_back_energyDeposit -> push_back( eDepositAcc_back );	 
	    ++tt_back_nsteps;
	  }
	}
 
      }

      if(is_pvtrack && volSel)   {
	//if(eventNumber == debugEvent || debugEvent == -1) G4cout << "pvtrack   track ID= " << currentTrackID << "  step number= " << stepNumber << G4endl;
	//filling step 0 (point 1 of step 1)
	if(stepNumber == 1) {
	  tt_step_pvtrack_px   -> push_back(  point1->GetMomentum().x()  );
	  tt_step_pvtrack_py   -> push_back(  point1->GetMomentum().y()  );
	  tt_step_pvtrack_pz   -> push_back(  point1->GetMomentum().z()  );
	  tt_step_pvtrack_ekin -> push_back(  point1->GetKineticEnergy() );
	  tt_step_pvtrack_x    -> push_back(  point1->GetPosition().x()  );
	  tt_step_pvtrack_y    -> push_back(  point1->GetPosition().y()  );
	  tt_step_pvtrack_z    -> push_back(  point1->GetPosition().z()  );
	  tt_step_pvtrack_stepNumber    -> push_back( stepNumber-1 );
	  tt_step_pvtrack_isEntering    -> push_back( enterVolume  );
	  tt_step_pvtrack_thisVolume    -> push_back( thisVolume   );
	  tt_step_pvtrack_nextVolume    -> push_back( thisVolume   ); //on purpose
	  tt_step_pvtrack_thisIndex     -> push_back( vindex       );
	  tt_step_pvtrack_nextIndex     -> push_back( vindex       ); //on purpose
	  tt_step_pvtrack_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_pvtrack_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_pvtrack_energyDeposit -> push_back( eDepositAcc_pvtrack );	 
	  ++tt_pvtrack_nsteps;
	}
	//filling steps that leaves the volume
	if(leaveVolume) {
	  tt_step_pvtrack_px   -> push_back(  point2->GetMomentum().x()  );
	  tt_step_pvtrack_py   -> push_back(  point2->GetMomentum().y()  );
	  tt_step_pvtrack_pz   -> push_back(  point2->GetMomentum().z()  );
	  tt_step_pvtrack_ekin -> push_back(  point2->GetKineticEnergy() );
	  tt_step_pvtrack_x    -> push_back(  point2->GetPosition().x()  );
	  tt_step_pvtrack_y    -> push_back(  point2->GetPosition().y()  );
	  tt_step_pvtrack_z    -> push_back(  point2->GetPosition().z()  );
	  tt_step_pvtrack_stepNumber    -> push_back( stepNumber  );
	  tt_step_pvtrack_isEntering    -> push_back( enterVolume );
	  tt_step_pvtrack_thisVolume    -> push_back( thisVolume  );
	  tt_step_pvtrack_nextVolume    -> push_back( nextVolume  );
	  tt_step_pvtrack_thisIndex     -> push_back( vindex       );
	  tt_step_pvtrack_nextIndex     -> push_back( vindexN       );
	  tt_step_pvtrack_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_pvtrack_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_pvtrack_energyDeposit -> push_back( eDepositAcc_pvtrack );	 
	  ++tt_pvtrack_nsteps;
	}
      }

      if(is_eletrack && volSel)  {
	//if(eventNumber == debugEvent || debugEvent == -1) G4cout << "eletrack   track ID= " << currentTrackID << "  step number= " << stepNumber << G4endl;
 	//filling step 0 (point 1 of step 1)
	if(stepNumber == 1) {
	  tt_step_ele_px   -> push_back(  point1->GetMomentum().x()  );
	  tt_step_ele_py   -> push_back(  point1->GetMomentum().y()  );
	  tt_step_ele_pz   -> push_back(  point1->GetMomentum().z()  );
	  tt_step_ele_ekin -> push_back(  point1->GetKineticEnergy() );
	  tt_step_ele_x    -> push_back(  point1->GetPosition().x()  );
	  tt_step_ele_y    -> push_back(  point1->GetPosition().y()  );
	  tt_step_ele_z    -> push_back(  point1->GetPosition().z()  );
	  tt_step_ele_stepNumber    -> push_back( stepNumber-1 );
	  tt_step_ele_isEntering    -> push_back( enterVolume  );
	  tt_step_ele_thisVolume    -> push_back( thisVolume   );
	  tt_step_ele_nextVolume    -> push_back( thisVolume   ); //on purpose
	  tt_step_ele_thisIndex     -> push_back( vindex       );
	  tt_step_ele_nextIndex     -> push_back( vindex       ); //on purpose
	  tt_step_ele_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_ele_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_ele_energyDeposit -> push_back( eDepositAcc_ele );	 
	  ++tt_ele_nsteps;
	}
	//filling steps that leaves the volume
	if(leaveVolume) {
	  tt_step_ele_px   -> push_back(  point2->GetMomentum().x()  );
	  tt_step_ele_py   -> push_back(  point2->GetMomentum().y()  );
	  tt_step_ele_pz   -> push_back(  point2->GetMomentum().z()  );
	  tt_step_ele_ekin -> push_back(  point2->GetKineticEnergy() );
	  tt_step_ele_x    -> push_back(  point2->GetPosition().x()  );
	  tt_step_ele_y    -> push_back(  point2->GetPosition().y()  );
	  tt_step_ele_z    -> push_back(  point2->GetPosition().z()  );
	  tt_step_ele_stepNumber    -> push_back( stepNumber  );
	  tt_step_ele_isEntering    -> push_back( enterVolume );
	  tt_step_ele_thisVolume    -> push_back( thisVolume  );
	  tt_step_ele_nextVolume    -> push_back( nextVolume  );	  
	  tt_step_ele_thisIndex     -> push_back( vindex       );
	  tt_step_ele_nextIndex     -> push_back( vindexN       );
	  tt_step_ele_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_ele_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_ele_energyDeposit -> push_back( eDepositAcc_ele );	 
	  ++tt_ele_nsteps;
	}
      }
      if(is_postrack && volSel)  {
	//if(eventNumber == debugEvent || debugEvent == -1) G4cout << "postrack   track ID= " << currentTrackID << "  step number= " << stepNumber << G4endl;
	//filling step 0 (point 1 of step 1)
	if(stepNumber == 1) {
	  tt_step_pos_px   -> push_back(  point1->GetMomentum().x()  );
	  tt_step_pos_py   -> push_back(  point1->GetMomentum().y()  );
	  tt_step_pos_pz   -> push_back(  point1->GetMomentum().z()  );
	  tt_step_pos_ekin -> push_back(  point1->GetKineticEnergy() );
	  tt_step_pos_x    -> push_back(  point1->GetPosition().x()  );
	  tt_step_pos_y    -> push_back(  point1->GetPosition().y()  );
	  tt_step_pos_z    -> push_back(  point1->GetPosition().z()  );
	  tt_step_pos_stepNumber    -> push_back( stepNumber-1 );
	  tt_step_pos_isEntering    -> push_back( enterVolume  );
	  tt_step_pos_thisVolume    -> push_back( thisVolume   );
	  tt_step_pos_nextVolume    -> push_back( thisVolume   ); //on purpose
	  tt_step_pos_thisIndex     -> push_back( vindex       );
	  tt_step_pos_nextIndex     -> push_back( vindex       ); //on purpose
	  tt_step_pos_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_pos_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_pos_energyDeposit -> push_back( eDepositAcc_pos );	 
	  ++tt_pos_nsteps;
	}
	//filling steps that leaves the volume
	if(leaveVolume) {
	  tt_step_pos_px   -> push_back(  point2->GetMomentum().x()  );
	  tt_step_pos_py   -> push_back(  point2->GetMomentum().y()  );
	  tt_step_pos_pz   -> push_back(  point2->GetMomentum().z()  );
	  tt_step_pos_ekin -> push_back(  point2->GetKineticEnergy() );
	  tt_step_pos_x    -> push_back(  point2->GetPosition().x()  );
	  tt_step_pos_y    -> push_back(  point2->GetPosition().y()  );
	  tt_step_pos_z    -> push_back(  point2->GetPosition().z()  );
	  tt_step_pos_stepNumber    -> push_back( stepNumber  );
	  tt_step_pos_isEntering    -> push_back( enterVolume );
	  tt_step_pos_thisVolume    -> push_back( thisVolume  );
	  tt_step_pos_nextVolume    -> push_back( nextVolume  );
	  tt_step_pos_thisIndex     -> push_back( vindex       );
	  tt_step_pos_nextIndex     -> push_back( vindexN       );
	  tt_step_pos_stepLength    -> push_back( aStep->GetStepLength()  );
	  tt_step_pos_trackLength   -> push_back( track->GetTrackLength() );
	  tt_step_pos_energyDeposit -> push_back( eDepositAcc_pos );	 
	  ++tt_pos_nsteps;
	}
      }

    }
  }

}

void DmpSimuStkStepNtupleMaker::FillEvent(const G4Event* evt)
{  


}






