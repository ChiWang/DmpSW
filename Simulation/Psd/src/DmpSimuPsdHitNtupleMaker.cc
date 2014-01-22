// Description: ntuple maker for the PSD
//
// Author(s):
//  - created by Zhou Yong. 10/10/2013

#include "DmpSimuPsdHitNtupleMaker.hh"

#include "G4SDManager.hh"
#include "DmpSimuPsdHit.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "TTree.h"


DmpSimuPsdHitNtupleMaker::DmpSimuPsdHitNtupleMaker()
    :tree(0)
{
    //set debugEvent to a particular event number for debug printout
    //debugEvent = -1; //-1 is all events
    debugEvent = -100; //-100 no event
}

DmpSimuPsdHitNtupleMaker::~DmpSimuPsdHitNtupleMaker()
{

}

void DmpSimuPsdHitNtupleMaker::book(const G4Run* aRun,TTree* aTree)
{
    tree=aTree;

    tt_PsdHit_n = 0;
    tt_PsdHit_strip        = new std::vector<int>();
    tt_PsdHit_ntracks      = new std::vector<int>();
    tt_PsdHit_ntracksBack  = new std::vector<int>();
    tt_PsdHit_edep         = new std::vector<double>();
    tt_PsdHit_sumposition  = new std::vector<double>();
    tt_PsdHit_pos_x        = new std::vector<double>();
    tt_PsdHit_pos_y        = new std::vector<double>();
    tt_PsdHit_pos_z        = new std::vector<double>();

    tree->Branch("tt_PsdHit_n",&tt_PsdHit_n,"tt_PsdHit_n/I");
    tree->Branch("tt_PsdHit_strip",&tt_PsdHit_strip);
    tree->Branch("tt_PsdHit_ntracks",&tt_PsdHit_ntracks);
    tree->Branch("tt_PsdHit_ntracksBack",&tt_PsdHit_ntracksBack);
    tree->Branch("tt_PsdHit_pos_x",&tt_PsdHit_pos_x);
    tree->Branch("tt_PsdHit_pos_y",&tt_PsdHit_pos_y);
    tree->Branch("tt_PsdHit_pos_z",&tt_PsdHit_pos_z);
    tree->Branch("tt_PsdHit_edep",&tt_PsdHit_edep);
    tree->Branch("tt_PsdHit_sumposition",  &tt_PsdHit_sumposition);

}

void DmpSimuPsdHitNtupleMaker::beginEvent(const G4Event* evt)
{
    eventNumber = evt->GetEventID();

    tt_PsdHit_n = 0;
    tt_PsdHit_strip       ->clear();
    tt_PsdHit_ntracks     ->clear();
    tt_PsdHit_ntracksBack ->clear();
    tt_PsdHit_pos_x       ->clear();
    tt_PsdHit_pos_y       ->clear();
    tt_PsdHit_pos_z       ->clear();
    tt_PsdHit_sumposition ->clear();
    tt_PsdHit_edep        ->clear();
}

void DmpSimuPsdHitNtupleMaker::FillEvent(const G4Event* evt)
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
	  
	tt_PsdHit_strip->push_back(StripNum);
	tt_PsdHit_edep ->push_back(StripEdep);
	
	tt_PsdHit_pos_x->push_back((*THC)[i]->GetPos().x());
	tt_PsdHit_pos_y->push_back((*THC)[i]->GetPos().y());
	tt_PsdHit_pos_z->push_back((*THC)[i]->GetPos().z());
	
	tt_PsdHit_ntracks    ->push_back((*THC)[i]->GetNtracks());
	tt_PsdHit_ntracksBack->push_back((*THC)[i]->GetNtracksBack());
	
	tt_PsdHit_sumposition->push_back((*THC)[i]->GetSumPosition());
	
	tt_PsdHit_n++;
      }
      
      if(eventNumber==debugEvent || debugEvent==-1){
	
      }
    }
}

void save()
{

}
