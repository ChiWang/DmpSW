/*
 *  $Id: DmpSimDataManager.cc, 2014-03-06 16:27:45 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include "TTree.h"

#include "G4Run.hh"
#include "G4Event.hh"

#include "DmpEvtSimPrimaryParticle.h"
#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"
#include "DmpSimDataManager.h"

//-------------------------------------------------------------------
void DmpSimDataManager::Initialize(){
// *
// *  TODO:  for primary particle
// *
  //fPrimaryParticle->Reset();
  fEvtRaw->GetEventHeader()->Initialize();
}

//-------------------------------------------------------------------
void DmpSimDataManager::BookBranch(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif

  fOutDataTree = new TTree("DAMPE_Raw","Simulation");
  fOutDataTree->Branch("PrimaryParticle","DmpEvtSimPrimaryParticle",&fPrimaryParticle,32000,2);
  fOutDataTree->Branch("RawEvent","DmpEventRaw",&fEvtRaw,32000,2);
}

//-------------------------------------------------------------------
DmpSimDataManager::DmpSimDataManager()
 :fPrimaryParticle(0),
  fEvtRaw(0)
{
  fPrimaryParticle = new DmpEvtSimPrimaryParticle();
  fEvtRaw = new DmpEventRaw();
  fPgkID += "Sim_V1.0_";
}

//-------------------------------------------------------------------
DmpSimDataManager::~DmpSimDataManager(){
  delete fPrimaryParticle;
  delete fEvtRaw;
}

//-------------------------------------------------------------------
void DmpSimDataManager::UpdatePrimaryParticleInformation(const G4Event *anEvent){
// *
// *  TODO: Use DataManager to save informations of parimary particle
// *
//  fPrimaryParticle->SetXXX();
}

//-------------------------------------------------------------------
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

//-------------------------------------------------------------------
DmpSimDataManager *gDataMgr = DmpSimDataManager::GetInstance();

