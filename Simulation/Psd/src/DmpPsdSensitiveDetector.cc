// Description: This class hinerits from G4VSensitiveDetector. It is used to
// build the PSD sensitive area geometry and produce DmpSimuPsdHit collection
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "G4RunManager.hh"
#include "DmpPsdSensitiveDetector.hh"
#include "DmpSimuPsdHit.hh"
#include "DmpDetectorConstruction.hh"
#include "DmpPsdDetectorDescription.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

DmpPsdSensitiveDetector::DmpPsdSensitiveDetector(G4String name)
:G4VSensitiveDetector(name)
{
  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());
  
  NbOfPSDStrips      =  (dmpDetector->GetPsdDetectorDescription())->GetNbOfPSDStrips();

  HitID = new G4int[NbOfPSDStrips];
  collectionName.insert("PSDHitCollection");
}

DmpPsdSensitiveDetector::~DmpPsdSensitiveDetector()
{
  delete [] HitID;
}

void DmpPsdSensitiveDetector::Initialize(G4HCofThisEvent*)
{
  PSDHitCollection = new DmpSimuPsdHitsCollection
    (SensitiveDetectorName,collectionName[0]);
   
  for (G4int j=0;j<NbOfPSDStrips;j++) 
  {
      
      HitID[j] = -1;
  }
}

G4bool DmpPsdSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{ 

  G4double edep = aStep->GetTotalEnergyDeposit();
  if ((edep/keV == 0.)) return false;      
  G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();
  bool is_backtrack= false;
  if(aStep->GetPreStepPoint()->GetMomentum().z()<0) is_backtrack= true;
  G4int trackID = aStep->GetTrack()->GetTrackID();
  
  // This TouchableHistory is used to obtain the physical volume
  // of the hit
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* psd_strip = theTouchable->GetVolume();

  G4int StripNumber=psd_strip->GetCopyNo();//copyNum 1-41 is Layer-Y,copyNum 42-82 is Layer-X
  G4String PSDName = psd_strip->GetName();
  
  //G4cout << PSDTileName << " " << edep/keV << G4endl;

  if (HitID[StripNumber-1]==-1){
    DmpSimuPsdHit* PSDHit = new DmpSimuPsdHit;
    PSDHit->AddEnergy(edep);
    PSDHit->SetStripNumber(StripNumber);
    PSDHit->SetPos(pos);
    PSDHit->SetNtracks(1);
    if(is_backtrack) PSDHit->SetNtracksBack(1);
    PSDHit->SetTrackID(trackID);
    if(StripNumber<42) { //Y-strip measuring X position
        PSDHit->AddSumPosition(edep*pos.x());
    }
    else { //X-strip measuring Y position
        PSDHit->AddSumPosition(edep*pos.y());
    }
    HitID[StripNumber-1] = PSDHitCollection->insert(PSDHit) -1;
  }
  else // This is not new
  {
      (*PSDHitCollection)[HitID[StripNumber-1]]->AddEnergy(edep);
      if(StripNumber<42) { //Y-strip
        (*PSDHitCollection)[HitID[StripNumber-1]]->AddSumPosition(edep*pos.x());
	  }
      else { //X-strip
        (*PSDHitCollection)[HitID[StripNumber-1]]->AddSumPosition(edep*pos.y());
	  }
      G4int oldID = (*PSDHitCollection)[HitID[StripNumber-1]]->GetTrackID();
	  if(oldID != trackID) {
        G4int oldN = (*PSDHitCollection) [HitID[StripNumber-1]] ->GetNtracks();
        (*PSDHitCollection) [HitID[StripNumber-1]]->SetNtracks(oldN + 1);
	    if(is_backtrack) {
          G4int oldNb = (*PSDHitCollection) [HitID[StripNumber-1]] ->GetNtracksBack();
          (*PSDHitCollection) [HitID[StripNumber-1]]->SetNtracksBack(oldNb + 1);
	    }
	  }
	}

 
  return true;
}

void DmpPsdSensitiveDetector::EndOfEvent(G4HCofThisEvent* HCE)
{
  static G4int HCID = -1;
  if(HCID<0)
    { 
      HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
  HCE->AddHitsCollection(HCID,PSDHitCollection);

  for (G4int j=0;j<NbOfPSDStrips;j++) 
    {
      HitID[j] = -1;
    };

}

void DmpPsdSensitiveDetector::clear()
{} 

void DmpPsdSensitiveDetector::DrawAll()
{} 

void DmpPsdSensitiveDetector::PrintAll()
{} 















