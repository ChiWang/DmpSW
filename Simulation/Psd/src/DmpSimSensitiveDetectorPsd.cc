// Description: This class hinerits from G4VSensitiveDetector. It is used to
// build the PSD sensitive area geometry and produce DmpSimHitPsd collection
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "G4RunManager.hh"
#include "DmpSimSensitiveDetectorPsd.hh"
#include "DmpSimHitPsd.hh"
#include "DmpSimDetectorConstruction.hh"
#include "DmpSimDetectorDescriptionPsd.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

DmpSimSensitiveDetectorPsd::DmpSimSensitiveDetectorPsd(G4String name)
:G4VSensitiveDetector(name)
{
  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpSimDetectorConstruction*)(runManager->GetUserDetectorConstruction());
  
  NbOfPSDStrips      =  (dmpDetector->GetDetectorDescriptionPsd())->GetNbOfPSDStrips(); 

  HitID = new G4int[NbOfPSDStrips];
  collectionName.insert("PSDHitCollection");
}

DmpSimSensitiveDetectorPsd::~DmpSimSensitiveDetectorPsd()
{
  delete [] HitID;
}

void DmpSimSensitiveDetectorPsd::Initialize(G4HCofThisEvent*)
{
  PSDHitCollection = new DmpSimHitPsdsCollection
    (SensitiveDetectorName,collectionName[0]);
   
  for (G4int j=0;j<NbOfPSDStrips;j++) 
    {
      
      HitID[j] = -1;
    };
}

G4bool DmpSimSensitiveDetectorPsd::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{ 

  G4double edep = aStep->GetTotalEnergyDeposit();
  if ((edep/keV == 0.)) return false;      
  
  // This TouchableHistory is used to obtain the physical volume
  // of the hit
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* acd_tile = theTouchable->GetVolume();  

  G4int StripNumber=acd_tile->GetCopyNo();
  G4String PSDName = acd_tile->GetName();
  
  //G4cout << PSDTileName << " " << edep/keV << G4endl;

  if (PSDName == "PSD" )
    {
      // This is a new hit
      if (HitID[StripNumber]==-1)
	{       
	  DmpSimHitPsd* PSSDHit = new DmpSimHitPsd;
	  PSSDHit->AddEnergy(edep);
	  PSSDHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	  PSSDHit->SetStripNumber(StripNumber);
	  HitID[StripNumber] = 
	    PSDHitCollection->insert(PSSDHit) -1;
	}
      else // This is not new
	{
	  (*PSDHitCollection)
	    [HitID[StripNumber]]->AddEnergy(edep);
	}
    }
 
  return true;
}

void DmpSimSensitiveDetectorPsd::EndOfEvent(G4HCofThisEvent* HCE)
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

void DmpSimSensitiveDetectorPsd::clear()
{} 

void DmpSimSensitiveDetectorPsd::DrawAll()
{} 

void DmpSimSensitiveDetectorPsd::PrintAll()
{} 















