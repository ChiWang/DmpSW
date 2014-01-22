// Description: manager for output data to a ROOT ntuple
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpRootNtupleManager.hh"
#include "DmpRootNtupleMessenger.hh"

#include "DmpSimuRunEventNtupleMaker.hh"
#include "DmpSimuPrimariesNtupleMaker.hh"
#include "DmpSimuStkStepNtupleMaker.hh"
#include "DmpSimuTrajectoryNtupleMaker.hh"
#include "DmpSimuBgoHitNtupleMaker.hh"
#include "DmpSimuStkHitNtupleMaker.hh"
#include "DmpSimuStkDigiNtupleMaker.hh"
#include "DmpSimuPsdHitNtupleMaker.hh"

#include "TFile.h"
#include "TTree.h"

DmpRootNtupleManager::DmpRootNtupleManager()
  :rootFile(0),tree(0),treeGen(0),nRootFile("DmpSimu"), nRootGenDebug(0), 
   calEcut(-1), siDigicut(-1), keepOnlyDownward(false)
{
      
  dmpSimuRunEventNtupleMaker     = new DmpSimuRunEventNtupleMaker();
  dmpSimuPrimariesNtupleMaker    = new DmpSimuPrimariesNtupleMaker();
  dmpSimuStkStepNtupleMaker      = new DmpSimuStkStepNtupleMaker();
  dmpSimuTrajectoryNtupleMaker   = new DmpSimuTrajectoryNtupleMaker();
  dmpSimuBgoHitNtupleMaker       = new DmpSimuBgoHitNtupleMaker();
  dmpSimuStkHitNtupleMaker       = new DmpSimuStkHitNtupleMaker();
  dmpSimuStkDigiNtupleMaker      = new DmpSimuStkDigiNtupleMaker();
  dmpSimuPsdHitNtupleMaker       = new DmpSimuPsdHitNtupleMaker();

  //create a messenger for this class
   
  rootMessenger = new DmpRootNtupleMessenger(this);
  G4cout << "ROOT FILE NAME: " << nRootFile << G4endl;
  //rootMessenger = new DmpRootNtupleMessenger();

}

DmpRootNtupleManager::~DmpRootNtupleManager()
{
  if ( rootFile ) delete rootFile;
  delete dmpSimuRunEventNtupleMaker;
  delete dmpSimuPrimariesNtupleMaker;
  delete dmpSimuStkStepNtupleMaker;
  delete dmpSimuTrajectoryNtupleMaker;
  delete dmpSimuBgoHitNtupleMaker;
  delete dmpSimuStkHitNtupleMaker;
  delete dmpSimuStkDigiNtupleMaker;
  delete dmpSimuPsdHitNtupleMaker;

  delete rootMessenger;
}

void DmpRootNtupleManager::book(const G4Run* aRun)
{ 
 
 // Creating a tree container to handle histograms and ntuples.
 // This tree is associated to an output file.
 //
 //G4String fileName = "DmpSimu.root";
  G4String fileName ;
  fileName.append(nRootFile);
  fileName.append(".root");
  G4cout << "ROOT FILE NAME: " << fileName << G4endl;
 rootFile = new TFile(fileName,"RECREATE");
 if(!rootFile) {
   G4cout << " DmpRootNtupleManager::book : problem creating the ROOT TFile " << G4endl;
   return;
 }
 G4cout << "\n----> Output ntuple file is opened in " << fileName << G4endl;


 // create 1 ntuple in subdirectory "tuples"
 tree = new TTree("dampe", "dampe tracker");

 //book ntuple branches and define ntuple data vectors here 
 dmpSimuRunEventNtupleMaker    ->book(aRun, tree);
 dmpSimuPrimariesNtupleMaker   ->book(aRun, tree);
 dmpSimuStkStepNtupleMaker     ->book(aRun, tree);
 dmpSimuTrajectoryNtupleMaker  ->book(aRun, tree);
 dmpSimuBgoHitNtupleMaker      ->book(aRun, tree);
 dmpSimuStkHitNtupleMaker      ->book(aRun, tree);
 dmpSimuStkDigiNtupleMaker     ->book(aRun, tree);
 dmpSimuPsdHitNtupleMaker      ->book(aRun, tree);

 // create 1 ntuple in subdirectory "tuples" to sotre the infos of the generated events
 treeGen = new TTree("dampeGenEvt", "dampe genereted events");
 //book ntuple branches and define ntuple data vectors here 
 dmpSimuRunEventNtupleMaker    ->book(aRun, treeGen);
 dmpSimuPrimariesNtupleMaker   ->book(aRun, treeGen);

 nInput = 0;
 nSaved = 0;

}

