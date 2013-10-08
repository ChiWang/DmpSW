// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimuStkHitNtupleMaker.hh"

#include "G4SDManager.hh"
#include "DmpSimuStkHit.hh"

#include "TTree.h"

DmpSimuStkHitNtupleMaker::DmpSimuStkHitNtupleMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimuStkHitNtupleMaker::~DmpSimuStkHitNtupleMaker()
{
}

void DmpSimuStkHitNtupleMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree = aTree;

 //book ntuple branches and define ntuple data vectors here 

 tt_SiHit_n = 0;
 tt_SiHit_id = new std::vector<int>();
 tt_SiHit_strip = new std::vector<int>();
 tt_SiHit_trackID  = new std::vector<unsigned int>();
 tt_SiHit_trackID1 = new std::vector<unsigned int>();
 tt_SiHit_trackID2 = new std::vector<unsigned int>();
 tt_SiHit_ntracks     = new std::vector<int>();
 tt_SiHit_ntracksBack = new std::vector<int>();
 tt_SiHit_ntracksPrim = new std::vector<int>();
 tt_SiHit_e     = new std::vector<double>();
 tt_SiHit_e_prim= new std::vector<double>();
 tt_SiHit_x     = new std::vector<double>();
 tt_SiHit_y     = new std::vector<double>();
 tt_SiHit_z     = new std::vector<double>();

 tree->Branch("tt_SiHit_n",      &tt_SiHit_n,   "tt_SiHit_n/i"  );
 tree->Branch("tt_SiHit_strip",  &tt_SiHit_strip);
 tree->Branch("tt_SiHit_id",     &tt_SiHit_id);
 tree->Branch("tt_SiHit_trackID",&tt_SiHit_trackID);
 tree->Branch("tt_SiHit_trackID1",&tt_SiHit_trackID1);
 tree->Branch("tt_SiHit_trackID2",&tt_SiHit_trackID2);
 tree->Branch("tt_SiHit_ntracks",&tt_SiHit_ntracks);
 tree->Branch("tt_SiHit_ntracksBack",&tt_SiHit_ntracksBack);
 tree->Branch("tt_SiHit_ntracksPrim",&tt_SiHit_ntracksPrim);
 tree->Branch("tt_SiHit_e",      &tt_SiHit_e);
 tree->Branch("tt_SiHit_e_prim", &tt_SiHit_e_prim);
 tree->Branch("tt_SiHit_x",      &tt_SiHit_x);
 tree->Branch("tt_SiHit_y",      &tt_SiHit_y);
 tree->Branch("tt_SiHit_z",      &tt_SiHit_z);

}

void DmpSimuStkHitNtupleMaker::beginEvent(const G4Event* evt)
{
  //set event number
  eventNumber = evt->GetEventID();

 //clear all ntuple data vectors here
  tt_SiHit_n = 0;
  tt_SiHit_e     -> clear();
  tt_SiHit_e_prim-> clear();
  tt_SiHit_x     -> clear();
  tt_SiHit_y     -> clear();
  tt_SiHit_z     -> clear();
  tt_SiHit_strip -> clear();
  tt_SiHit_id    -> clear();
  tt_SiHit_trackID  -> clear();
  tt_SiHit_trackID1 -> clear();
  tt_SiHit_trackID2 -> clear();
  tt_SiHit_ntracks     -> clear();
  tt_SiHit_ntracksBack -> clear();
  tt_SiHit_ntracksPrim -> clear();

}

void DmpSimuStkHitNtupleMaker::FillStep(const G4Step* aStep)
{
}

void DmpSimuStkHitNtupleMaker::FillEvent(const G4Event* evt)
{  
  
  //Tracker hits
  DmpSimuStkHitsCollection* THC = 0;
  G4SDManager * SDman = G4SDManager::GetSDMpointer();  
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

  if (HCE) {
    THC = (DmpSimuStkHitsCollection*) (HCE->GetHC(SDman->GetCollectionID("STKHitCollection")));
  }

  if (THC) {
    int n_hit = THC->entries();
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << "Number of track hits in this event =  " << n_hit << G4endl;
      G4cout << "  edp  " << "  strip " << " plane " << " type " 
	     << "  x    " << "   y    " << "     z    " <<  G4endl;       
    }   
    G4double ESil=0;
    G4double ESilPrim=0;
    G4ThreeVector pos;
    G4int NStrip, NPlane, IsX;
    tt_SiHit_n = 0;
    for (int i=0;i<n_hit;i++) {
      ESil     = (*THC)[i]->GetEdepSil();
      ESilPrim = (*THC)[i]->GetEdepSilPrim();
      NStrip = (*THC)[i]->GetNStrip();
      NPlane = (*THC)[i]->GetNSilPlane();
      IsX    = (*THC)[i]->GetPlaneType();
      pos    = (*THC)[i]->GetPos();
      tt_SiHit_e      -> push_back(ESil);
      tt_SiHit_e_prim -> push_back(ESilPrim);
      tt_SiHit_x -> push_back(pos.x());
      tt_SiHit_y -> push_back(pos.y());
      tt_SiHit_z -> push_back(pos.z());
      tt_SiHit_strip   -> push_back(IsX*1000000 + NPlane*100000 + NStrip);
      tt_SiHit_id      -> push_back(i);
      tt_SiHit_trackID -> push_back((*THC)[i]->GetPrimTrackID());
      tt_SiHit_trackID1 -> push_back((*THC)[i]->GetTrackID1());
      tt_SiHit_trackID2 -> push_back((*THC)[i]->GetTrackID());
      tt_SiHit_ntracks -> push_back((*THC)[i]->GetNtracks());
      tt_SiHit_ntracksBack -> push_back((*THC)[i]->GetNtracksBack());
      tt_SiHit_ntracksPrim -> push_back((*THC)[i]->GetNtracksPrim());
      ++tt_SiHit_n;
      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << ESil/MeV <<  "   "  << NStrip << "    " << NPlane <<  "    " << IsX << "    " 
	       << (*THC)[i]->GetTrackID()
	       << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
      }        
    }
  }


}






