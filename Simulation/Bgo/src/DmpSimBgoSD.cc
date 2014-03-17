/*
 *  $Id: DmpSimBgoSD.cc, 2014-03-04 22:43:18 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimBgoSD.h"
#include "DmpEventRaw.h"
#include "DmpEvtBgoHit.h"
#include "DmpSimDataManager.h"

DmpSimBgoSD::DmpSimBgoSD(G4String name)
 :G4VSensitiveDetector(name)
{
  fHitCollection = DmpSimDataManager::GetInstance()->GetRawEvent()->GetHitCollectionBgo();
}

DmpSimBgoSD::~DmpSimBgoSD(){
}

void DmpSimBgoSD::Initialize(G4HCofThisEvent*){
// *
// *  TODO: check right? delete elements in TClonesArray of Bgo Hits
// *
  fHitCollection->Delete();
  fHitCollection->Clear(); // delete all Hits in collection
}

G4bool DmpSimBgoSD::ProcessHits(G4Step *aStep,G4TouchableHistory *ROHist){
// *  TODO: check barID is right?
#pragma message("TODO ----> check barID is right?")
  int barID = 333;//(ROHist->GetVolume(1)->GetCopyNo())*100 + ROHist->GetVolume(0)->GetCopyNo();
  int index = -1;
  for(int i=0;i<fHitCollection->GetEntriesFast();++i){
    if(((DmpEvtBgoHit*)fHitCollection->At(i))->GetSDID() == barID){
      index = i;
    }
  }
  DmpEvtBgoHit *aHit = 0;
  if(index < 0){
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"add new hit barID = "<<barID<<std::endl;
    index = fHitCollection->GetEntriesFast();
    aHit = (DmpEvtBgoHit*)fHitCollection->ConstructedAt(index);
    aHit->SetSDID(barID);
  }else{
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"old hit barID = "<<barID<<std::endl;
    aHit = (DmpEvtBgoHit*)fHitCollection->At(index);
  }
// *  TODO: use real data from G4Step
  double e = aStep->GetTotalEnergyDeposit()/MeV;    // use MeV
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aHit->AppendThisHit(e,position.x()/cm,position.y()/cm,position.z()/cm);
}

void DmpSimBgoSD::EndOfEvent(G4HCofThisEvent* HCE){
}


