/*
 *  $Id: DmpSimNudSD.cc, 2014-05-22 17:37:48 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimNudSD.h"
#include "DmpEvtMCNudMSD.h"
#include "DmpRootIOSvc.h"

//-------------------------------------------------------------------
DmpSimNudSD::DmpSimNudSD()
 :G4VSensitiveDetector("NudSD"),
  fBlockSet(0)
{
  fBlockSet = new TClonesArray("DmpEvtMCNudMSD",4);
  DmpRootIOSvc::GetInstance()->RegisterObject("MCTruth/Nud",fBlockSet);
}

//-------------------------------------------------------------------
DmpSimNudSD::~DmpSimNudSD(){
  fBlockSet->Delete();
  fBlockSet->Clear();
  delete fBlockSet;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimNudSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string blockName = theTouchable->GetVolume()->GetName();
  blockName.assign(blockName.end()-1,blockName.end());        // get ID
  short blockID = boost::lexical_cast<short>(blockName);
  DmpEvtMCNudMSD *aBlock = 0;
  for(short i=0;i<fBlockSet->GetEntriesFast();++i){
    if(((DmpEvtMCNudMSD*)fBlockSet->At(i))->GetSDID() == blockID){
      aBlock = (DmpEvtMCNudMSD*)fBlockSet->At(i);
      break;
    }
  }
  if(aBlock == 0){
    DmpLogDebug<<"\thit a new block: "<<blockID<<DmpLogEndl;
    aBlock = (DmpEvtMCNudMSD*)fBlockSet->New(fBlockSet->GetEntriesFast());
    aBlock->SetSDID(blockID);
  }
  aBlock->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,aStep->GetPreStepPoint()->GetGlobalTime()/ns);
  return true;
}

//-------------------------------------------------------------------
void DmpSimNudSD::Initialize(G4HCofThisEvent*){
// *
// *  TODO:  after DmpRootIOSvc filled this event?
// *
  fBlockSet->Delete();
  fBlockSet->Clear();
}

//-------------------------------------------------------------------
void DmpSimNudSD::EndOfEvent(G4HCofThisEvent* HCE){
}


