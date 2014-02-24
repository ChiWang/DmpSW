// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013
//  - modified by C.Wang 10/02/2014 --> converted from NTuple maker to Event class maker

#include "DmpEvtBgoHit.hh"
#include "DmpSimuBgoHitEventMaker.hh"

#include "DmpDetectorConstruction.hh"
#include "DmpBgoDetectorDescription.hh"
#include "DmpSimuBgoHit.hh"

#include "G4RunManager.hh"
//#include "G4DigiManager.hh"
#include "G4SDManager.hh"

#include "TTree.h"
#include "DmpParameterBgo.h"    // in Kernel
using namespace DmpParameter::Bgo;  // use parameter kPlaneNb

DmpSimuBgoHitEventMaker::DmpSimuBgoHitEventMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimuBgoHitEventMaker::~DmpSimuBgoHitEventMaker()
{
}

void DmpSimuBgoHitEventMaker::book(const G4Run* aRun, TTree* aTree)
{ 
  tree = aTree;
  BgoHitEvt = new DmpEvtBgoHit();
  tree->Branch("DmpEvtBgoHit", "DmpEvtBgoHit",  &BgoHitEvt);
}

void DmpSimuBgoHitEventMaker::beginEvent(const G4Event* evt)
{
  eventNumber = evt->GetEventID();
  BgoHitEvt->Reset();
}

