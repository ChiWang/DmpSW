// Description: event maker for Nud
//
// Author(s):
//  - added by Tiekuang Dong 2012/12/23 (revised by A.Tykhonov)

#include "DmpSimuNudHitEventMaker.hh"
#include "DmpNudDetectorDescription.hh"
#include "DmpDetectorConstruction.hh"
#include "DmpSimuNudHit.hh"

#include "G4RunManager.hh"
#include "G4DigiManager.hh"
#include "G4SDManager.hh"

#include "TTree.h"

DmpSimuNudHitEventMaker::DmpSimuNudHitEventMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimuNudHitEventMaker::~DmpSimuNudHitEventMaker()
{
}

void DmpSimuNudHitEventMaker::book(const G4Run* aRun, TTree* aTree)
{
  tree = aTree;
  dmpEvtNudHit = new DmpEvtNudHit();
  tree->Branch("DmpEvtNudHit", "DmpEvtNudHit",  &dmpEvtNudHit);
}

void DmpSimuNudHitEventMaker::beginEvent(const G4Event* evt)
{
  eventNumber = evt->GetEventID();
  dmpEvtNudHit->Reset();
}

void DmpSimuNudHitEventMaker::FillStep(const G4Step* aStep)
{
}

void DmpSimuNudHitEventMaker::FillEvent(const G4Event* evt)
{  
  //fill even info here, also filter and save ntuple
  //bool toKeep = true;

  //NUD hits
  DmpSimuNudHitsCollection* CHC0 = 0;
  DmpSimuNudHitsCollection* CHC1 = 0;
  DmpSimuNudHitsCollection* CHC2 = 0;
  DmpSimuNudHitsCollection* CHC3 = 0;

  G4SDManager * SDman = G4SDManager::GetSDMpointer();  
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

  if (HCE) {
  
    CHC1 = (DmpSimuNudHitsCollection*) (HCE->GetHC(SDman->GetCollectionID("NUDHitCollection1")));
     
    CHC2 = (DmpSimuNudHitsCollection*) (HCE->GetHC(SDman->GetCollectionID("NUDHitCollection2")));
 
    CHC3 = (DmpSimuNudHitsCollection*) (HCE->GetHC(SDman->GetCollectionID("NUDHitCollection3")));
    
    CHC0 = (DmpSimuNudHitsCollection*) (HCE->GetHC(SDman->GetCollectionID("NUDHitCollection0")));
 
  }


  if (CHC0) {
    G4int n_hit = CHC0->entries();
    if(eventNumber == debugEvent || debugEvent == -1) {
    G4cout << "Number of NUD hits0 in this event =  " << n_hit << G4endl;  
    }   
    
    G4RunManager* runManager = G4RunManager::GetRunManager();
    DmpDetectorConstruction* dmpDetector =
      (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

    G4int NbOfNudBlocks = 4;
    
    if(NbOfNudBlocks != dmpDetector->GetNudDetectorDescription()->GetNbOfNUDStrips()) G4cout<< "WARNING NbOfNudBlocks is not "<< NbOfNudBlocks<< "!!!"<< G4endl;
    G4double Edep=0.;
    G4double time=0.; 
    G4ThreeVector pos;
  //  G4int  NudBlockNumber;
   
    for (int i=0;i<n_hit;i++) {
      Edep           = (*CHC0)[i]->GetEdep();
      pos            = (*CHC0)[i]->GetPos();
   
      time           = (*CHC0)[i]->GetTime();
      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << Edep/MeV <<  "   "  << time << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
      }

      DmpNudHit* dmpNudHit = new DmpNudHit(Edep, time);
      dmpEvtNudHit->nud_totE0 += Edep;
      dmpEvtNudHit->nudHits0.push_back(*dmpNudHit);
}
}



 if (CHC1) {
 
    G4int n_hit = CHC1->entries();
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << "Number of NUD hits1 in this event =  " << n_hit << G4endl;  
    }   
    
    G4RunManager* runManager = G4RunManager::GetRunManager();
    DmpDetectorConstruction* dmpDetector =
      (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

    G4int NbOfNudBlocks = 4;
    
    if(NbOfNudBlocks != dmpDetector->GetNudDetectorDescription()->GetNbOfNUDStrips()) G4cout<< "WARNING NbOfNudBlocks is not "<< NbOfNudBlocks<< "!!!"<< G4endl;
   G4double Edep=0.;
    G4double time=0.; 
    G4ThreeVector pos;
  //  G4int  NudBlockNumber;
    for (int i=0;i<n_hit;i++) {
      Edep           = (*CHC1)[i]->GetEdep();
      pos            = (*CHC1)[i]->GetPos();
  
      time           = (*CHC1)[i]->GetTime();
      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << Edep/MeV <<  "   "  << time << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
      }        
    
      DmpNudHit* dmpNudHit = new DmpNudHit(Edep, time);
      dmpEvtNudHit->nud_totE1 += Edep;
      dmpEvtNudHit->nudHits1.push_back(*dmpNudHit);
}
}


  if (CHC2) {
    G4int n_hit = CHC2->entries();
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << "Number of NUD hits2 in this event =  " << n_hit << G4endl;  
    }   
    
    G4RunManager* runManager = G4RunManager::GetRunManager();
    DmpDetectorConstruction* dmpDetector =
      (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

    G4int NbOfNudBlocks = 4;
    
    if(NbOfNudBlocks != dmpDetector->GetNudDetectorDescription()->GetNbOfNUDStrips()) G4cout<< "WARNING NbOfNudBlocks is not "<< NbOfNudBlocks<< "!!!"<< G4endl;
    G4double Edep=0.;
    G4double time=0.; 
    G4ThreeVector pos;
  //  G4int  NudBlockNumber;
    for (int i=0;i<n_hit;i++) {
      Edep           = (*CHC2)[i]->GetEdep();
      pos            = (*CHC2)[i]->GetPos();
 
      time           = (*CHC2)[i]->GetTime();
      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << Edep/MeV <<  "   "  << time << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
      }        
    
      DmpNudHit* dmpNudHit = new DmpNudHit(Edep, time);
      dmpEvtNudHit->nud_totE2 += Edep;
      dmpEvtNudHit->nudHits2.push_back(*dmpNudHit);
}
}

 //NUD hits
 // DmpSimuNudHitsCollection* CHC3 = 0;
 // G4SDManager * SDman = G4SDManager::GetSDMpointer();  
 // G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

 
  if (CHC3) {
    G4int n_hit = CHC3->entries();
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << "Number of NUD hits3 in this event =  " << n_hit << G4endl;  
    }   
    
    G4RunManager* runManager = G4RunManager::GetRunManager();
    DmpDetectorConstruction* dmpDetector =
      (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

    G4int NbOfNudBlocks = 4;
    
    if(NbOfNudBlocks != dmpDetector->GetNudDetectorDescription()->GetNbOfNUDStrips()) G4cout<< "WARNING NbOfNudBlocks is not "<< NbOfNudBlocks<< "!!!"<< G4endl;
    G4double Edep=0.;
    G4double time=0.; 
    G4ThreeVector pos;
  //  G4int  NudBlockNumber;
   
    for (int i=0;i<n_hit;i++) {
      Edep           = (*CHC3)[i]->GetEdep();
      pos            = (*CHC3)[i]->GetPos();
 
      time           = (*CHC3)[i]->GetTime();
      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << Edep/MeV <<  "   "  << time << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
      }        
    
      DmpNudHit* dmpNudHit = new DmpNudHit(Edep, time);
      dmpEvtNudHit->nud_totE3 += Edep;
      dmpEvtNudHit->nudHits3.push_back(*dmpNudHit);

    }
 }
    if(eventNumber == debugEvent || debugEvent == -1) {
    G4cout << " total energy deposited: " << dmpEvtNudHit->nud_totE0 <<G4endl;
    G4cout << " total energy deposited: " << dmpEvtNudHit->nud_totE1 <<G4endl;
    G4cout << " total energy deposited: " << dmpEvtNudHit->nud_totE2 <<G4endl;
    G4cout << " total energy deposited: " << dmpEvtNudHit->nud_totE3 <<G4endl;
    }

}



G4bool DmpSimuNudHitEventMaker::passTotalEnergyCut(G4double cut)
{  
 // return (tt_nud_totE > cut);
return true;
}




