/*
 *  $Id: DmpSimBgoSD.cc, 2014-03-04 22:43:18 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifdef DmpDebug
//#include <iostream>
#endif

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
  fHitCollection = DmpSimDataManager::GetInstance()->GetRawEvent()->GetHitCollection(DmpDetector::kBgo);
}

DmpSimBgoSD::~DmpSimBgoSD(){
}

void DmpSimBgoSD::Initialize(G4HCofThisEvent*){
  fHitCollection->Delete();
  fHitCollection->Clear(); // delete all Hits in collection
}

#include <boost/lexical_cast.hpp>
G4bool DmpSimBgoSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
// *
// *  TODO: update the method to get barID
// *
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string barName = theTouchable->GetVolume()->GetName();
  barName.assign(barName.end()-4,barName.end());        // get ID
  int barID = boost::lexical_cast<int>(barName);
  //int barID = 333;
  //int barID = (theTouchable->GetVolume(1)->GetCopyNo())*100 + theTouchable->GetVolume()->GetCopyNo();
  int index = -1;
  for(int i=0;i<fHitCollection->GetEntriesFast();++i){
    if(((DmpEvtBgoHit*)fHitCollection->At(i))->GetSDID() == barID){
      index = i;
    }
  }
  DmpEvtBgoHit *aHit = 0;
  if(index < 0){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"\tnew bar has hits = "<<barID<<std::endl;
#endif
    index = fHitCollection->GetEntriesFast();
    aHit = (DmpEvtBgoHit*)fHitCollection->ConstructedAt(index);
    aHit->SetSDID(barID);
  }else{
    aHit = (DmpEvtBgoHit*)fHitCollection->At(index);
  }
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aHit->AddThisHit(aStep->GetTotalEnergyDeposit()/MeV,position.x()/cm,position.y()/cm,position.z()/cm);
}

void DmpSimBgoSD::EndOfEvent(G4HCofThisEvent* HCE){
}


