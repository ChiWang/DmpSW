/*
 *  $Id: DmpSimSvcDataMgr.cc, 2014-04-10 21:08:38 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include "TTree.h"
#include "TClonesArray.h"

#include "G4Event.hh"

#include "DmpEvtMCPrimaryParticle.h"
#include "DmpEvtMCPsdMSD.h"
#include "DmpEvtMCStkMSD.h"
#include "DmpEvtMCBgoMSD.h"
#include "DmpEvtMCNudMSD.h"
#include "DmpSimSvcDataMgr.h"

//-------------------------------------------------------------------
DmpSimSvcDataMgr::DmpSimSvcDataMgr()
 :DmpVSvc("Sim/DataMgr"),
  fPrimaryParticle(0),
  fPsdOutSet(0),
  fStkOutSet(0),
  fBgoOutSet(0),
  fNudOutSet(0)
{
  SetPackageID("Sim_V1.0_");
  fPrimaryParticle = new DmpEvtMCPrimaryParticle();
  fPsdOutSet = new TClonesArray("DmpEvtMCPsdMSD",300);
  fStkOutSet = new TClonesArray("DmpEvtMCStkMSD",300);
  fBgoOutSet = new TClonesArray("DmpEvtMCBgoMSD",300);
  fNudOutSet = new TClonesArray("DmpEvtMCNudMSD",300);
}

//-------------------------------------------------------------------
DmpSimSvcDataMgr::~DmpSimSvcDataMgr(){
  delete fPrimaryParticle;
  fPsdOutSet->Delete(); fPsdOutSet->Clear(); delete fPsdOutSet;
  fStkOutSet->Delete(); fStkOutSet->Clear(); delete fStkOutSet;
  fBgoOutSet->Delete(); fBgoOutSet->Clear(); delete fBgoOutSet;
  fNudOutSet->Delete(); fNudOutSet->Clear(); delete fNudOutSet;
}

//-------------------------------------------------------------------
void DmpSimSvcDataMgr::Set(const std::string &type, const std::string &argv){
  if(type == "OutDataPath"){
    SetOutDataPath(argv);
  }else if(type == "OutDataNote"){
    AppendDataNote(argv);
  }else if(type == "InData"){
    SetInputData(argv);
  }
}

//-------------------------------------------------------------------
void DmpSimSvcDataMgr::BookBranch(){
// *
// *  TODO:  for primary particle
// *
  //fPrimaryParticle->Reset();
  fOutDataTree = new TTree("DAMPE_Raw","Simulation");
  fOutDataTree->Branch("PrimaryParticle","DmpEvtMCPrimaryParticle",&fPrimaryParticle,32000,2);
  fOutDataTree->Branch("Psd",fPsdOutSet,32000,2);
  fOutDataTree->Branch("Stk",fStkOutSet,32000,2);
  fOutDataTree->Branch("Bgo",fBgoOutSet,32000,2);
  fOutDataTree->Branch("Nud",fNudOutSet,32000,2);
}

//-------------------------------------------------------------------
TClonesArray* DmpSimSvcDataMgr::GetOutCollection(DmpDetector::DmpEDetectorID id) const{
  switch(id){
    case DmpDetector::kPsd:
      return fPsdOutSet;
    case DmpDetector::kStk:
      return fStkOutSet;
    case DmpDetector::kBgo:
      return fBgoOutSet;
    case DmpDetector::kNud:
      return fNudOutSet;
  }
}

//-------------------------------------------------------------------
void DmpSimSvcDataMgr::ResetEvent(){
  fPsdOutSet->Delete(); fPsdOutSet->Clear();
  fStkOutSet->Delete(); fStkOutSet->Clear();
  fBgoOutSet->Delete(); fBgoOutSet->Clear();
  fNudOutSet->Delete(); fNudOutSet->Clear();
}

//-------------------------------------------------------------------
void DmpSimSvcDataMgr::Digitize(){
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

