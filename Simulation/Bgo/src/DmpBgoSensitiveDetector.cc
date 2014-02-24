// Description: This class hinerits from G4VSensitiveDetector. It is used to
// build the BGO sensitive area geometry and produce DmpSimuBgoHit collection 
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "G4RunManager.hh"
#include "DmpBgoSensitiveDetector.hh"
#include "DmpSimuBgoHit.hh"
#include "DmpDetectorConstruction.hh"
#include "DmpBgoDetectorDescription.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

DmpBgoSensitiveDetector::DmpBgoSensitiveDetector(G4String name):G4VSensitiveDetector(name)
{
 G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());
  
  NbOfCALLayerBars  = (dmpDetector->GetBgoDetectorDescription())->GetNbOfCALLayerBars();
  NbOfCALLayers  = (dmpDetector->GetBgoDetectorDescription())->GetNbOfCALLayers();

  G4cout <<  NbOfCALLayerBars << " bars " << G4endl;
  G4cout <<  NbOfCALLayers << " layers " << G4endl;
  
  NbOfCALChannels = NbOfCALLayerBars*NbOfCALLayers/2;
  G4cout << NbOfCALChannels << "Nb of cal channels" <<G4endl;
  
  ChitXID = new G4int[NbOfCALChannels];
  ChitYID = new G4int[NbOfCALChannels];
  collectionName.insert("BGOHitCollection");

  //m_attenuation = -0.001; //light attenuation per mm; default 0.1% per mm

  //average attenuation length is about 1.4m
  //so m_attenuation=-1/(1.4m)=-0.000714 per mm
  m_attenuation = -0.000714; 
  //(old)light attenuation per mm; default 0.06% per mm
}

DmpBgoSensitiveDetector::~DmpBgoSensitiveDetector()
{
  delete [] ChitXID;
  delete [] ChitYID;
}

void DmpBgoSensitiveDetector::Initialize(G4HCofThisEvent*)
{
  BGOHitCollection = new DmpSimuBgoHitsCollection
    (SensitiveDetectorName,collectionName[0]);
  for (G4int i=0;i<NbOfCALChannels;i++)
      {
	ChitXID[i] = -1;
	ChitYID[i] = -1;
      };
}

