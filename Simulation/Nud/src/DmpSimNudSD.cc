/*
 *  $Id: DmpSimNudSD.cc, 2014-05-05 15:50:07 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimNudSD.h"
#include "DmpEvtMCNudMSD.h"
#include "DmpSimSvcDataMgr.h"
#include "DmpCore.h"

//-------------------------------------------------------------------
DmpSimNudSD::DmpSimNudSD(G4String name)
 :G4VSensitiveDetector(name)
{
}

//-------------------------------------------------------------------
DmpSimNudSD::~DmpSimNudSD(){
}

//-------------------------------------------------------------------
void DmpSimNudSD::Initialize(G4HCofThisEvent*){
  fMSDSet = ((DmpSimSvcDataMgr*)gCore->ServiceManager()->Get("Sim/DataMgr"))->GetOutCollection(DmpDetector::kNud);
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimNudSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
// *
// *  TODO:  check Gdml file of Nud,
// block ID ??
// *
  //static TClonesArray *fMSDSet = ((DmpSimSvcDataMgr*)gCore->ServiceManager()->Get("Sim/DataMgr"))->GetOutCollection(DmpDetector::kNud);
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string barName = theTouchable->GetVolume()->GetName();
  barName.assign(barName.end()-4,barName.end());        // get ID
  int barID = boost::lexical_cast<int>(barName);
  int index = -1;
  for(int i=0;i<fMSDSet->GetEntriesFast();++i){
    if(((DmpEvtMCNudMSD*)fMSDSet->At(i))->GetSDID() == barID){
      index = i;
      break;
    }
  }
  static DmpEvtMCNudMSD *aMSD = 0;
  if(index < 0){
    if(gCore->PrintDebug()){
      std::cout<<"DEBUG: "<<__PRETTY_FUNCTION__<<"\tnew bar has hits = "<<barID<<std::endl;
    }
    aMSD = (DmpEvtMCNudMSD*)fMSDSet->New(fMSDSet->GetEntriesFast());
    aMSD->SetSDID(barID);
  }else{
    aMSD = (DmpEvtMCNudMSD*)fMSDSet->At(index);
  }
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aMSD->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,position.x()/cm,position.y()/cm,position.z()/cm);
// *
// *  TODO:  add time:(first time and last time at here??)
// *
}

//-------------------------------------------------------------------
void DmpSimNudSD::EndOfEvent(G4HCofThisEvent* HCE){
}


