/*
 *  $Id: DmpSimBgoSD.cc, 2014-03-04 22:43:18 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimBgoSD.h"
#include "DmpEvtMCBgoMSD.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpCore.h"

//-------------------------------------------------------------------
DmpSimBgoSD::DmpSimBgoSD(G4String name)
 :G4VSensitiveDetector(name)
{
}

//-------------------------------------------------------------------
DmpSimBgoSD::~DmpSimBgoSD(){
}

//-------------------------------------------------------------------
void DmpSimBgoSD::Initialize(G4HCofThisEvent*){
  fMSDSet = ((DmpSimSvcDataMgr*)gCore->ServiceManager()->Get("Sim/DataMgr"))->GetOutCollection(DmpDetector::kBgo);
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimBgoSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string barName = theTouchable->GetVolume(1)->GetName();
  //std::cout<<"name = "<<barName<<std::endl;
  //return false;
  barName.assign(barName.end()-4,barName.end());        // get ID
  int barID = boost::lexical_cast<int>(barName);
  DmpEvtMCBgoMSD *aMSD = 0;
  for(int i=0;i<fMSDSet->GetEntriesFast();++i){
    if(((DmpEvtMCBgoMSD*)fMSDSet->At(i))->GetSDID() == barID){
      aMSD = (DmpEvtMCBgoMSD*)fMSDSet->At(i);
      break;
    }
  }
  if(aMSD == 0){
    if(gCore->PrintDebug()){
      std::cout<<"DEBUG: "<<__PRETTY_FUNCTION__<<"\thit a new bar: "<<barID<<std::endl;
    }
    aMSD = (DmpEvtMCBgoMSD*)fMSDSet->New(fMSDSet->GetEntriesFast());
    aMSD->SetSDID(barID);
  }
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aMSD->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,position.x()/mm,position.y()/mm,position.z()/mm);
  return true;
}

//-------------------------------------------------------------------
void DmpSimBgoSD::EndOfEvent(G4HCofThisEvent* HCE){
}


