// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimHitBgoNtupleMaker.hh"

#include "DmpDetectorConstruction.hh"
#include "DmpSimDetectorDescriptionBgo.hh"
#include "DmpSimHitBgo.hh"

#include "G4RunManager.hh"
#include "G4DigiManager.hh"
#include "G4SDManager.hh"

#include "TTree.h"

DmpSimHitBgoNtupleMaker::DmpSimHitBgoNtupleMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimHitBgoNtupleMaker::~DmpSimHitBgoNtupleMaker()
{
}

void DmpSimHitBgoNtupleMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree = aTree;

 //book ntuple branches and define ntuple data vectors here 
 tt_CalLayer_nlayer = 0;    
 tt_CalLayer_centroid   = new std::vector<double>();
 tt_CalLayer_e          = new std::vector<double>();
 tt_CalLayer_sumw2      = new std::vector<double>();
 tt_CalLayer_index      = new std::vector<int>();

 tree->Branch("tt_cal_totE",         &tt_cal_totE);
 tree->Branch("tt_cal_totE_1MeV",    &tt_cal_totE_1MeV);
 tree->Branch("tt_cal_totE_10MeV",   &tt_cal_totE_10MeV);

 tree->Branch("tt_CalLayer_nlayer",    &tt_CalLayer_nlayer,   "tt_CalLayer_nlayer/i"  );
 tree->Branch("tt_CalLayer_centroid",  &tt_CalLayer_centroid);
 tree->Branch("tt_CalLayer_e",         &tt_CalLayer_e);
 tree->Branch("tt_CalLayer_sumw2",     &tt_CalLayer_sumw2);
 tree->Branch("tt_CalLayer_index",     &tt_CalLayer_index);

 tt_CalLayer_nlayer_1MeV = 0;    
 tt_CalLayer_centroid_1MeV   = new std::vector<double>();
 tt_CalLayer_e_1MeV          = new std::vector<double>();
 tt_CalLayer_sumw2_1MeV      = new std::vector<double>();
 tt_CalLayer_index_1MeV      = new std::vector<int>();

 tree->Branch("tt_CalLayer_nlayer_1MeV",    &tt_CalLayer_nlayer_1MeV,   "tt_CalLayer_nlayer_1MeV/i"  );
 tree->Branch("tt_CalLayer_centroid_1MeV",  &tt_CalLayer_centroid_1MeV);
 tree->Branch("tt_CalLayer_e_1MeV",         &tt_CalLayer_e_1MeV);
 tree->Branch("tt_CalLayer_sumw2_1MeV",     &tt_CalLayer_sumw2_1MeV);
 tree->Branch("tt_CalLayer_index_1MeV",     &tt_CalLayer_index_1MeV);

 tt_CalHit_n  = 0;
 tt_CalHit_bar = new std::vector<int>();
 tt_CalHit_e   = new std::vector<double>();
 tree->Branch("tt_CalHit_n",      &tt_CalHit_n,   "tt_CalHit_n/i"  );
 tree->Branch("tt_CalHit_bar",  &tt_CalHit_bar);
 tree->Branch("tt_CalHit_e",      &tt_CalHit_e);

}

void DmpSimHitBgoNtupleMaker::beginEvent(const G4Event* evt)
{
  //set event number
  eventNumber = evt->GetEventID();

  //clear all ntuple data vectors here
  tt_cal_totE       = 0.;
  tt_cal_totE_1MeV  = 0.;
  tt_cal_totE_10MeV = 0.;
 
  tt_CalLayer_nlayer = 0;    
  tt_CalLayer_centroid    -> clear();
  tt_CalLayer_e           -> clear();
  tt_CalLayer_sumw2       -> clear();
  tt_CalLayer_index       -> clear();

  tt_CalLayer_nlayer_1MeV = 0;    
  tt_CalLayer_centroid_1MeV    -> clear();
  tt_CalLayer_e_1MeV           -> clear();
  tt_CalLayer_sumw2_1MeV       -> clear();
  tt_CalLayer_index_1MeV       -> clear();

  tt_CalHit_n  = 0;
  tt_CalHit_bar -> clear();
  tt_CalHit_e   -> clear();

}

