// Description: This class hinerits from G4VSensitiveDetector. It is used to
// build the BGO sensitive area geometry and produce DmpSimHitBgo collection 
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "G4RunManager.hh"
#include "DmpSimSensitiveDetectorBgo.hh"
#include "DmpSimHitBgo.hh"
#include "DmpDetectorConstruction.hh"
#include "DmpSimDetectorDescriptionBgo.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

DmpSimSensitiveDetectorBgo::DmpSimSensitiveDetectorBgo(G4String name):G4VSensitiveDetector(name)
{
 G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());
  
  NbOfCALBars    = (dmpDetector->GetSimDetectorDescriptionBgo())->GetNbOfCALBars();
  NbOfCALLayers  = (dmpDetector->GetSimDetectorDescriptionBgo())->GetNbOfCALLayers();

  G4cout <<  NbOfCALBars << " bars " << G4endl;
  G4cout <<  NbOfCALLayers << " layers " << G4endl;
  
  NbOfCALChannels = NbOfCALBars*NbOfCALLayers;
  
  ChitXID = new G4int[NbOfCALChannels];
  ChitYID = new G4int[NbOfCALChannels];
  collectionName.insert("BGOHitCollection");
}

DmpSimSensitiveDetectorBgo::~DmpSimSensitiveDetectorBgo()
{
  delete [] ChitXID;
  delete [] ChitYID;
}

void DmpSimSensitiveDetectorBgo::Initialize(G4HCofThisEvent*)
{
  BGOHitCollection = new DmpSimHitBgosCollection
    (SensitiveDetectorName,collectionName[0]);
  for (G4int i=0;i<NbOfCALChannels;i++)
      {
	ChitXID[i] = -1;
	ChitYID[i] = -1;
      };
}

G4bool DmpSimSensitiveDetectorBgo::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{ 
  
  G4double edep = aStep->GetTotalEnergyDeposit();
  if ((edep/keV == 0.)) return false;      
  
  // This TouchableHistory is used to obtain the physical volume
  // of the hit
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* cal_bar = theTouchable->GetVolume();  
  G4VPhysicalVolume* cal_plane = theTouchable->GetVolume(1);

  G4int CALBarNumber=cal_bar->GetCopyNo();
  G4String CALBarName = cal_bar->GetName();
  
  G4int PlaneNumber = 0;
  PlaneNumber=cal_plane->GetCopyNo();
  G4String PlaneName = cal_plane->GetName();


  G4int NChannel = 0;
  
  NChannel = PlaneNumber * NbOfCALBars + CALBarNumber; 
  
  if (PlaneName == "BGOLayerX" )
    
    // The hit is on an X CsI plane
    
    {
      // This is a new hit
      if (ChitXID[NChannel]==-1)
	{       
	  DmpSimHitBgo* CalorimeterHit = new DmpSimHitBgo;
	  CalorimeterHit->SetCALType(1);
	  CalorimeterHit->AddEnergy(edep);
	  CalorimeterHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	  CalorimeterHit->SetCALPlaneNumber(PlaneNumber);
	  CalorimeterHit->SetCALBarNumber(CALBarNumber);
	  ChitXID[NChannel] = 
	    BGOHitCollection->insert(CalorimeterHit) -1;
	}
      else // This is not new
	{
	  (*BGOHitCollection)
	    [ChitXID[NChannel]]->AddEnergy(edep);
	}
    }
 
  if (PlaneName == "BGOLayerY")
    // The hit is on an Y CsI plane    
    {   
      // This is a new hit
      if (ChitYID[NChannel]==-1)
	{       
	  DmpSimHitBgo* CalorimeterHit 
	    = new DmpSimHitBgo;
	  CalorimeterHit->SetCALType(0);
	  CalorimeterHit->AddEnergy(edep);
	  CalorimeterHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	  CalorimeterHit->SetCALPlaneNumber(PlaneNumber);
	  CalorimeterHit->SetCALBarNumber(CALBarNumber);
	  ChitYID[NChannel] = 
	    BGOHitCollection->insert(CalorimeterHit)-1;
	}
      else // This is not new
	{
	  (*BGOHitCollection)
	    [ChitYID[NChannel]]->AddEnergy(edep);
	}
    }
  
  return true;
}

void DmpSimSensitiveDetectorBgo::EndOfEvent(G4HCofThisEvent* HCE)
{
  static G4int HCID = -1;
  if(HCID<0)
    { 
      HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
  HCE->AddHitsCollection(HCID,BGOHitCollection);


  for (G4int i=0;i<NbOfCALChannels;i++) 
    {
      ChitXID[i] = -1;
      ChitYID[i] = -1;
    };
}


void DmpSimSensitiveDetectorBgo::clear()
{} 

void DmpSimSensitiveDetectorBgo::DrawAll()
{} 

void DmpSimSensitiveDetectorBgo::PrintAll()
{} 














