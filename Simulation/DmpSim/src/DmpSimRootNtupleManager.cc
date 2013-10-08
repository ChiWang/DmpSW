// Description: manager for output data to a ROOT ntuple
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpSimRootNtupleManager.hh"

#include "DmpSimRunEventNtupleMaker.hh"
#include "DmpSimPrimariesNtupleMaker.hh"
#include "DmpSimStepNtupleMakerStk.hh"
#include "DmpSimTrajectoryNtupleMaker.hh"
#include "DmpSimHitNtupleMakerBgo.hh"
#include "DmpSimHitNtupleMakerStk.hh"
#include "DmpSimDigiNtupleMakerStk.hh"

#include "TFile.h"
#include "TTree.h"

DmpSimRootNtupleManager::DmpSimRootNtupleManager()
:rootFile(0),tree(0)
{
      
  dmpSimRunEventNtupleMaker     = new DmpSimRunEventNtupleMaker();
  dmpSimPrimariesNtupleMaker    = new DmpSimPrimariesNtupleMaker();
  dmpSimStkStepNtupleMaker      = new DmpSimStepNtupleMakerStk();
  dmpSimTrajectoryNtupleMaker   = new DmpSimTrajectoryNtupleMaker();
  dmpSimBgoHitNtupleMaker       = new DmpSimHitNtupleMakerBgo();
  dmpSimStkHitNtupleMaker       = new DmpSimHitNtupleMakerStk();
  dmpSimStkDigiNtupleMaker      = new DmpSimDigiNtupleMakerStk();

}

DmpSimRootNtupleManager::~DmpSimRootNtupleManager()
{
  if ( rootFile ) delete rootFile;
  delete dmpSimRunEventNtupleMaker;
  delete dmpSimPrimariesNtupleMaker;
  delete dmpSimStkStepNtupleMaker;
  delete dmpSimTrajectoryNtupleMaker;
  delete dmpSimBgoHitNtupleMaker;
  delete dmpSimStkHitNtupleMaker;
  delete dmpSimStkDigiNtupleMaker;

}

void DmpSimRootNtupleManager::book(const G4Run* aRun)
{ 
 
 // Creating a tree container to handle histograms and ntuples.
 // This tree is associated to an output file.
 //
 G4String fileName = "DmpSim.root";
 rootFile = new TFile(fileName,"RECREATE");
 if(!rootFile) {
   G4cout << " DmpSimRootNtupleManager::book : problem creating the ROOT TFile " << G4endl;
   return;
 }
 G4cout << "\n----> Output ntuple file is opened in " << fileName << G4endl;


 // create 1 ntuple in subdirectory "tuples"
 tree = new TTree("dampe", "dampe tracker");

 //book ntuple branches and define ntuple data vectors here 
 dmpSimRunEventNtupleMaker    ->book(aRun, tree);
 dmpSimPrimariesNtupleMaker   ->book(aRun, tree);
 dmpSimStkStepNtupleMaker     ->book(aRun, tree);
 dmpSimTrajectoryNtupleMaker  ->book(aRun, tree);
 dmpSimBgoHitNtupleMaker      ->book(aRun, tree);
 dmpSimStkHitNtupleMaker      ->book(aRun, tree);
 dmpSimStkDigiNtupleMaker     ->book(aRun, tree);

}

void DmpSimRootNtupleManager::beginEvent(const G4Event* evt)
{
  //clear all ntuple data vectors here
  dmpSimRunEventNtupleMaker    ->beginEvent(evt);
  dmpSimPrimariesNtupleMaker   ->beginEvent(evt);
  dmpSimStkStepNtupleMaker     ->beginEvent(evt);
  dmpSimTrajectoryNtupleMaker  ->beginEvent(evt);
  dmpSimBgoHitNtupleMaker      ->beginEvent(evt);
  dmpSimStkHitNtupleMaker      ->beginEvent(evt);
  dmpSimStkDigiNtupleMaker     ->beginEvent(evt);

}

void DmpSimRootNtupleManager::save()
{ 
  if (rootFile) {
    rootFile->Write();        // Writing the histograms to the file
    rootFile->Close();        // and closing the tree (and the file)
    G4cout << "\n----> ntuple Tree is saved \n" << G4endl;
  }
}

void DmpSimRootNtupleManager::FillStep(const G4Step* aStep)
{
  dmpSimStkStepNtupleMaker ->FillStep(aStep);
}

void DmpSimRootNtupleManager::FillEvent(const G4Event* evt)
{  
  //fill even info here, also filter and save ntuple
  bool toKeep = true;

  dmpSimRunEventNtupleMaker    ->FillEvent(evt);
  dmpSimPrimariesNtupleMaker   ->FillEvent(evt);
  dmpSimTrajectoryNtupleMaker  ->FillEvent(evt);
  dmpSimBgoHitNtupleMaker      ->FillEvent(evt);
  dmpSimStkHitNtupleMaker      ->FillEvent(evt);
  dmpSimStkDigiNtupleMaker     ->FillEvent(evt);

  //if(!dmpSimBgoHitNtupleMaker->passTotalEnergyCut(4500.)) toKeep = false;
  if(!dmpSimBgoHitNtupleMaker->passTotalEnergyCut(900.)) toKeep = false;
  if (tree && toKeep) tree->Fill();

}