void DmpRootNtupleManager::beginEvent(const G4Event* evt)
{
  //clear all ntuple data vectors here
  dmpSimuRunEventNtupleMaker    ->beginEvent(evt);
  dmpSimuPrimariesNtupleMaker   ->beginEvent(evt);
  dmpSimuStkStepNtupleMaker     ->beginEvent(evt);
  dmpSimuTrajectoryNtupleMaker  ->beginEvent(evt);
  dmpSimuBgoHitNtupleMaker      ->beginEvent(evt);
  dmpSimuStkHitNtupleMaker      ->beginEvent(evt);
  dmpSimuStkDigiNtupleMaker     ->beginEvent(evt);
  dmpSimuPsdHitNtupleMaker      ->beginEvent(evt);

}

void DmpRootNtupleManager::save()
{ 
  if (rootFile) {
    rootFile->Write();        // Writing the histograms to the file
    rootFile->Close();        // and closing the tree (and the file)
    G4cout << "\n----> ntuple Tree is saved \n" << G4endl;
    G4cout << "\n----> number of input event = " << nInput << " \n" << G4endl;
    G4cout << "\n----> number of saved event = " << nSaved << " \n" << G4endl;
  }
}

void DmpRootNtupleManager::FillStep(const G4Step* aStep)
{
  dmpSimuStkStepNtupleMaker ->FillStep(aStep);
}

void DmpRootNtupleManager::FillEvent(const G4Event* evt)
{  
  //fill even info here, also filter and save ntuple
  bool toKeep = true;

  dmpSimuRunEventNtupleMaker    ->FillEvent(evt);
  dmpSimuPrimariesNtupleMaker   ->FillEvent(evt);
  dmpSimuTrajectoryNtupleMaker  ->FillEvent(evt);
  dmpSimuBgoHitNtupleMaker      ->FillEvent(evt);
  dmpSimuStkHitNtupleMaker      ->FillEvent(evt);
  dmpSimuStkDigiNtupleMaker     ->FillEvent(evt);
  dmpSimuPsdHitNtupleMaker      ->FillEvent(evt);
  //if(!dmpSimuBgoHitNtupleMaker->passTotalEnergyCut(900.)) toKeep = false;
  if(!dmpSimuBgoHitNtupleMaker ->passTotalEnergyCut(calEcut))  toKeep = false;
  if(!dmpSimuStkDigiNtupleMaker->passTotalDigiCut(siDigicut)) toKeep = false;
                                                   
  double pvpart_px   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().x();
  double pvpart_py   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().y();
  double pvpart_pz   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().z();

  G4ThreeVector vecPrim = G4ThreeVector(pvpart_px,pvpart_py,pvpart_pz);
  double thetaPrim  = vecPrim.theta();
  bool isDownward = (thetaPrim>0.5*pi); //downward going particles  
  if(!isDownward && keepOnlyDownward) toKeep = false;

  ++nInput;
  if (tree && toKeep) {
    tree->Fill();
    ++nSaved;
  }
  if(nInput%1000 == 0) G4cout << "\n----> number of event generated = " << nInput << " \n" << G4endl;

  //toKeep = false;
  //if(nRootGenDebug) toKeep = true;   
  if (treeGen && nRootGenDebug) treeGen->Fill();

}