void DmpSimHitBgoNtupleMaker::FillStep(const G4Step* aStep)
{
}

void DmpSimHitBgoNtupleMaker::FillEvent(const G4Event* evt)
{  
  //fill even info here, also filter and save ntuple
  //bool toKeep = true;

  //Calorimeter hits
  DmpSimHitBgosCollection* CHC = 0;
  G4SDManager * SDman = G4SDManager::GetSDMpointer();  
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

  if (HCE) {
    CHC = (DmpSimHitBgosCollection*) (HCE->GetHC(SDman->GetCollectionID("BGOHitCollection")));
  }

  if (CHC) {
    int n_hit = CHC->entries();
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << "Number of calorimeter hits in this event =  " << n_hit << G4endl;
      G4cout << "  edp  " << "  bar " << " plane " << " type " 
	     << "  x    " << "   y    " << "     z    " <<  G4endl;       
    }   
    
    G4RunManager* runManager = G4RunManager::GetRunManager();
    DmpDetectorConstruction* dmpDetector =
      (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

    G4int NbOfCALLayers = 7;
    //G4int NbOfCALBars    = 12;
    if(NbOfCALLayers != dmpDetector->GetSimDetectorDescriptionBgo()->GetNbOfCALLayers()) G4cout<< "WARNING NbOfCALLayers is not "<< NbOfCALLayers<< "!!!"<< G4endl;

    G4double xLayerSum  [7] = {0.0};
    G4double xLayerSumW [7] = {0.0};
    G4double xLayerSumW2[7] = {0.0};
    G4double yLayerSum  [7] = {0.0};
    G4double yLayerSumW [7] = {0.0};
    G4double yLayerSumW2[7] = {0.0};
    G4double xLayerSum_1MeV   [7] = {0.0};
    G4double xLayerSumW_1MeV  [7] = {0.0};
    G4double xLayerSumW2_1MeV [7] = {0.0};
    G4double yLayerSum_1MeV   [7] = {0.0};
    G4double yLayerSumW_1MeV  [7] = {0.0};
    G4double yLayerSumW2_1MeV [7] = {0.0};
    

    G4double Edep=0;
    G4ThreeVector pos;
    G4int CALBarNumber, CALPlaneNumber, CALType;
    tt_CalHit_n = 0;

    for (int i=0;i<n_hit;i++) {
      Edep           = (*CHC)[i]->GetEdepCAL();
      pos            = (*CHC)[i]->GetPos();
      CALBarNumber   = (*CHC)[i]->GetCALBarNumber();
      CALPlaneNumber = (*CHC)[i]->GetCALPlaneNumber();
      CALType        = (*CHC)[i]->GetCALType();
      if(Edep>0.0) {
	tt_CalHit_e      -> push_back(Edep);
	tt_CalHit_bar    -> push_back(CALType*1000000 + CALPlaneNumber*100000 + CALBarNumber);
	++tt_CalHit_n;
      }

      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << Edep/MeV <<  "   "  << CALBarNumber << "    " << CALPlaneNumber <<  "    " << CALType 
	       << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
      }        
      tt_cal_totE += Edep;
      if(Edep>1./MeV)  tt_cal_totE_1MeV  += Edep;
      if(Edep>10./MeV) tt_cal_totE_10MeV += Edep;
      if(CALType==1) { // x layers
	xLayerSum   [CALPlaneNumber] += Edep;
	xLayerSumW  [CALPlaneNumber] += Edep*CALBarNumber;
	xLayerSumW2 [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
	if(Edep>1./MeV) {
	  xLayerSum_1MeV   [CALPlaneNumber] += Edep;
	  xLayerSumW_1MeV  [CALPlaneNumber] += Edep*CALBarNumber;
	  xLayerSumW2_1MeV [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
	}
      }
      else if(CALType==0) { // y layers
	yLayerSum   [CALPlaneNumber] += Edep;
	yLayerSumW  [CALPlaneNumber] += Edep*CALBarNumber;
	yLayerSumW2 [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
	if(Edep>1./MeV) {
	  yLayerSum_1MeV   [CALPlaneNumber] += Edep;
	  yLayerSumW_1MeV  [CALPlaneNumber] += Edep*CALBarNumber;
	  yLayerSumW2_1MeV [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
	}
      }
      else {
	G4cout << "WARNING wrong CALType!!! " << CALType << G4endl;
      }
    }

    tt_CalLayer_nlayer = 0;
    tt_CalLayer_nlayer_1MeV = 0;
    for (int i=0;i<NbOfCALLayers;i++) {
      if(xLayerSum[i] > 0) {
	double pos = xLayerSumW[i]/xLayerSum[i];
	tt_CalLayer_centroid -> push_back(pos);
	tt_CalLayer_e        -> push_back(xLayerSum[i]);
	tt_CalLayer_sumw2    -> push_back(xLayerSumW2[i]); //width = sqrt(sumw2/e-centroid**2)
	tt_CalLayer_index    -> push_back(100+i);
	++tt_CalLayer_nlayer;
      }
      if(yLayerSum[i] > 0) {
	double pos = yLayerSumW[i]/yLayerSum[i];
	tt_CalLayer_centroid -> push_back(pos);
	tt_CalLayer_e        -> push_back(yLayerSum[i]);
	tt_CalLayer_sumw2    -> push_back(yLayerSumW2[i]); //width = sqrt(sumw2/e-centroid**2)
	tt_CalLayer_index    -> push_back(i);
	++tt_CalLayer_nlayer;
      }

      if(xLayerSum_1MeV[i] > 0) {
	double pos = xLayerSumW_1MeV[i]/xLayerSum_1MeV[i];
	tt_CalLayer_centroid_1MeV -> push_back(pos);
	tt_CalLayer_e_1MeV        -> push_back(xLayerSum_1MeV[i]);
	tt_CalLayer_sumw2_1MeV    -> push_back(xLayerSumW2_1MeV[i]);
	tt_CalLayer_index_1MeV    -> push_back(100+i);
	++tt_CalLayer_nlayer_1MeV;
      }
      if(yLayerSum_1MeV[i] > 0) {
	double pos = yLayerSumW_1MeV[i]/yLayerSum_1MeV[i];
	tt_CalLayer_centroid_1MeV -> push_back(pos);
	tt_CalLayer_e_1MeV        -> push_back(yLayerSum_1MeV[i]);
	tt_CalLayer_sumw2_1MeV    -> push_back(yLayerSumW2_1MeV[i]);
	tt_CalLayer_index_1MeV    -> push_back(i);
	++tt_CalLayer_nlayer_1MeV;
      }

      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << " xLayer " << i << " " << " esum " << xLayerSum[i] << " esumW " << xLayerSumW[i] << G4endl;
	G4cout << " yLayer " << i << " " << " esum " << yLayerSum[i] << " esumW " << yLayerSumW[i] << G4endl;
	G4cout << " 1MeV xLayer " << i << " " << " esum " << xLayerSum_1MeV[i] << " esumW " << xLayerSumW_1MeV[i] << G4endl;
	G4cout << " 1MeV yLayer " << i << " " << " esum " << yLayerSum_1MeV[i] << " esumW " << yLayerSumW_1MeV[i] << G4endl;
      }
    }

    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << " total energy deposited: " << tt_cal_totE << " " << tt_cal_totE_1MeV << " "
	     << tt_cal_totE_10MeV << G4endl;
    }

  }

}

G4bool DmpSimHitBgoNtupleMaker::passTotalEnergyCut(G4double cut) 
{  
  return (tt_cal_totE > cut);
}




