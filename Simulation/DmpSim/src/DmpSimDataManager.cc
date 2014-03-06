/*
 *  $Id: DmpSimDataManager.cc, 2014-03-04 10:41:09 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include <time.h>

#include "TFile.h"
#include "TTree.h"

#include "G4Run.hh"
#include "G4Event.hh"

#include "DmpSimDataManager.h"
#include "DmpEvtHeader.h"
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
  fEvtRaw(0),
  fPrimaryParticle(0)
{
  fTree = new TTree("Simulation","Simulation");
  fPrimaryParticle = new DmpEvtSimPrimaryParticle();
  fEvtRaw = new DmpEventRaw();
}

DmpSimDataManager::~DmpSimDataManager(){
  delete fTree;     // need??
  delete fPrimaryParticle;
  delete fEvtRaw;
}

//-------------------------------------------------------------------
void DmpSimDataManager::BookFile(const G4Run *aRun){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
  fTree->Branch("EventSource","DmpEvtSimPrimaryParticle",&fPrimaryParticle,32000,2);
  fTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
  fEvtRaw->fEvtHeader->SetRunID(aRun->GetRunID());
// *
// *  TODO: set RunMode in fEvtHeader
// *
}

void DmpSimDataManager::SaveFile(){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
  char name[100];
  {
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  strftime(name,99,"./DmpSim_%Y%m%d%H%M%S.root",p);
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
  fEvtRaw->fEvtHeader->SetEventID(anEvent->GetEventID());
  int pdgCode = anEvent->GetPrimaryVertex()->GetPrimary()->GetPDGcode();
  fEvtRaw->fEvtHeader->SetParticlePdgCode(pdgCode);
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

DmpEvtHeader* DmpSimDataManager::GetEventHeader() const{
  return fEvtRaw->fEvtHeader;
}

TClonesArray* DmpSimDataManager::GetHitCollection(DmpParameters::DmpSubDetectors id) const{
  TClonesArray  *subDet=0;
 //*  TODO:  add hits in EvtRaw
  if(id == DmpParameters::kPsd){
    //subDet = fEvtRaw->fPsdHits;
  }else if(id == DmpParameters::kStk){
    //subDet = fEvtRaw->fStkHits;
  }else if(id == DmpParameters::kBgo){
    subDet = fEvtRaw->fBgoHits;
  }else if(id == DmpParameters::kNud){
    //subDet = fEvtRaw->fNudHits;
  }
  return subDet;
}

