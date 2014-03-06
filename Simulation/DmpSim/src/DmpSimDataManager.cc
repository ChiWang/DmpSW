/*
 *  $Id: DmpSimDataManager.cc, 2014-03-06 16:27:45 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include <time.h>

#include "TFile.h"
#include "TTree.h"

#include "G4Run.hh"
#include "G4Event.hh"

#include "DmpEvtHeader.h"
#include "DmpSimDataManager.h"
#include "DmpEventRaw.h"
#include "DmpEvtSimPrimaryParticle.h"

DmpSimDataManager* DmpSimDataManager::fInstance = 0;
//-------------------------------------------------------------------

DmpSimDataManager* DmpSimDataManager::GetInstance(){
  if (fInstance == 0){
    fInstance = new DmpSimDataManager();
  }
  return fInstance;
}

void DmpSimDataManager::Vanish(){
  if(fInstance != 0){
    delete fInstance;
    fInstance = 0;
  }
}

//-------------------------------------------------------------------
DmpSimDataManager::DmpSimDataManager()
 :fTree(0),
  fPrimaryParticle(0)
{
  fTree = new TTree("Simulation","Simulation");
  fPrimaryParticle = new DmpEvtSimPrimaryParticle();
}

DmpSimDataManager::~DmpSimDataManager(){
  delete fTree;     // need??
  delete fPrimaryParticle;
}

//-------------------------------------------------------------------
void DmpSimDataManager::BookFile(const G4Run *aRun){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
  fTree->Branch("PrimaryParticle","DmpEvtSimPrimaryParticle",&fPrimaryParticle,32000,2);
  fTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
  fEvtRaw->GetEventHeader()->SetRunID(aRun->GetRunID());
// *
// *  TODO: set RunMode in EventHeader
// *
}

void DmpSimDataManager::SaveFile(){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
  char name[100];{
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
// *  TODO:  how to save file at where execute dmpSim?
  strftime(name,99,"DmpSim_%Y%m%d%H%M%S.root",p);
  }
  TFile *aFile = new TFile(name,"recreate");
  fTree->Write();
  aFile->Close();
  delete aFile;
}

void DmpSimDataManager::UpdatePrimaryParticleInformation(const G4Event *anEvent){
// *
// *  TODO: Use DataManager to save informations of parimary particle
// *
//  fPrimaryParticle->SetXXX();
}

void DmpSimDataManager::UpdateEventHeader(const G4Event *anEvent){
  fEvtRaw->GetEventHeader()->SetEventID(anEvent->GetEventID());
  int pdgCode = anEvent->GetPrimaryVertex()->GetPrimary()->GetPDGcode();
  fEvtRaw->GetEventHeader()->SetParticlePdgCode(pdgCode);
}

void DmpSimDataManager::Digitize(){
// *
// *  TODO: call this function before FillEvent() 
// *
/* old digitize, were in EndOfEventAction()
  G4DigiManager *fDM = G4DigiManager::GetDMpointer();
  G4HCofThisEvent* HCE = anEvent->GetHCofThisEvent();
  DmpSimStkHitsCollection *THC = 0;
  if(HCE){
    THC = (DmpSimStkHitsCollection*)(HCE->GetHC(stkHitCollID));
    //if (THC){
	//int n_hit = THC->entries();
	//G4cout <<G4endl;
	//G4cout << "Number of tracker hits in this event =  " << n_hit << G4endl;
	//}
    DmpSimDigitization * myDM = (DmpSimDigitization*)fDM->FindDigitizerModule( "DmpSimDigitization" );
    myDM->Digitize();
  }
  */
}

void DmpSimDataManager::FillEvent(){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
  fTree->Fill();
}

