/*
 *  $Id: DmpSimPsdSD.cc, 2014-05-24 12:58:41 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/05/2014
*/

#include "TClonesArray.h"

#include "G4Step.hh"
#include "G4TouchableHistory.hh"

#include "DmpSimPsdSD.h"
#include "DmpEvtMCPsdMSD.h"
#include "DmpIOSvc.h"

//-------------------------------------------------------------------
DmpSimPsdSD::DmpSimPsdSD()
 :G4VSensitiveDetector("PsdSD"),
  fStripSet(0)
{
  fStripSet = new TClonesArray("DmpEvtMCPsdMSD",90);
  DmpIOSvc::GetInstance()->AddBranch("MCTruth/Psd",fStripSet);
}

//-------------------------------------------------------------------
DmpSimPsdSD::~DmpSimPsdSD(){
  fStripSet->Delete();
  fStripSet->Clear();
  delete fStripSet;
}

//-------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
G4bool DmpSimPsdSD::ProcessHits(G4Step *aStep, G4TouchableHistory*){
  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
// *
// *  TODO:  GetVolume(level is right?)
// *
  std::string stripName = theTouchable->GetVolume(1)->GetName();
  stripName.assign(stripName.end()-3,stripName.end());        // get ID
  short stripID = boost::lexical_cast<short>(stripName);
  DmpEvtMCPsdMSD *aStrip = 0;
  for(short i=0;i<fStripSet->GetEntriesFast();++i){
    if(((DmpEvtMCPsdMSD*)fStripSet->At(i))->GetSDID() == stripID){
      aStrip = (DmpEvtMCPsdMSD*)fStripSet->At(i);
      break;
    }
  }
  if(aStrip == 0){
    DmpLogDebug<<"\thit a new strip: "<<stripID<<DmpLogEndl;
    aStrip = (DmpEvtMCPsdMSD*)fStripSet->New(fStripSet->GetEntriesFast());
    aStrip->SetSDID(stripID);
  }
  G4ThreeVector position = aStep->GetPreStepPoint()->GetPosition();
  aStrip->AddG4Hit(aStep->GetTotalEnergyDeposit()/MeV,position.x()/mm,position.y()/mm,position.z()/mm);
  if(aStep->GetPreStepPoint()->GetMomentum().z() < 0){
    aStrip->SetBackTrackID(aStep->GetTrack()->GetTrackID());
  }
  
  return true;
}

//-------------------------------------------------------------------
void DmpSimPsdSD::Initialize(G4HCofThisEvent*){
  fStripSet->Delete();
  fStripSet->Clear();
}

//-------------------------------------------------------------------
void DmpSimPsdSD::EndOfEvent(G4HCofThisEvent* HCE){
}











