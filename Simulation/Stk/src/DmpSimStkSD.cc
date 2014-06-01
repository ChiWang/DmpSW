/*
 *  $Id: DmpSimStkSD.cc, 2014-05-25 09:29:41 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/05/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimStkSD.h"
#include "DmpEvtMCStkMSD.h"
#include "DmpIOSvc.h"

//-------------------------------------------------------------------
DmpSimStkSD::DmpSimStkSD()
 :G4VSensitiveDetector("StkSD"),
  fLadderSet(0)
{
  fLadderSet = new TClonesArray("DmpEvtMCStkMSD",300);
  DmpIOSvc::GetInstance()->AddBranch("MCTruth/Stk",fLadderSet);
}

//-------------------------------------------------------------------
DmpSimStkSD::~DmpSimStkSD(){
  fLadderSet->Delete();
  fLadderSet->Clear();
  delete fLadderSet;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimStkSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string barName = theTouchable->GetVolume(1)->GetName();
  barName.assign(barName.end()-4,barName.end());        // get ID
  int barID = boost::lexical_cast<int>(barName);
  DmpEvtMCStkMSD *aBar = 0;
  for(int i=0;i<fLadderSet->GetEntriesFast();++i){
    if(((DmpEvtMCStkMSD*)fLadderSet->At(i))->GetSDID() == barID){
      aBar = (DmpEvtMCStkMSD*)fLadderSet->At(i);
      break;
    }
  }
  if(aBar == 0){
    LogDebug<<"\thit a new bar: "<<barID<<std::endl;
    aBar = (DmpEvtMCStkMSD*)fLadderSet->New(fLadderSet->GetEntriesFast());
    aBar->SetSDID(barID);
  }
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aBar->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,position.x()/mm,position.y()/mm,position.z()/mm);
  return true;
}

//-------------------------------------------------------------------
void DmpSimStkSD::Initialize(G4HCofThisEvent*){
// *
// *  TODO:  after DmpIOSvc filled this event?
// *
  fLadderSet->Delete();
  fLadderSet->Clear();
}

//-------------------------------------------------------------------
void DmpSimStkSD::EndOfEvent(G4HCofThisEvent* HCE){
}


