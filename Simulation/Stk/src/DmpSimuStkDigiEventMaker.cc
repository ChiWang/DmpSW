//
// Author(s):
//  - creation by Andrii Tykhonov, 27/01/2014

#include "DmpSimuStkDigiEventMaker.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"

#include "DmpSimuStkDigi.hh"
#include "DmpSimuStkDigitizer.hh"

#include "G4RunManager.hh"
#include "DmpDetectorConstruction.hh"
#include "DmpStkDetectorDescription.hh"



DmpSimuStkDigiEventMaker::DmpSimuStkDigiEventMaker()
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimuStkDigiEventMaker::~DmpSimuStkDigiEventMaker()
{
}

void DmpSimuStkDigiEventMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  /*
   *   Book an STK Digit branch
   */
  tree = aTree;
  run  = aRun;
  StkDigitEvt = new DmpEvtStkDigit();
  tree->Branch("DmpEvtStkDigit",  "DmpEvtStkDigit",  &StkDigitEvt);


  /*
   *   Get number of readout channels
   */
  G4RunManager* runManager = G4RunManager::GetRunManager();
  DmpDetectorConstruction* dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

  G4int NStripsPerLadder = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRStrips();
  G4int NLadderPerBlock  = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRTiles();
  G4int NBlockPerLayer   = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRBlocks();
  G4int NDoubleLayers    = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRLayers();  

  G4int NStripsPerLayer = NStripsPerLadder*NLadderPerBlock*NBlockPerLayer;  
  NbOfROChannels = NStripsPerLayer * NDoubleLayers ;//divided by 2 for readout, but mutiply by 2 for double layer
  G4cout << "DmpSimuStkDigiNtupleMaker::book() called " << G4endl;
  G4cout <<  "  Total number of readout channels : " << NbOfROChannels << G4endl;
}

void DmpSimuStkDigiEventMaker::beginEvent(const G4Event* evt)
{

    StkDigitEvt->Reset();
    //StkDigitEvt->eventNumber = evt->GetEventID();
    //StkDigitEvt->runNumber = run->GetRunID();
    //StkDigitEvt->NbOfROChannels = NbOfROChannels;
}


/*
void DmpSimuStkDigiEventMaker::FillStep(const G4Step* aStep)
{
}
*/

void DmpSimuStkDigiEventMaker::FillEvent(const G4Event* evt)
{  
    G4DigiManager * fDM = G4DigiManager::GetDMpointer();
    G4int myDigiCollID = fDM->GetDigiCollectionID("STKDigitsCollection");
    DmpSimuStkDigitsCollection * DC = (DmpSimuStkDigitsCollection*)fDM->GetDigiCollection( myDigiCollID );
    
    DmpSimuStkDigitizer * myDM = (DmpSimuStkDigitizer*)fDM->FindDigitizerModule( "DmpSimuStkDigitizer" );
    G4int *ThitID = myDM->GetThitID();
    
    if(DC) {
        //G4cout << "DmpRootNtupleManager: Total STK Digits " << DC->entries() << G4endl;
        //G4cout << G4endl;
        //G4int NbOfTKRChannels =  73728;
        //G4int NbOfTKRChannels =  122880;

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
        //StkDigitEvt->nSiDigit = 0;
        for (G4int j=0;j<NbOfROChannels;j++) {
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

            DmpStkDigit* digit=new DmpStkDigit();
            digit->SiDigit_e = EChannel;
            digit->SiDigit_e_prim = EChannelPrim;
            digit->SiDigit_strip = IsX*1000000 + NPlane*100000 + NStrip;
            digit->SiDigit_trackID = (*DC)[i]->GetPrimTrackID();
            digit->SiDigit_ntracks = (*DC)[i]->GetNtracks();
            digit->SiDigit_ntracksBack = (*DC)[i]->GetNtracksBack();
            digit->SiDigit_ntracksPrim = (*DC)[i]->GetNtracksPrim();
            digit->SiDigit_nhits =(*DC)[i]->GetNhits();
            digit->SiDigit_nhitsBack = (*DC)[i]->GetNhitsBack();
            digit->SiDigit_hitID = (*DC)[i]->GetHitID();
            digit->SiDigit_hitID1 =(*DC)[i]->GetHitID1();
            digit->SiDigit_hitID2 = (*DC)[i]->GetHitID2();

            ++(StkDigitEvt->nSiDigit);
            StkDigitEvt->SiDigits.push_back(*digit);

            //G4cout << " " << IsX << "|" << NPlane  << "|" << NStrip << "|"  << EChannel
            //	     << "|"  << EChannelPrim << "|"  << (*DC)[i]->GetPrimTrackID() << G4endl;
            //G4int NChannel = NStrip + (NPlane*2 + IsX)*6144;
            //G4cout << " location " << i << "  strip number in layer " << NStrip << " channel number "  << NChannel  << G4endl;
        }
    }
    //G4cout << "Total Silicon Digits " << tt_SiDigit_n << G4endl;
}


G4bool DmpSimuStkDigiEventMaker::passTotalDigiCut(G4int cut)
{  
  return (StkDigitEvt->nSiDigit > cut);
}