G4bool DmpBgoSensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{ 
 
 
  G4double     edep = aStep->GetTotalEnergyDeposit();
  G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();
  if ((edep/keV == 0.)) return false;      
  
  // This TouchableHistory is used to obtain the physical volume
  // of the hit
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* cal_bar = theTouchable->GetVolume(1);  

  G4int CALBarNumber = -1;
  G4int CALLayerNumber = -1;

  G4int CopyNo=cal_bar->GetCopyNo();
  CALBarNumber = CopyNo-((int)(CopyNo/100))*100;  //bar No: 0~21
  CALLayerNumber = (int)(CopyNo/100);             //layer No: 0~13
  
  G4int CALPlaneNumber = 0;    //Plane number is 0~6, to suit Xin's DmpSimuBgoHitNtupleMaker
  if(CALLayerNumber==0  || CALLayerNumber==1 ){CALPlaneNumber=6;}
  if(CALLayerNumber==2  || CALLayerNumber==3 ){CALPlaneNumber=5;}
  if(CALLayerNumber==4  || CALLayerNumber==5 ){CALPlaneNumber=4;}
  if(CALLayerNumber==6  || CALLayerNumber==7 ){CALPlaneNumber=3;}
  if(CALLayerNumber==8  || CALLayerNumber==9 ){CALPlaneNumber=2;}
  if(CALLayerNumber==10 || CALLayerNumber==11){CALPlaneNumber=1;}
  if(CALLayerNumber==12 || CALLayerNumber==13){CALPlaneNumber=0;}

  G4int NChannel = 0;
  
  //NChannel = CALPlaneNumber * NbOfCALLayerBars + CALBarNumber; 
  
  if (CALLayerNumber%2==0 )
    //even layers(0,2,4,6,8,10,12)
    // The hit is on an X BGO plane
    
    {
      NChannel = (CALLayerNumber/2) * NbOfCALLayerBars + CALBarNumber; 

      G4double dpos = 300. - pos.x(); //distance to the positive side PMT
      G4double dneg = 300. + pos.x();
      G4double fracPos = 0.5*exp(m_attenuation*dpos);
      G4double fracNeg = 0.5*exp(m_attenuation*dneg);
      // This is a new hit
      if (ChitXID[NChannel]==-1)
	{       
	  DmpSimuBgoHit* CalorimeterHit = new DmpSimuBgoHit;
	  CalorimeterHit->SetCALType(1);
	  CalorimeterHit->AddEnergy(edep);
	  CalorimeterHit->SetPos(pos);
	  CalorimeterHit->AddSumPosition(edep*pos.x());
	  CalorimeterHit->AddEnergyPos(fracPos*edep);
	  CalorimeterHit->AddEnergyNeg(fracNeg*edep);
	  CalorimeterHit->SetCALLayerNumber(CALLayerNumber);
	  CalorimeterHit->SetCALBarNumber(CALBarNumber);
          CalorimeterHit->SetCALPlaneNumber(CALPlaneNumber);
	  ChitXID[NChannel] = 
	  BGOHitCollection->insert(CalorimeterHit) -1;
	  //std::cout << " new x bar hit at " << pos << " energy tot/pos/neg " << edep << "/" << fracPos*edep << "/" << (1.-fracPos)*edep << std::endl;
          //G4cout << "[DmpBgoSensitiveDetector::ProcessHits]:hit bar at layer: " << CALLayerNumber << ", X plane: " << CALPlaneNumber << ", Bar: " << CALBarNumber << ", NChannel: " << NChannel << G4endl;
	}
          
      else // This is not new
	{
	  (*BGOHitCollection)
	    [ChitXID[NChannel]]->AddEnergy(edep);
	  (*BGOHitCollection)
	    [ChitXID[NChannel]]->AddSumPosition(edep*pos.x());
	  (*BGOHitCollection)
	    [ChitXID[NChannel]]->AddEnergyPos(fracPos*edep);
	  (*BGOHitCollection)
	    [ChitXID[NChannel]]->AddEnergyNeg(fracNeg*edep);
	  //std::cout << " old x bar hit at " << pos << " energy tot/pos/neg " << edep << "/" << fracPos*edep << "/" << (1.-fracPos)*edep << std::endl;
          //G4cout << "[DmpBgoSensitiveDetector::ProcessHits]:This is not new hit, at layer: " << CALLayerNumber << ", X plane: " << CALPlaneNumber << ", Bar: " << CALBarNumber << ", NChannel: " << NChannel << G4endl;
	}
    }
 
  if (CALLayerNumber%2==1)
    //odd layers(1,3,5,7,9,11,13)
    // The hit is on an Y BGO plane    
    { 
      NChannel = (int(CALLayerNumber/2)) * NbOfCALLayerBars + CALBarNumber;
  
      G4double dpos = 300. - pos.y(); //distance to the positive side PMT
      G4double dneg = 300. + pos.y();
      G4double fracPos = 0.5*exp(m_attenuation*dpos);
      G4double fracNeg = 0.5*exp(m_attenuation*dneg);
      // This is a new hit
      if (ChitYID[NChannel]==-1)
	{       
	  DmpSimuBgoHit* CalorimeterHit 
	    = new DmpSimuBgoHit;
	  CalorimeterHit->SetCALType(0);
	  CalorimeterHit->AddEnergy(edep);
	  CalorimeterHit->SetPos(pos);
	  CalorimeterHit->AddSumPosition(edep*pos.y());
	  CalorimeterHit->AddEnergyPos(fracPos*edep);
	  CalorimeterHit->AddEnergyNeg(fracNeg*edep);
	  CalorimeterHit->SetCALLayerNumber(CALLayerNumber);
	  CalorimeterHit->SetCALBarNumber(CALBarNumber);
          CalorimeterHit->SetCALPlaneNumber(CALPlaneNumber);
	  ChitYID[NChannel] = 
	    BGOHitCollection->insert(CalorimeterHit)-1;
	  //std::cout << " new y bar hit at " << pos << " energy tot/pos/neg " << edep << "/" << fracPos*edep << "/" << (1.-fracPos)*edep << std::endl;
          //G4cout << "[DmpBgoSensitiveDetector::ProcessHits]:hit bar at layer: " << CALLayerNumber << ", Y plane: " << CALPlaneNumber << ", Bar: "<< CALBarNumber << ", NChannel: " << NChannel << G4endl;
	}
      else // This is not new
	{
	  (*BGOHitCollection)
	    [ChitYID[NChannel]]->AddEnergy(edep);
	  (*BGOHitCollection)
	    [ChitYID[NChannel]]->AddSumPosition(edep*pos.y());
	  (*BGOHitCollection)
	    [ChitYID[NChannel]]->AddEnergyPos(fracPos*edep);
	  (*BGOHitCollection)
	    [ChitYID[NChannel]]->AddEnergyNeg(fracNeg*edep);
	  //std::cout << " old y bar hit at " << pos << " energy tot/pos/neg " << edep << "/" << fracPos*edep << "/" << (1.-fracPos)*edep << std::endl;
          //G4cout << "[DmpBgoSensitiveDetector::ProcessHits]:This is not new hit, at layer: " << CALLayerNumber << ", Y plane: " << CALPlaneNumber << ", Bar: " << CALBarNumber << ", NChannel: " << NChannel << G4endl;
	}
    }


  return true;
}

void DmpBgoSensitiveDetector::EndOfEvent(G4HCofThisEvent* HCE)
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


void DmpBgoSensitiveDetector::clear()
{} 

void DmpBgoSensitiveDetector::DrawAll()
{} 

void DmpBgoSensitiveDetector::PrintAll()
{} 














