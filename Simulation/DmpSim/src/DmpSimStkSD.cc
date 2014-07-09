/*
 *  $Id: DmpSimStkSD.cc, 2014-06-05 21:46:27 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/05/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimStkSD.h"
#include "DmpEvtMCStkMSD.h"
#include "DmpRootIOSvc.h"

//-------------------------------------------------------------------
DmpSimStkSD::DmpSimStkSD()
 :G4VSensitiveDetector("StkSD"),
  fStripSet(0)
{
  fStripSet = new TClonesArray("DmpEvtMCStkMSD",74000); // strips number = layer(6) * block(4) * ladder(4) * strip(384*2)
// *
// *  TODO:  check Register status
// *
  DmpRootIOSvc::GetInstance()->RegisterObject("Event/MCTruth/Stk",fStripSet);
}

//-------------------------------------------------------------------
DmpSimStkSD::~DmpSimStkSD(){
  fStripSet->Delete();
  delete fStripSet;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimStkSD::ProcessHits(G4Step *aStep,G4TouchableHistory*){
// *
// *  TODO: 
// *
  G4TouchableHistory *theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  std::string stripName = theTouchable->GetVolume(1)->GetName();
  stripName.assign(stripName.end()-4,stripName.end());        // get ID
  int stripID = boost::lexical_cast<int>(stripName);
  DmpEvtMCStkMSD *aStrip = 0;
  for(int i=0;i<fStripSet->GetEntriesFast();++i){
    if(((DmpEvtMCStkMSD*)fStripSet->At(i))->GetSDID() == stripID){
      aStrip = (DmpEvtMCStkMSD*)fStripSet->At(i);
      break;
    }
  }
  if(aStrip == 0){
    DmpLogDebug<<"\t[Stk] hit a new strip: "<<stripID<<DmpLogEndl;
    aStrip = (DmpEvtMCStkMSD*)fStripSet->New(fStripSet->GetEntriesFast());
    aStrip->SetSDID(stripID);
  }
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aStrip->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,position.x()/mm,position.y()/mm,position.z()/mm);
  if(aStep->GetPreStepPoint()->GetMomentumDirection().z() < 0){
    aStrip->SetBackTrack(aStep->GetTrack()->GetTrackID(),aStep->GetTotalEnergyDeposit()/MeV);
  }
  return true;
}

//-------------------------------------------------------------------
void DmpSimStkSD::Initialize(G4HCofThisEvent*){
  fStripSet->Delete();
}

//-------------------------------------------------------------------
void DmpSimStkSD::EndOfEvent(G4HCofThisEvent* HCE){
}


