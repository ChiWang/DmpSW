/*
 *  $Id: DmpSimNudSD.cc, 2014-05-22 17:37:48 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimNudSD.h"
#include "DmpEvtMCNudBlock.h"
#include "DmpRootIOSvc.h"
#include "DmpDataBufSvc.h"

//-------------------------------------------------------------------
DmpSimNudSD::DmpSimNudSD()
 :G4VSensitiveDetector("NudSD"),
  fBlockSet(0)
{
  fBlockSet = new TClonesArray("DmpEvtMCNudBlock",4);
// *
// *  TODO:  check Register status
// *
  gDataBufSvc->RegisterObject("Event/MCTruth/Nud",fBlockSet);
}

//-------------------------------------------------------------------
DmpSimNudSD::~DmpSimNudSD(){
  fBlockSet->Delete();
  delete fBlockSet;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimNudSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string blockName = theTouchable->GetVolume()->GetName();
  blockName.assign(blockName.end()-1,blockName.end());        // get ID
  short blockID = boost::lexical_cast<short>(blockName);
  DmpEvtMCNudBlock *aBlock = 0;
  for(short i=0;i<fBlockSet->GetEntriesFast();++i){
    if(((DmpEvtMCNudBlock*)fBlockSet->At(i))->GetGlobalBlockID() == blockID){
      aBlock = (DmpEvtMCNudBlock*)fBlockSet->At(i);
      break;
    }
  }
  if(aBlock == 0){
    DmpLogDebug<<"\thit a new block: "<<blockID<<DmpLogEndl;
    aBlock = (DmpEvtMCNudBlock*)fBlockSet->New(fBlockSet->GetEntriesFast());
    aBlock->SetGlobalBlockID(blockID);
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
}

//-------------------------------------------------------------------
void DmpSimNudSD::EndOfEvent(G4HCofThisEvent* HCE){
}


