/*
 *  $Id: DmpSimBgoSD.cc, 2014-03-04 22:43:18 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "TClonesArray.h"

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
  int barID = (ROHist->GetVolume(1)->GetCopyNo())*100 + ROHist->GetVolume(0)->GetCopyNo();
  int index = -1;
  DmpEvtBgoHit *aHit = 0;
  for(int i=0;i<fHitCollection->GetEntriesFast();++i){
    if(((DmpEvtBgoHit*)fHitCollection->At(i))->GetUID() == barID){
      index = i;
    }
  }
  if(index < 0){
    index = fHitCollection->GetEntriesFast();
    aHit = (DmpEvtBgoHit*)fHitCollection->ConstructedAt(index);
  }else{
    aHit = (DmpEvtBgoHit*)fHitCollection->At(index);
  }
  double e = aStep->GetTotalEnergyDeposit()/MeV;    // use MeV
// *  TODO: using GetDeltaPosition(this is wrong) or GetPreStepPoint
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aHit->AppendThisHit(e,position.x()/cm,position.y()/cm,position.z()/cm);
}

void DmpSimBgoSD::EndOfEvent(G4HCofThisEvent* HCE){
}


