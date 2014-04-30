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
#include "DmpKernel.h"

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
  fMSDSet = ((DmpSimSvcDataMgr*)gKernel->ServiceManager()->Get("Sim/DataMgr"))->GetOutCollection(DmpDetector::kBgo);
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimBgoSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
  //static TClonesArray *fMSDSet = ((DmpSimSvcDataMgr*)gKernel->ServiceManager()->Get("Sim/DataMgr"))->GetOutCollection(DmpDetector::kBgo);
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string barName = theTouchable->GetVolume()->GetName();
  barName.assign(barName.end()-4,barName.end());        // get ID
  int barID = boost::lexical_cast<int>(barName);
  int index = -1;
  for(int i=0;i<fMSDSet->GetEntriesFast();++i){
    if(((DmpEvtMCBgoMSD*)fMSDSet->At(i))->GetSDID() == barID){
      index = i;
      break;
    }
  }
  static DmpEvtMCBgoMSD *aMSD = 0;
  if(index < 0){
    if(gKernel->OutDegubInfor()){
      std::cout<<"DEBUG: "<<__PRETTY_FUNCTION__<<"\tnew bar has hits = "<<barID<<std::endl;
    }
    aMSD = (DmpEvtMCBgoMSD*)fMSDSet->New(fMSDSet->GetEntriesFast());
    aMSD->SetSDID(barID);
  }else{
    aMSD = (DmpEvtMCBgoMSD*)fMSDSet->At(index);
  }
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aMSD->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,position.x()/cm,position.y()/cm,position.z()/cm);
}

//-------------------------------------------------------------------
void DmpSimBgoSD::EndOfEvent(G4HCofThisEvent* HCE){
}


