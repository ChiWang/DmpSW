// Description: This class hinerits from G4VSensitiveDetector. It is used to
// build the PSD sensitive area geometry and produce DmpSimPsdHit collection
//
// Author(s):
//  - added by Tiekuang Dong 2012/12/23

#include "DmpNudSensitiveDetector.h"
#include "DmpSimNudHit.h"
#include "DmpDetectorConstruction.h"

#include "G4RunManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

DmpNudSensitiveDetector::DmpNudSensitiveDetector(G4String name)
:G4VSensitiveDetector(name)
{
  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());
  
 // NbOfNUDStrips      =  (dmpDetector->GetNudDetectorDescription())->GetNbOfNUDStrips(); 

 // HitID = new G4int[NbOfNUDStrips];
 // collectionName.insert("NUDHitCollection");

  NbOfNUDTimeIntervals=150;
  TimeInterval=100.;  // in ns 

  HitID0 = new G4int[NbOfNUDTimeIntervals];
  HitID1 = new G4int[NbOfNUDTimeIntervals];
  HitID2 = new G4int[NbOfNUDTimeIntervals];
  HitID3 = new G4int[NbOfNUDTimeIntervals];

 collectionName.insert("NUDHitCollection0");
 collectionName.insert("NUDHitCollection1");
 collectionName.insert("NUDHitCollection2");
 collectionName.insert("NUDHitCollection3"); 

 //EdepTime[NbOfNUDTimeIntervals]; 
}

DmpNudSensitiveDetector::~DmpNudSensitiveDetector()
{
 // delete [] HitID;

delete [] HitID0;
delete [] HitID1;
delete [] HitID2;
delete [] HitID3;
}

void DmpNudSensitiveDetector::Initialize(G4HCofThisEvent*)
{
 // NUDHitCollection = new DmpSimNudHitsCollection
  //  (SensitiveDetectorName,collectionName[0]);
 

 NUDHitCollection0 = new DmpSimNudHitsCollection
    (SensitiveDetectorName,collectionName[0]);
  
 NUDHitCollection1 = new DmpSimNudHitsCollection
    (SensitiveDetectorName,collectionName[1]);

 NUDHitCollection2 = new DmpSimNudHitsCollection
    (SensitiveDetectorName,collectionName[2]);
 NUDHitCollection3 = new DmpSimNudHitsCollection
    (SensitiveDetectorName,collectionName[3]);



/* 
 for (G4int j=0;j<NbOfNUDStrips;j++) 
    {
           HitID[j] = -1;
    };
*/

for (G4int j=0;j<NbOfNUDTimeIntervals;j++) 
    {
       HitID0[j] = -1;
       HitID1[j] = -1;
       HitID2[j] = -1;
       HitID3[j] = -1;
    };

}

G4bool DmpNudSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{ 
  
  
  //G4cout<< "NUD ProcessHits can be run " << G4endl; 
  G4double StepTime=aStep->GetTrack()->GetGlobalTime();
  G4double edep = aStep->GetTotalEnergyDeposit();
  if ((edep/keV == 0.)) return false;      
  G4double TimeDown,TimeUp;  
  for (G4int i=0;i<NbOfNUDTimeIntervals;i++) {
    TimeDown=i*TimeInterval;
    TimeUp=(i+1)*TimeInterval; 


   if (StepTime>TimeDown&&StepTime<=TimeUp)   { 
  // This TouchableHistory is used to obtain the physical volume
  // of the hit
   EdepTime[i]=edep;
 
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* nud_phy = theTouchable->GetVolume();  
  G4LogicalVolume* nud_log=nud_phy->GetLogicalVolume();
 // G4int StripNumber=acd_tile->GetCopyNo();
  G4String NUDName = nud_log->GetName();


if (NUDName == "NUD0")
    {
      // This is a new hit
      if (HitID0[i]==-1)
	{       
	  DmpSimNudHit* PSSDHit = new DmpSimNudHit;
          PSSDHit->AddEnergy(EdepTime[i]);
	  PSSDHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
          PSSDHit->SetTime((i+1)*100.);   
	  HitID0[i] = 
	    NUDHitCollection0->insert(PSSDHit) -1;
	}
      else // This is not new
	{
	  (*NUDHitCollection0)
               [HitID0[i]]->AddEnergy(EdepTime[i]);
   
	}
    }

else if (NUDName == "NUD1" )
    {
 

     // This is a new hit
      if (HitID1[i]==-1)
	{       
	  DmpSimNudHit* PSSDHit = new DmpSimNudHit;
          PSSDHit->AddEnergy(EdepTime[i]);
	  PSSDHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
          PSSDHit->SetTime((i+1)*100.);   
	  HitID1[i] = 
	    NUDHitCollection1->insert(PSSDHit) -1;
	}
      else // This is not new
	{
	  (*NUDHitCollection1)
               [HitID1[i]]->AddEnergy(EdepTime[i]);
       
	}
    }


else if (NUDName == "NUD2")
    {
      // This is a new hit
      if (HitID2[i]==-1)
	{       
	  DmpSimNudHit* PSSDHit = new DmpSimNudHit;
          PSSDHit->AddEnergy(EdepTime[i]);
	  PSSDHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
        PSSDHit->SetTime((i+1)*100.);   
	  HitID2[i] = 
	    NUDHitCollection2->insert(PSSDHit) -1;
	}
      else // This is not new
	{
	  (*NUDHitCollection2)
               [HitID2[i]]->AddEnergy(EdepTime[i]);
  
	}
    }

else if (NUDName == "NUD3")
    {

     // This is a new hit
      if (HitID3[i]==-1)
	{       
	  DmpSimNudHit* PSSDHit = new DmpSimNudHit;
          PSSDHit->AddEnergy(EdepTime[i]);
	  PSSDHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
         PSSDHit->SetTime((i+1)*100.);   
	  HitID3[i] = 
	    NUDHitCollection3->insert(PSSDHit) -1;
 
	}
      else // This is not new
	  {
	  (*NUDHitCollection3)
               [HitID3[i]]->AddEnergy(EdepTime[i]);
    
	  }
      } // end of for (G4int i=0;i<NbOfNUDTimeIntervals;i++) 
   }  //end of if (StepTime>TimeDown&&StepTime<=TimeUp) 
} 
  return true;
}

void DmpNudSensitiveDetector::EndOfEvent(G4HCofThisEvent* HCE)
{
static G4int HCID0 = -1;
static G4int HCID1 = -1;
static G4int HCID2 = -1;
static G4int HCID3 = -1;

  if(HCID0<0)
    { 
      HCID0 = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }


  if(HCID1<0)
    { 
      HCID1 = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[1]);
    }

  if(HCID2<0)
    { 
      HCID2 = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[2]);
    }

  if(HCID3<0)
    { 
      HCID3 = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[3]);
    }


 HCE->AddHitsCollection(HCID0,NUDHitCollection0);
 HCE->AddHitsCollection(HCID1,NUDHitCollection1);
 HCE->AddHitsCollection(HCID2,NUDHitCollection2);
 HCE->AddHitsCollection(HCID3,NUDHitCollection3);


 for (G4int j=0;j<NbOfNUDTimeIntervals;j++) 
    {
       HitID0[j] = -1;
       HitID1[j] = -1;
       HitID2[j] = -1;
       HitID3[j] = -1;
    };
}

void DmpNudSensitiveDetector::clear()
{} 

void DmpNudSensitiveDetector::DrawAll()
{} 

void DmpNudSensitiveDetector::PrintAll()
{} 















