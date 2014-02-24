// Description: ntuple maker for the PSD
//
// Author(s):
//  - created by Zhou Yong. 10/10/2013
//  - modified by A.Tykhonov 05/02/2014 --> converted from NTuple maker to Event class maker

#include "DmpSimuPsdHitEventMaker.hh"

#include "G4SDManager.hh"
#include "DmpSimuPsdHit.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "TTree.h"


DmpSimuPsdHitEventMaker::DmpSimuPsdHitEventMaker()
    :tree(0)
{
    //set debugEvent to a particular event number for debug printout
    //debugEvent = -1; //-1 is all events
    debugEvent = -100; //-100 no event
}

DmpSimuPsdHitEventMaker::~DmpSimuPsdHitEventMaker()
{

}

void DmpSimuPsdHitEventMaker::book(const G4Run* aRun,TTree* aTree)
{
    tree=aTree;
    PsdHitEvt = new DmpEvtPsdHit();
    tree->Branch("DmpEvtPsdHit", "DmpEvtPsdHit",  &PsdHitEvt);

}

void DmpSimuPsdHitEventMaker::beginEvent(const G4Event* evt)
{
    eventNumber = evt->GetEventID();
    PsdHitEvt->Reset();
}

void DmpSimuPsdHitEventMaker::FillEvent(const G4Event* evt)
{
    DmpSimuPsdHitsCollection* THC=0;
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

    if(HCE){
        THC = (DmpSimuPsdHitsCollection*) (HCE->GetHC(SDman->GetCollectionID("PSDHitCollection")));
    }

    if(THC){
      int n_hit = THC->entries();
      if(eventNumber==debugEvent || debugEvent==-1){
	
      }

      G4int StripNum;
      G4double StripEdep;
      for(int i=0;i<n_hit;i++){
	StripNum=(*THC)[i]->GetStripNumber();
	StripEdep=(*THC)[i]->GetEdep();
	  
	DmpPsdHit* hit = new  DmpPsdHit();

	hit->strip = StripNum;
	hit->edep  = StripEdep;
	
	hit->pos_x =(*THC)[i]->GetPos().x();
	hit->pos_y =(*THC)[i]->GetPos().y();
	hit->pos_z =(*THC)[i]->GetPos().z();
	
	hit->ntracks     = (*THC)[i]->GetNtracks();
	hit->ntracksBack = (*THC)[i]->GetNtracksBack();
	
	hit->sumposition = (*THC)[i]->GetSumPosition();
	
	PsdHitEvt->PsdHits.push_back(*hit);
	++(PsdHitEvt->nPsdHit);
      }
      
      if(eventNumber==debugEvent || debugEvent==-1){
	
      }
    }
}

