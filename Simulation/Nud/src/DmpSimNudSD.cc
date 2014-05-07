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
  std::string blockName = theTouchable->GetVolume()->GetName();
  blockName.assign(blockName.end()-4,blockName.end());        // get ID
  short blockID = boost::lexical_cast<short>(blockName);
  int index = -1;
  for(int i=0;i<fMSDSet->GetEntriesFast();++i){
    if(((DmpEvtMCNudMSD*)fMSDSet->At(i))->GetSDID() == blockID){
      index = i;
      break;
    }
  }
  static DmpEvtMCNudMSD *aMSD = 0;
  if(index < 0){
    if(gCore->PrintDebug()){
      std::cout<<"DEBUG: "<<__PRETTY_FUNCTION__<<"\tnew block has hits = "<<blockID<<std::endl;
    }
    aMSD = (DmpEvtMCNudMSD*)fMSDSet->New(fMSDSet->GetEntriesFast());
    aMSD->SetSDID(blockID);
  }else{
    aMSD = (DmpEvtMCNudMSD*)fMSDSet->At(index);
  }
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aMSD->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,position.x()/cm,position.y()/cm,position.z()/cm);
  if(aMSD->GetStartTime()){
    aMSD->SetStopTime(aStep->GetPreStepPoint()->GetGlobalTime());
  }else{
    aMSD->SetStartTime(aStep->GetPreStepPoint()->GetGlobalTime());
  }
}

//-------------------------------------------------------------------
void DmpSimNudSD::EndOfEvent(G4HCofThisEvent* HCE){
}


