/*
 *  $Id: DmpSimBgoSD.cc, 2014-05-19 12:03:10 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimBgoSD.h"
#include "DmpEvtMCBgoMSD.h"
#include "DmpRootIOSvc.h"

//-------------------------------------------------------------------
DmpSimBgoSD::DmpSimBgoSD()
 :G4VSensitiveDetector("BgoSD"),
  fBarSet(0)
{
  fBarSet = new TClonesArray("DmpEvtMCBgoMSD",300);
  DmpRootIOSvc::GetInstance()->RegisterObject("Event/MCTruth/Bgo",fBarSet);
}

//-------------------------------------------------------------------
DmpSimBgoSD::~DmpSimBgoSD(){
  fBarSet->Delete();
  fBarSet->Clear();
  delete fBarSet;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimBgoSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string barName = theTouchable->GetVolume(1)->GetName();
  barName.assign(barName.end()-4,barName.end());        // get ID
  int barID = boost::lexical_cast<int>(barName);
  DmpEvtMCBgoMSD *aBar = 0;
  for(int i=0;i<fBarSet->GetEntriesFast();++i){
    if(((DmpEvtMCBgoMSD*)fBarSet->At(i))->GetSDID() == barID){
      aBar = (DmpEvtMCBgoMSD*)fBarSet->At(i);
      break;
    }
  }
  if(aBar == 0){
    DmpLogDebug<<"\thit a new bar: "<<barID<<DmpLogEndl;
    aBar = (DmpEvtMCBgoMSD*)fBarSet->New(fBarSet->GetEntriesFast());
    aBar->SetSDID(barID);
  }
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aBar->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,position.x()/mm,position.y()/mm,position.z()/mm);
  return true;
}

//-------------------------------------------------------------------
void DmpSimBgoSD::Initialize(G4HCofThisEvent*){
// *
// *  TODO:  after DmpRootIOSvc filled this event?
// *
  fBarSet->Delete();
  fBarSet->Clear();
}

//-------------------------------------------------------------------
void DmpSimBgoSD::EndOfEvent(G4HCofThisEvent* HCE){
}


