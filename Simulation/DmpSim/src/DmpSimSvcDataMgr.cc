/*
 *  $Id: DmpSimSvcDataMgr.cc, 2014-04-10 21:08:38 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include "TTree.h"
#include "TClonesArray.h"

#include "G4Event.hh"

#include "DmpEvtSimPrimaryParticle.h"
#include "DmpEvtHeader.h"
#include "DmpEvtPsdMSD.h"
#include "DmpEvtStkMSD.h"
#include "DmpEvtBgoMSD.h"
#include "DmpEvtNudMSD.h"
#include "DmpSimSvcDataMgr.h"

//-------------------------------------------------------------------
DmpSimSvcDataMgr::DmpSimSvcDataMgr()
 :DmpVSvcDataMgr("Sim/DataMgr"),
  fPrimaryParticle(0),
  fEvtHeader(0),
  fPsdOutSet(0),
  fStkOutSet(0),
  fBgoOutSet(0),
  fNudOutSet(0)
{
  SetPackageID("Sim_V1.0_");
  fPrimaryParticle = new DmpEvtSimPrimaryParticle();
  fEvtHeader = new DmpEvtHeader();
  fPsdOutSet = new TClonesArray("DmpEvtPsdMSD",300);
  fStkOutSet = new TClonesArray("DmpEvtStkMSD",300);
  fBgoOutSet = new TClonesArray("DmpEvtBgoMSD",300);
  fNudOutSet = new TClonesArray("DmpEvtNudMSD",300);
  std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
}

//-------------------------------------------------------------------
DmpSimSvcDataMgr::~DmpSimSvcDataMgr(){
  delete fPrimaryParticle;
  delete fEvtHeader;
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
  }
}

//-------------------------------------------------------------------
void DmpSimSvcDataMgr::BookBranch(){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<std::endl;
#endif
// *
// *  TODO:  for primary particle
// *
  //fPrimaryParticle->Reset();
  fEvtHeader->Initialize();
  fOutDataTree = new TTree("DAMPE_Raw","Simulation");
  fOutDataTree->Branch("PrimaryParticle","DmpEvtSimPrimaryParticle",&fPrimaryParticle,32000,2);
  fOutDataTree->Branch("EventHeader","DmpEvtHeader",&fEvtHeader,32000,2);
  fOutDataTree->Branch("Psd",fPsdOutSet,32000,2);
  fOutDataTree->Branch("Stk",fStkOutSet,32000,2);
  fOutDataTree->Branch("Bgo",fBgoOutSet,32000,2);
  fOutDataTree->Branch("Nud",fNudOutSet,32000,2);
}

//-------------------------------------------------------------------
TClonesArray* DmpSimSvcDataMgr::GetOutCollection(DmpDetector::DmpEDetectorID id) const{
  std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"Add = "<<fBgoOutSet<<std::endl;
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
void DmpSimSvcDataMgr::UpdatePrimaryParticleInformation(const G4Event *anEvent){
// *
// *  TODO: Use DataManager to save informations of parimary particle
// *
//  fPrimaryParticle->SetXXX();
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

