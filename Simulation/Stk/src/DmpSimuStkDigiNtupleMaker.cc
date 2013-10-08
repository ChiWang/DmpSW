// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimuStkDigiNtupleMaker.hh"

#include "G4SDManager.hh"
#include "G4DigiManager.hh"

#include "DmpSimuStkDigi.hh"
#include "DmpSimuStkDigitizer.hh"

#include "TTree.h"

DmpSimuStkDigiNtupleMaker::DmpSimuStkDigiNtupleMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimuStkDigiNtupleMaker::~DmpSimuStkDigiNtupleMaker()
{
}

void DmpSimuStkDigiNtupleMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree = aTree;

 //book ntuple branches and define ntuple data vectors here 

 tt_SiDigit_n = 0;
 tt_SiDigit_strip   = new std::vector<int>();
 tt_SiDigit_trackID = new std::vector<unsigned int>();
 tt_SiDigit_e       = new std::vector<double>();
 tt_SiDigit_e_prim  = new std::vector<double>();
 tt_SiDigit_ntracks     = new std::vector<int>();
 tt_SiDigit_ntracksBack = new std::vector<int>();
 tt_SiDigit_ntracksPrim = new std::vector<int>();
 tt_SiDigit_nhits       = new std::vector<int>();
 tt_SiDigit_nhitsBack   = new std::vector<int>();
 tt_SiDigit_hitID       = new std::vector<int>();
 tt_SiDigit_hitID1      = new std::vector<int>();
 tt_SiDigit_hitID2      = new std::vector<int>();

 tree->Branch("tt_SiDigit_n",      &tt_SiDigit_n,   "tt_SiDigit_n/i"  );
 tree->Branch("tt_SiDigit_strip",  &tt_SiDigit_strip);
 tree->Branch("tt_SiDigit_trackID",&tt_SiDigit_trackID);
 tree->Branch("tt_SiDigit_e",      &tt_SiDigit_e);
 tree->Branch("tt_SiDigit_e_prim", &tt_SiDigit_e_prim);
 tree->Branch("tt_SiDigit_ntracks",    &tt_SiDigit_ntracks);
 tree->Branch("tt_SiDigit_ntracksBack",&tt_SiDigit_ntracksBack);
 tree->Branch("tt_SiDigit_ntracksPrim",&tt_SiDigit_ntracksPrim);
 tree->Branch("tt_SiDigit_nhits",      &tt_SiDigit_nhits);
 tree->Branch("tt_SiDigit_nhitsBack",  &tt_SiDigit_nhitsBack);
 tree->Branch("tt_SiDigit_hitID",      &tt_SiDigit_hitID);
 tree->Branch("tt_SiDigit_hitID1",     &tt_SiDigit_hitID1);
 tree->Branch("tt_SiDigit_hitID2",     &tt_SiDigit_hitID2);

}

void DmpSimuStkDigiNtupleMaker::beginEvent(const G4Event* evt)
{
  //set event number
  eventNumber = evt->GetEventID();

 //clear all ntuple data vectors here
  tt_SiDigit_n = 0;
  tt_SiDigit_e       -> clear();
  tt_SiDigit_e_prim  -> clear();
  tt_SiDigit_strip   -> clear();
  tt_SiDigit_trackID -> clear();
  tt_SiDigit_ntracks     -> clear();
  tt_SiDigit_ntracksBack -> clear();
  tt_SiDigit_ntracksPrim -> clear();
  tt_SiDigit_nhits       -> clear();
  tt_SiDigit_nhitsBack   -> clear();
  tt_SiDigit_hitID       -> clear();
  tt_SiDigit_hitID1      -> clear();
  tt_SiDigit_hitID2      -> clear();

}

void DmpSimuStkDigiNtupleMaker::FillStep(const G4Step* aStep)
{
}

void DmpSimuStkDigiNtupleMaker::FillEvent(const G4Event* evt)
{  
  
  G4DigiManager * fDM = G4DigiManager::GetDMpointer();
  G4int myDigiCollID = fDM->GetDigiCollectionID("STKDigitsCollection");    
  DmpSimuStkDigitsCollection * DC = (DmpSimuStkDigitsCollection*)fDM->GetDigiCollection( myDigiCollID );

  DmpSimuStkDigitizer * myDM = 
    (DmpSimuStkDigitizer*)fDM->FindDigitizerModule( "DmpSimuStkDigitizer" );

  G4int *ThitID = myDM->GetThitID();

  if(DC) {
    G4cout << "DmpRootNtupleManager: Total STK Digits " << DC->entries() << G4endl;
    G4cout << G4endl;
    
    G4int NbOfTKRChannels =  73728;
    /***
	for (G4int i=0;i<NbOfTKRChannels ;i++) {
	G4int j = (ThitID)[i];
	if(j!=-1) G4cout << "digit on channel " << i << " at collection location " << j << "  energy  " << (*DC)[j]->GetEnergy() <<  G4endl;
	}
    ***/
    //G4cout << " i|X|Lay|C|E|Eprim/Id   " <<G4endl;
    
    //G4int n_digi =  DC->entries();
    G4int NStrip, NPlane, IsX;
    //G4double Energy_Threshold = 10.*keV;
    G4double Energy_Threshold = 0.*keV;
    //for (G4int i=0;i<n_digi;i++) {
    for (G4int j=0;j<NbOfTKRChannels;j++) {
      //SiDigit
      G4int i = (ThitID)[j];
      if(i==-1) continue;
      if((*DC)[i]->GetDigiType()!=0) continue;
      
      G4double EChannel     = (*DC)[i]->GetEnergy();
      // energy threhold
      if(EChannel < Energy_Threshold) continue;
      NStrip = (*DC)[i]->GetStripNumber();
      NPlane = (*DC)[i]->GetPlaneNumber();
      IsX    = (*DC)[i]->GetPlaneType();
      G4double EChannelPrim = (*DC)[i]->GetEnergyPrim();
      tt_SiDigit_e       -> push_back(EChannel);
      tt_SiDigit_e_prim  -> push_back(EChannelPrim);
      tt_SiDigit_strip   -> push_back(IsX*1000000 + NPlane*100000 + NStrip);
      tt_SiDigit_trackID -> push_back((*DC)[i]->GetPrimTrackID());
      tt_SiDigit_ntracks     -> push_back((*DC)[i]->GetNtracks());
      tt_SiDigit_ntracksBack -> push_back((*DC)[i]->GetNtracksBack());
      tt_SiDigit_ntracksPrim -> push_back((*DC)[i]->GetNtracksPrim());
      tt_SiDigit_nhits       -> push_back((*DC)[i]->GetNhits());
      tt_SiDigit_nhitsBack   -> push_back((*DC)[i]->GetNhitsBack());
      tt_SiDigit_hitID       -> push_back((*DC)[i]->GetHitID());
      tt_SiDigit_hitID1      -> push_back((*DC)[i]->GetHitID1());
      tt_SiDigit_hitID2      -> push_back((*DC)[i]->GetHitID2());
      ++tt_SiDigit_n;
      //G4cout << " " << IsX << "|" << NPlane  << "|" << NStrip << "|"  << EChannel 
      //	     << "|"  << EChannelPrim << "|"  << (*DC)[i]->GetPrimTrackID() << G4endl;
      //G4int NChannel = NStrip + (NPlane*2 + IsX)*6144;
      //G4cout << " location " << i << "  strip number in layer " << NStrip << " channel number "  << NChannel  << G4endl;
      
    }
  }
  //G4cout << "Total Silicon Digits " << tt_SiDigit_n << G4endl;


}






