// Description: manager for output data to a ROOT file
//
// Author(s):
//  - creation by Andrii Tykhonov, 27/01/2014

#include "DmpRootEventDataManager.hh"

#include "TFile.h"
#include "TTree.h"

DmpRootEventDataManager::DmpRootEventDataManager()
  :rootFileName             ("DmpSimu"),
   keepMCgeneratorDebugInfo (true     ),
   calEcut                  (-1       ),
   siDigicut                (-1       )
{
      
  // * Header
  dmpSimuRunEventHeaderMaker    = new DmpSimuRunEventHeaderMaker();

  // * Auxiliary simulation info
  dmpSimuPrimariesEventMaker    = new DmpSimuPrimariesEventMaker();
  dmpSimuTrajectoryEventMaker   = new DmpSimuTrajectoryEventMaker();

  // * BGO
  dmpSimuBgoHitEventMaker       = new DmpSimuBgoHitEventMaker();

  // * STK
  dmpSimuStkStepEventMaker      = new DmpSimuStkStepEventMaker();
  dmpSimuStkHitEventMaker       = new DmpSimuStkHitEventMaker();
  dmpSimuStkDigiEventMaker      = new DmpSimuStkDigiEventMaker();

  // * PSD
  dmpSimuPsdHitEventMaker       = new DmpSimuPsdHitEventMaker();

  // * NUD
  dmpSimuNudHitEventMaker       = new DmpSimuNudHitEventMaker();


  //create a messenger for this class
  rootMessenger = new DmpRootEventDataMessenger(this);


  //G4cout << "ROOT FILE NAME: " << rootFileName << G4endl;
  //rootMessenger = new DmpRootNtupleMessenger();

}

DmpRootEventDataManager::~DmpRootEventDataManager()
{
  //if ( rootFile ) delete rootFile;
  delete dmpSimuRunEventHeaderMaker;
  // * General
  delete dmpSimuPrimariesEventMaker;
  delete dmpSimuTrajectoryEventMaker;
  // * STK
  delete dmpSimuStkStepEventMaker;
  delete dmpSimuStkHitEventMaker;
  delete dmpSimuStkDigiEventMaker;
  // * PSD
  delete dmpSimuPsdHitEventMaker;
  // * NUD
  delete dmpSimuNudHitEventMaker;

  // * BGO
  delete dmpSimuBgoHitEventMaker;

  delete rootMessenger;
}

void DmpRootEventDataManager::book(const G4Run* aRun)
{ 
 

 /*
 treeHit     = new TTree("DmpEvtHit",   "DmpEvtHit");
 treeDigit   = new TTree("DmpEvtDigit", "DmpEvtDigit");
 treeSimul   = new TTree("DmpEvtSimul", "DmpEvtSimul");
 treeTruth   = new TTree("DmpEvtTruth", "DmpEvtTruth");
 */
 tree     = new TTree("DampeSimulation",      "DampeSimulation");
 

 if(keepMCgeneratorDebugInfo){
     dmpSimuRunEventHeaderMaker   ->book(aRun, tree);
     dmpSimuPrimariesEventMaker   ->book(aRun, tree);
 }

 dmpSimuTrajectoryEventMaker  ->book(aRun, tree);
 dmpSimuStkHitEventMaker      ->book(aRun, tree);
 dmpSimuStkDigiEventMaker     ->book(aRun, tree);
 dmpSimuStkStepEventMaker     ->book(aRun, tree);
 dmpSimuPsdHitEventMaker      ->book(aRun, tree);
 dmpSimuNudHitEventMaker      ->book(aRun, tree);
 dmpSimuBgoHitEventMaker      ->book(aRun, tree);
}

void DmpRootEventDataManager::beginEvent(const G4Event* evt)
{
  //clear all ntuple data vectors here
  if(keepMCgeneratorDebugInfo){
      dmpSimuRunEventHeaderMaker  ->beginEvent(evt);
      dmpSimuPrimariesEventMaker  ->beginEvent(evt);
  }
  dmpSimuTrajectoryEventMaker ->beginEvent(evt);
  dmpSimuStkHitEventMaker     ->beginEvent(evt);
  dmpSimuStkDigiEventMaker    ->beginEvent(evt);
  dmpSimuStkStepEventMaker    ->beginEvent(evt);
  dmpSimuPsdHitEventMaker     ->beginEvent(evt);
  dmpSimuNudHitEventMaker     ->beginEvent(evt);
  dmpSimuBgoHitEventMaker     ->beginEvent(evt);

}

void DmpRootEventDataManager::beginRun(const G4Run* aRun)
{
  // this tree should contain all the infos that are updated only once at the beginnig of te run (i.e. GPS config)
  treeRun = new TTree("DampeSimulationHeader",      "DampeSimulationHeader");
  //treeGen  = new TTree("DampeGeneratedEvents", "DampeGeneratedEvents");

  dmpSimuRunEventHeaderMaker  ->beginRun(aRun, treeRun);
}


void DmpRootEventDataManager::save()
{ 
    /*
     *  Save trees to ROOT files
     */

    TString name;
    name.Append(rootFileName);
    name.Append(".root");
    TFile* rootFile   = new TFile(name,  "RECREATE");
    if(!rootFile) {
        G4cout << "[DmpRootEventManager::book] ERROR -  problem creating the ROOT TFile: " << name <<G4endl;
        return;
    }
    /*
    treeHit->Write();
    treeDigit->Write();
    treeSimul->Write();
    treeTruth->Write();
    */
    tree->Write();
    treeRun->Write();
    //if(keepMCgeneratorDebugInfo) treeGen->Write();
    rootFile->Close();
    //G4cout << " ROOT TFile: " << name <<G4endl;

}


void DmpRootEventDataManager::FillStep(const G4Step* aStep)
{
  dmpSimuStkStepEventMaker ->FillStep(aStep);
}


void DmpRootEventDataManager::FillEvent(const G4Event* evt)
{  
  // *
  // * Fill event
  // *
  if(keepMCgeneratorDebugInfo){
    dmpSimuRunEventHeaderMaker   ->FillEvent(evt);
    dmpSimuPrimariesEventMaker   ->FillEvent(evt);
  }
  dmpSimuTrajectoryEventMaker  ->FillEvent(evt);
  dmpSimuStkHitEventMaker      ->FillEvent(evt);
  dmpSimuStkDigiEventMaker     ->FillEvent(evt);
  dmpSimuPsdHitEventMaker      ->FillEvent(evt);
  dmpSimuNudHitEventMaker      ->FillEvent(evt);
  dmpSimuBgoHitEventMaker      ->FillEvent(evt);

  // *
  // * Put event to the tree
  // *
  bool toKeep = true;
  if(!dmpSimuStkDigiEventMaker->passTotalDigiCut(siDigicut))   toKeep = false;
  // *   TODO: replace BGO ntuple thing with Event Class
  if(!dmpSimuBgoHitEventMaker ->passTotalEnergyCut(calEcut))  toKeep = false;
  if(toKeep){
      tree->Fill();
  }

  /* 
  if(keepMCgeneratorDebugInfo){
      treeGen->Fill();
  }
  */

}


void DmpRootEventDataManager::FillRun(const G4Run* aRun, DmpSimuPrimaryGeneratorAction* dmpSimuPrimaryGeneratorAction)
{
  
  dmpSimuRunEventHeaderMaker -> FillRun(aRun, dmpSimuPrimaryGeneratorAction);
  bool toKeep = true;
  if(toKeep){
    treeRun->Fill();
  }

}
