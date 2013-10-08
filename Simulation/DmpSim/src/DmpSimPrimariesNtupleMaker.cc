// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimPrimariesNtupleMaker.hh"

#include "TTree.h"

DmpSimPrimariesNtupleMaker::DmpSimPrimariesNtupleMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimPrimariesNtupleMaker::~DmpSimPrimariesNtupleMaker()
{
}

void DmpSimPrimariesNtupleMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree = aTree;

 //book ntuple branches and define ntuple data vectors here 
 tree->Branch("tt_npv",       &tt_npv,     "tt_npv/i"  );
 //tree->Branch("tt_npvpart",   &tt_npv,     "tt_npvpart/i");

 tree->Branch("tt_pv_x",      &tt_pv_x);
 tree->Branch("tt_pv_y",      &tt_pv_y);
 tree->Branch("tt_pv_z",      &tt_pv_z);
 tree->Branch("tt_pvpart_px", &tt_pvpart_px  );
 tree->Branch("tt_pvpart_py", &tt_pvpart_py  );
 tree->Branch("tt_pvpart_pz", &tt_pvpart_pz  );
 tree->Branch("tt_pvpart_ekin",&tt_pvpart_ekin);
 tree->Branch("tt_pvpart_q",  &tt_pvpart_q   );
 tree->Branch("tt_pvpart_pdg",&tt_pvpart_pdg );

}

void DmpSimPrimariesNtupleMaker::beginEvent(const G4Event* evt)
{
  //set event number
  eventNumber = evt->GetEventID();

 //clear all ntuple data vectors here


}

void DmpSimPrimariesNtupleMaker::FillStep(const G4Step* aStep)
{
}

void DmpSimPrimariesNtupleMaker::FillEvent(const G4Event* evt)
{  
  
  if(eventNumber == debugEvent || debugEvent == -1) {
    G4int nVertex = evt->GetNumberOfPrimaryVertex();
    G4cout << " Number of PrimaryVertex: " << nVertex << G4endl;
    for ( G4int j = 0; j < nVertex; j++) { 
      evt->GetPrimaryVertex(j)->Print();
      G4cout << "   vetex " << j << " position " << evt->GetPrimaryVertex(j)->GetPosition() << G4endl;
      G4int nPart =  evt->GetPrimaryVertex(j)->GetNumberOfParticle(); 
      G4cout << "   Number of PrimaryParticles in this vertex: " << nPart << G4endl;
      for ( G4int i = 0; i < nPart; i++) {
	G4cout << "   particle " << i << " momentum " << evt->GetPrimaryVertex(j)->GetPrimary(i)->GetMomentum() << G4endl;
      }
    }
  }
  
  tt_npv   = evt->GetNumberOfPrimaryVertex();
  if(tt_npv>1) G4cout << " WARNING: Number of PrimaryVertex more than 1: " << tt_npv << G4endl;

  tt_pv_x = evt->GetPrimaryVertex(0)->GetPosition().x();
  tt_pv_y = evt->GetPrimaryVertex(0)->GetPosition().y();
  tt_pv_z = evt->GetPrimaryVertex(0)->GetPosition().z();

  tt_npvpart   =  evt->GetPrimaryVertex(0)->GetNumberOfParticle(); 
  if(tt_npvpart>1) G4cout << " WARNING: Number of PrimaryParticle more than 1: " << tt_npvpart << G4endl;

  tt_pvpart_px   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().x();
  tt_pvpart_py   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().y();
  tt_pvpart_pz   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().z();
  tt_pvpart_ekin = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetKineticEnergy();
  tt_pvpart_q    = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetCharge();
  tt_pvpart_pdg  = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetPDGcode();


}






