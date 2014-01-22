// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimuRunEventNtupleMaker.hh"

#include "TTree.h"

DmpSimuRunEventNtupleMaker::DmpSimuRunEventNtupleMaker()
  :tree(0), m_runNumber(-1)
{
}

DmpSimuRunEventNtupleMaker::~DmpSimuRunEventNtupleMaker()
{
}

void DmpSimuRunEventNtupleMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree = aTree;

 //book ntuple branches and define ntuple data vectors here 
  tree->Branch("tt_run",       &tt_run,     "tt_run/i"  );
  tree->Branch("tt_event",     &tt_event,   "tt_event/i");

 m_runNumber = aRun->GetRunID();
}

void DmpSimuRunEventNtupleMaker::beginEvent(const G4Event* evt)
{
  //clear all ntuple data vectors here
  //set event number
}

void DmpSimuRunEventNtupleMaker::FillStep(const G4Step* aStep)
{
}

void DmpSimuRunEventNtupleMaker::FillEvent(const G4Event* evt)
{  
  //fill even info here, also filter and save ntuple
  //bool toKeep = true;

  tt_run   = m_runNumber;
  tt_event = evt->GetEventID();

  //  if (tree && toKeep) tree->Fill();

}