// *TODO: tt_ to event class
void DmpSimuBgoHitEventMaker::FillEvent(const G4Event* evt){
  DmpSimuBgoHitsCollection* CHC = 0;
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if (HCE) {
    G4SDManager* SDman = G4SDManager::GetSDMpointer();  
    CHC = (DmpSimuBgoHitsCollection*) (HCE->GetHC(SDman->GetCollectionID("BGOHitCollection")));
  }
  if (CHC == 0) return;
/* needless
    G4RunManager* runManager = G4RunManager::GetRunManager();
    DmpDetectorConstruction* dmpDetector = (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());
    if(kPlaneNb != (dmpDetector->GetBgoDetectorDescription()->GetNbOfCALLayers())/2) G4cout<< "WARNING CALLayers is not "<< kPlaneNb<< "!!!"<< G4endl;
*/
// *TODO:  7 = kPlaneNb
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
  
  int ind_maxBar_layer[14];
  int ind_maxBarPos_layer[14];
  int ind_maxBarNeg_layer[14];
  double e_maxBar_layer[14];
  double e_maxBarPos_layer[14];
  double e_maxBarNeg_layer[14];
  for (int i=0;i<kPlaneNb*2;i++) {
    ind_maxBar_layer[i]    = -1;
    ind_maxBarPos_layer[i] = -1;
    ind_maxBarNeg_layer[i] = -1;
    e_maxBar_layer[i]      = 0.;
    e_maxBarPos_layer[i]   = 0.;
    e_maxBarNeg_layer[i]   = 0.;
  }

//------------------------------------------------------------------- hit loop
// *TODO: in Psd/src/DmpSimuPsdHitEventMaker.cc, create object DmpPsdHit but not delete it, why?
  int n_hit = CHC->entries();
/* needless
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << "Number of calorimeter hits in this event =  " << n_hit << G4endl;
      G4cout << "  edp  " << "  bar " << " plane " << " type " 
	     << "  x    " << "   y    " << "     z    " <<  G4endl;       
    }
*/
  DmpBgoHit* hit = new DmpBgoHit();
  G4double Edep=0;
  G4double EdepPos=0;
  G4double EdepNeg=0;
  G4ThreeVector pos;
  G4int CALBarNumber, CALPlaneNumber, CALType;
  for (int i=0;i<n_hit;i++) {
    Edep           = (*CHC)[i]->GetEdepCAL();
    if(Edep<0.0)  {G4cout<<"E of hit < 0.0"<<G4endl;continue;}
    EdepPos        = (*CHC)[i]->GetEdepPos();
    EdepNeg        = (*CHC)[i]->GetEdepNeg();
    pos            = (*CHC)[i]->GetPos();
    CALBarNumber   = (*CHC)[i]->GetCALBarNumber();
    CALPlaneNumber = (*CHC)[i]->GetCALPlaneNumber();
    CALType        = (*CHC)[i]->GetCALType();     // ??

    { // for single G4Step ??
      int layer = 2*CALPlaneNumber;             //y layer
      if(CALType==1) layer= 2*CALPlaneNumber+1; //x layer
      if(e_maxBar_layer[layer] < Edep) {	    
        e_maxBar_layer[layer] = Edep;	    
        ind_maxBar_layer[layer] = CALBarNumber;	 
      }
      if(e_maxBarPos_layer[layer] < EdepPos) {	    
        e_maxBarPos_layer[layer] = EdepPos;	    
        ind_maxBarPos_layer[layer] = CALBarNumber;	 
      }
      if(e_maxBarNeg_layer[layer] < EdepNeg) {	    
        e_maxBarNeg_layer[layer] = EdepNeg;	    
        ind_maxBarNeg_layer[layer] = CALBarNumber;	 
      }
    }
      // why in Edep > 0.0 ?? 
    hit->Hit_e    = Edep;
    hit->Hit_bar  = CALType*1000000 + CALPlaneNumber*100000 + CALBarNumber;
    hit->Hit_epos = EdepPos;
    hit->Hit_eneg = EdepNeg;
    hit->Hit_sumposition = (*CHC)[i]->GetSumPosition();
	BgoHitEvt->BgoHits.push_back(*hit);
    ++(BgoHitEvt->Hit_n);
/*  needless
      if(eventNumber == debugEvent || debugEvent == -1) {
	G4cout << Edep/MeV <<  "   "  << CALBarNumber << "    " << CALPlaneNumber <<  "    " << CALType 
	       << "     " << pos.x()/mm << " " <<  pos.y()/mm << " " <<  pos.z()/mm << G4endl;
      }
*/
    BgoHitEvt->totE += Edep;
    if(Edep>1./MeV)  BgoHitEvt->totE_1MeV  += Edep;
    if(Edep>10./MeV) BgoHitEvt->totE_10MeV += Edep;
    if(CALType==1) { // x layers
      xLayerSum   [CALPlaneNumber] += Edep;
      xLayerSumW  [CALPlaneNumber] += Edep*CALBarNumber;
      xLayerSumW2 [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
      if(Edep>1./MeV) {
        xLayerSum_1MeV   [CALPlaneNumber] += Edep;
        xLayerSumW_1MeV  [CALPlaneNumber] += Edep*CALBarNumber;
        xLayerSumW2_1MeV [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
      }
    }else if(CALType==0) { // y layers
      yLayerSum   [CALPlaneNumber] += Edep;
      yLayerSumW  [CALPlaneNumber] += Edep*CALBarNumber;
      yLayerSumW2 [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
      if(Edep>1./MeV) {
        yLayerSum_1MeV   [CALPlaneNumber] += Edep;
        yLayerSumW_1MeV  [CALPlaneNumber] += Edep*CALBarNumber;
        yLayerSumW2_1MeV [CALPlaneNumber] += Edep*CALBarNumber*CALBarNumber;
      }
    }else {
      G4cout << "WARNING wrong CALType!!! " << CALType << G4endl;
    }
  }
//------------------------------------------------------------------- hit loop

  for (int i=0;i<kPlaneNb*2;i++) {
    if(ind_maxBar_layer[i] != -1) {
      BgoHitEvt->MaxBar_layer-> push_back(i);
      BgoHitEvt->MaxBar_ind  -> push_back(ind_maxBar_layer[i]);
      BgoHitEvt->MaxBar_e    -> push_back(e_maxBar_layer[i]  );
    }
    if(ind_maxBarPos_layer[i] != -1) {
      BgoHitEvt->MaxBarPos_layer -> push_back(i);
      BgoHitEvt->MaxBarPos_ind   -> push_back(ind_maxBarPos_layer[i]);
      BgoHitEvt->MaxBarPos_e     -> push_back(e_maxBarPos_layer[i]  );
    }
    if(ind_maxBarNeg_layer[i] != -1) {
	  BgoHitEvt->MaxBarNeg_layer -> push_back(i);
	  BgoHitEvt->MaxBarNeg_ind   -> push_back(ind_maxBarNeg_layer[i]);
	  BgoHitEvt->MaxBarNeg_e     -> push_back(e_maxBarNeg_layer[i]  );
    }
  }

  for (int i=0;i<kPlaneNb;i++) {
    if(xLayerSum[i] > 0) {
      double pos = xLayerSumW[i]/xLayerSum[i];
      BgoHitEvt->Layer_centroid -> push_back(pos);
      BgoHitEvt->Layer_e        -> push_back(xLayerSum[i]);
      BgoHitEvt->Layer_sumw2    -> push_back(xLayerSumW2[i]); //width = sqrt(sumw2/e-centroid**2)
      BgoHitEvt->Layer_index    -> push_back(100+i);
      ++(BgoHitEvt->Layer_nlayer);
    }
    if(yLayerSum[i] > 0) {
      double pos = yLayerSumW[i]/yLayerSum[i];
      BgoHitEvt->Layer_centroid -> push_back(pos);
      BgoHitEvt->Layer_e        -> push_back(yLayerSum[i]);
      BgoHitEvt->Layer_sumw2    -> push_back(yLayerSumW2[i]); //width = sqrt(sumw2/e-centroid**2)
      BgoHitEvt->Layer_index    -> push_back(i);
      ++(BgoHitEvt->Layer_nlayer);
    }
    if(xLayerSum_1MeV[i] > 0) {
      double pos = xLayerSumW_1MeV[i]/xLayerSum_1MeV[i];
      BgoHitEvt->Layer_centroid_1MeV -> push_back(pos);
      BgoHitEvt->Layer_e_1MeV        -> push_back(xLayerSum_1MeV[i]);
      BgoHitEvt->Layer_sumw2_1MeV    -> push_back(xLayerSumW2_1MeV[i]);
      BgoHitEvt->Layer_index_1MeV    -> push_back(100+i);
      ++(BgoHitEvt->Layer_nlayer_1MeV);
    }
    if(yLayerSum_1MeV[i] > 0) {
      double pos = yLayerSumW_1MeV[i]/yLayerSum_1MeV[i];
      BgoHitEvt->Layer_centroid_1MeV -> push_back(pos);
      BgoHitEvt->Layer_e_1MeV        -> push_back(yLayerSum_1MeV[i]);
      BgoHitEvt->Layer_sumw2_1MeV    -> push_back(yLayerSumW2_1MeV[i]);
      BgoHitEvt->Layer_index_1MeV    -> push_back(i);
      ++(BgoHitEvt->Layer_nlayer_1MeV);
    }
/* needless
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << " xLayer " << i << " " << " esum " << xLayerSum[i] << " esumW " << xLayerSumW[i] << G4endl;
      G4cout << " yLayer " << i << " " << " esum " << yLayerSum[i] << " esumW " << yLayerSumW[i] << G4endl;
      G4cout << " 1MeV xLayer " << i << " " << " esum " << xLayerSum_1MeV[i] << " esumW " << xLayerSumW_1MeV[i] << G4endl;
      G4cout << " 1MeV yLayer " << i << " " << " esum " << yLayerSum_1MeV[i] << " esumW " << yLayerSumW_1MeV[i] << G4endl;
    }
*/
  }

/*  needless
    if(eventNumber == debugEvent || debugEvent == -1) {
      G4cout << " total energy deposited: " << BgoHitEvt->totE << " " << BgoHitEvt->totE_1MeV << " " << BgoHitEvt->totE_10MeV << G4endl;
    }
 */
}

G4bool DmpSimuBgoHitEventMaker::passTotalEnergyCut(G4double cut){
  return (BgoHitEvt->totE > cut);
}


