// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimuStkHitEventMaker.hh"
#include "G4SDManager.hh"
#include "DmpSimuStkHit.hh"
#include "DmpEvtStkHit.hh"



DmpSimuStkHitEventMaker::DmpSimuStkHitEventMaker()
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimuStkHitEventMaker::~DmpSimuStkHitEventMaker()
{
}

void DmpSimuStkHitEventMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree      = aTree;
  run       = aRun;
  StkHitEvt = new DmpEvtStkHit();
  tree->Branch("DmpEvtStkHit", "DmpEvtStkHit",  &StkHitEvt);
  //tree->Branch("debugEvent", &debugEvent,  "debugEvent/I");
  //std::cout<< "\n\n\n\n\n\n Branch booked \n\n\n\n\n"<<std::endl;

}

void DmpSimuStkHitEventMaker::beginEvent(const G4Event* evt)
{
    eventNumber =  evt->GetEventID();
    StkHitEvt->Reset();

    //StkHitEvt->eventNumber =  evt->GetEventID();
    //StkHitEvt->eventNumber =  evt->GetEventID();
    //StkHitEvt->runNumber   =  run->GetRunID();

}

/*
void DmpSimuStkHitNtupleMaker::FillStep(const G4Step* aStep)
{
}
*/

void DmpSimuStkHitEventMaker::FillEvent(const G4Event* evt)
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
      //StkHitEvt->nSiHit  =  0;
      for (int i=0;i<n_hit;i++) {

          //std::cout<<"adding hit"<<std::endl;

          ESil     = (*THC)[i]->GetEdepSil();
          ESilPrim = (*THC)[i]->GetEdepSilPrim();
          NStrip = (*THC)[i]->GetNStrip();
          NPlane = (*THC)[i]->GetNSilPlane();
          IsX    = (*THC)[i]->GetPlaneType();
          pos    = (*THC)[i]->GetPos();

          DmpStkHit* hit=new DmpStkHit();
          hit->SiHit_e  =  ESil;
          hit->SiHit_e_prim = ESilPrim;
          hit->SiHit_x = pos.x();
          hit->SiHit_y = pos.y();
          hit->SiHit_z = pos.z();
          hit->SiHit_strip  = IsX*1000000 + NPlane*100000 + NStrip;
          hit->SiHit_id = i;
          hit->SiHit_trackID  = (*THC)[i]->GetPrimTrackID();
          hit->SiHit_trackID1 = (*THC)[i]->GetTrackID1();
          hit->SiHit_trackID2 = (*THC)[i]->GetTrackID();
          hit->SiHit_ntracks = (*THC)[i]->GetNtracks();
          hit->SiHit_ntracksBack = (*THC)[i]->GetNtracksBack();
          hit->SiHit_ntracksPrim = (*THC)[i]->GetNtracksPrim();
          hit->SiHit_chrgTrks_e = (*THC)[i]->GetChrgTrkEnergy();

          ++ (StkHitEvt->nSiHit);
          StkHitEvt->SiHits.push_back(*hit);

          if(eventNumber == debugEvent || debugEvent == -1) {
              G4cout << ESil/MeV <<  "   "  << NStrip << "    " << NPlane <<  "    " << IsX << "    "
                      << (*THC)[i]->GetTrackID()
                      << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
          }

      }

  }
}






