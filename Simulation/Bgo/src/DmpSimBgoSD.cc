/*
 *  $Id: DmpSimBgoSD.cc, 2014-03-04 22:43:18 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "TClonesArray.h"
#include "TRandom.h"    // test, not need indeed

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpEvtBgoHit.h"
#include "DmpSimBgoSD.h"
#include "DmpSimDataManager.h"

DmpSimBgoSD::DmpSimBgoSD(G4String name)
 :G4VSensitiveDetector(name)
{
  fHitCollection = DmpSimDataManager::GetInstance()->GetHitCollection(DmpParameters::kBgo);
}

DmpSimBgoSD::~DmpSimBgoSD(){
}

void DmpSimBgoSD::Initialize(G4HCofThisEvent*){
// *
// *  TODO: check right? delete elements in TClonesArray of Bgo Hits
// *
  fHitCollection->Clear(); // delete all Hits in collection
}

G4bool DmpSimBgoSD::ProcessHits(G4Step *aStep,G4TouchableHistory *ROHist){
// *  TODO: check barID is right?
#pragma message("TODO ----> check barID is right?")
  //int barID = (ROHist->GetVolume(1)->GetCopyNo())*100 + ROHist->GetVolume(0)->GetCopyNo();
  int barID;
  { barID = (int)gRandom->Uniform(13)*100 + (int)gRandom->Uniform(21);} // test
  int index = -1;
  DmpEvtBgoHit *aHit = 0;
  for(int i=0;i<fHitCollection->GetEntriesFast();++i){
    if(((DmpEvtBgoHit*)fHitCollection->At(i))->GetUID() == barID){
      index = i;
    }
  }
  if(index < 0){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"add new hit barID = "<<barID<<std::endl;
    index = fHitCollection->GetEntriesFast();
    aHit = (DmpEvtBgoHit*)fHitCollection->ConstructedAt(index);
    aHit->SetUID(barID);
  }else{
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"old hit barID = "<<barID<<std::endl;
    aHit = (DmpEvtBgoHit*)fHitCollection->At(index);
  }
// *  TODO: use real data from G4Step
  //double e = aStep->GetTotalEnergyDeposit()/MeV;    // use MeV
  //G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  //aHit->AppendThisHit(e,position.x()/cm,position.y()/cm,position.z()/cm);
  aHit->AppendThisHit(gRandom->Gaus(200,10),gRandom->Gaus(10,4),gRandom->Gaus(5,9),gRandom->Gaus(5,10));
}

void DmpSimBgoSD::EndOfEvent(G4HCofThisEvent* HCE){
}


