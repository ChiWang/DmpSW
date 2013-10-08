// Description: This class hinerits from G4VSensitiveDetector. It is used to
// build the STK sensitive area geometry and produce DmpSimuStkHit collection
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "G4RunManager.hh"
#include "DmpStkSensitiveDetector.hh"
#include "DmpStkROGeometry.hh"

#include "DmpSimuStkHit.hh"
#include "DmpDetectorConstruction.hh"
#include "DmpStkDetectorDescription.hh"
#include "DmpSimuPrimaryGeneratorAction.hh"

#include "G4VPhysicalVolume.hh"

#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

#include "G4ios.hh"

DmpStkSensitiveDetector::DmpStkSensitiveDetector(G4String name):G4VSensitiveDetector(name)
{
  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector = (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

  G4int NbOfTKRTiles  =  dmpDetector->GetStkDetectorDescription()->GetNbOfTKRTiles();
  G4int NbOfTKRBlocks =  dmpDetector->GetStkDetectorDescription()->GetNbOfTKRBlocks();
  NbOfTKRStrips  = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRStrips();
  NbOfTKRLayers  = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRLayers();  
  G4cout << "DmpStkSensitiveDetector::constructor called " << G4endl;

   G4cout <<  "  " << NbOfTKRTiles  << " tracker ladders " << G4endl;
  G4cout <<  "  " << NbOfTKRBlocks << " tracker blocks " << G4endl;
  G4cout <<  "  " << NbOfTKRLayers << " tracker layers " << G4endl;
  //G4cout <<  "  " << NbOfTKRStrips << " tracker strips per tile (ladder) " << G4endl;
  G4cout <<  "  " << NbOfTKRStrips << " tracker strips per ladder " << G4endl;

  NbOfTKRStrips = NbOfTKRStrips*NbOfTKRTiles*NbOfTKRBlocks;  
 
  G4cout <<  "  NbOfTKRStrips in DmpStkSensitiveDetector is the number of strips per layer : " << NbOfTKRStrips << G4endl;
  
  //NbOfTKRChannels = NbOfTKRStrips* NbOfTKRTiles * NbOfTKRLayers;
  //G4cout <<  "  total number of readout channels (why times NbOfTKRTiles again?): " << NbOfTKRChannels << G4endl;
  NbOfTKRChannels = NbOfTKRStrips * NbOfTKRLayers;
  G4cout <<  "  total number of readout channels per view : " << NbOfTKRChannels << G4endl;

  ThitXID = new G4int[NbOfTKRChannels];
  ThitYID = new G4int[NbOfTKRChannels];
  //set the collection name (in G4VSensitiveDetector)
  collectionName.insert("STKHitCollection");

}

DmpStkSensitiveDetector::~DmpStkSensitiveDetector()
{
  delete [] ThitXID;
  delete [] ThitYID;
}

void DmpStkSensitiveDetector::Initialize(G4HCofThisEvent*)
{
  TrackerCollection = new DmpSimuStkHitsCollection
    (SensitiveDetectorName,collectionName[0]);

 for (G4int i=0;i<NbOfTKRChannels;i++)
   {
     ThitXID[i] = -1;
     ThitYID[i] = -1;
   };

 G4RunManager* runManager = G4RunManager::GetRunManager();
 primaryGeneratorAction =
   (DmpSimuPrimaryGeneratorAction*)(runManager->GetUserPrimaryGeneratorAction());

 isPhotonRun = false;
 if(primaryGeneratorAction->GetParticleDefinition()->GetParticleName() == "gamma") isPhotonRun = true;

}

G4bool DmpStkSensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist)
{ 
   
  G4double edep = aStep->GetTotalEnergyDeposit();
  if ((edep/keV == 0.)) return false;      

  bool is_backtrack= false;
  if(aStep->GetPreStepPoint()->GetMomentum().z()>0) is_backtrack= true;

  G4int StripTotal = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRStrips();
  G4int TileTotal  = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRTiles();  //number of tiles per layer

  // This TouchableHistory is used to obtain the physical volume
  // of the hit
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
  
  //G4cout << "       point1 momentum (MeV): " <<aStep->GetPreStepPoint()->GetMomentum().x() << G4endl;
  //G4VPhysicalVolume* phys_tile = theTouchable->GetVolume();  
  
  G4VPhysicalVolume* plane = theTouchable->GetVolume(1);  //this is a Tile
  
  G4int PlaneNumber = 0;
  PlaneNumber=plane->GetCopyNo();
  G4String PlaneName = plane->GetName();
  G4int LayerNumber = PlaneNumber/4;  //0-11
  G4int BlockNumber = (PlaneNumber%4);//0-3  

  // The RO History is used to obtain the real strip
  // of the hit

  G4int StripNumber = 0;
  G4VPhysicalVolume* strip = 0;
  strip = ROhist->GetVolume();

  //  if (strip){
    G4String StripName = strip->GetName();
    StripNumber= strip->GetCopyNo();  
    //Number of RO strips on a tile: 0-767
    //  }
  //  ROhist->MoveUpHistory();
  G4VPhysicalVolume* tile = ROhist->GetVolume(1); 
  G4int TileNumber = tile->GetCopyNo();  
  G4String TileName = tile->GetName();   
  /***
  G4cout << " Strip Number = " << StripNumber << ", name = " << StripName  << G4endl;      
  G4cout << " Tile Number = " << TileNumber << ", name = " << TileName  << G4endl;
  G4cout << " Block Index = " << PlaneNumber << ", name = " << PlaneName  << G4endl;
  G4cout << " Layer Number = " << LayerNumber  << ", Block Number = " << BlockNumber <<G4endl;

  //StripTotal=768, TileTotal=4 (numnber of tiles per ladders)
  //G4cout << " StripTotal = " << StripTotal  << " TileTotal = " << TileTotal << G4endl;
  ***/
  //Ladder number
  G4int NTile = (TileNumber%TileTotal);  
  G4int j=0;
  
  //4 tiles wire-bonded to a ladder 
  for (j=0;j<TileTotal;j++)
    {
      //strip number within a block (0-3071)
      if(NTile==j) StripNumber += StripTotal*NTile;
    }  
  
  G4int NChannel = 0;
  //NChannel = PlaneNumber*TileTotal*StripTotal + StripNumber;
  NChannel = (LayerNumber*4 + BlockNumber)*TileTotal*StripTotal + StripNumber;

  //strip number witin a layer (0-12287)
  StripNumber += BlockNumber*TileTotal*StripTotal;

 
  G4int trackID = aStep->GetTrack()->GetTrackID();
  bool isPrim = false;
  if((trackID == 2 || trackID == 3) && isPhotonRun) isPrim = true;
  else if (trackID == 1) isPrim = true;

  //G4cout << " Channel Number = " << NChannel  << " Strip number on plane = " << StripNumber << " plane name " << PlaneName << G4endl;
  if (PlaneName == "STKDetectorX" ) {
    // The hit is on an X silicon plane
    
    //G4cout << "   X layer " << " hitXid " << ThitXID[NChannel] << G4endl;
    // This is a new hit
    if (ThitXID[NChannel]==-1) {       
      DmpSimuStkHit* TrackerHit = new DmpSimuStkHit;
      TrackerHit->SetPlaneType(1);
      TrackerHit->AddSil(edep);
      TrackerHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
      TrackerHit->SetNSilPlane(LayerNumber);
      TrackerHit->SetNSilBlock(BlockNumber);
      TrackerHit->SetNStrip(StripNumber);
      TrackerHit->SetNtracks(1);
      /***
	  TrackerHit->SetPDGcode( aStep->GetTrack()->GetDynamicParticle()->GetPDGcode() );
      ***/
      //count back scattering tracks
      if(is_backtrack) TrackerHit->SetNtracksBack(1);
      
      //current track ID
      TrackerHit->SetTrackID(trackID);
      if(isPrim) {
	TrackerHit->AddSilPrim(edep);
	TrackerHit->SetPrimTrackID(trackID);
	TrackerHit->SetNtracksPrim(1);
      }
      ThitXID[NChannel] = TrackerCollection->insert(TrackerHit) -1;
      //G4cout << "X new strip: track ID " << aStep->GetTrack()->GetTrackID() <<  " edp " << edep<< " prim edp " << TrackerHit->GetEdepSilPrim() << " NChannel " << NChannel << " isPrim " << isPrim << G4endl;
    }
    else { // This is not new strip      
      (*TrackerCollection)[ThitXID[NChannel]]->AddSil(edep);
      if(isPrim) {
	(*TrackerCollection)[ThitXID[NChannel]]->AddSilPrim(edep);
      }
      G4int oldID = (*TrackerCollection)[ThitXID[NChannel]]->GetTrackID();
      //G4cout << "  X more hit old track " << oldID << " new track " << trackID << " isPrim " << isPrim << G4endl;
      if(oldID != trackID) {
	if(isPrim) {
	  G4int oldPrimID = (*TrackerCollection)[ThitXID[NChannel]]->GetPrimTrackID();
	  (*TrackerCollection)[ThitXID[NChannel]]->SetPrimTrackID(oldPrimID*100 + trackID);
	  G4int oldP = (*TrackerCollection)[ThitXID[NChannel]]->GetNtracksPrim();
	  (*TrackerCollection)[ThitXID[NChannel]]->SetNtracksPrim(oldP + 1);
	}
	//save old ID if not primary track
	bool oldPrim = false;
	if((oldID == 2 || oldID == 3) && isPhotonRun) oldPrim = true;
	else if (oldID == 1) oldPrim = true;
	if(!oldPrim) (*TrackerCollection)[ThitXID[NChannel]]->SetTrackID1(oldID);
	
	//update current track ID
	(*TrackerCollection)[ThitXID[NChannel]]->SetTrackID(trackID);
	//update number of tracks
	G4int oldN = (*TrackerCollection)[ThitXID[NChannel]]->GetNtracks();
	(*TrackerCollection)[ThitXID[NChannel]]->SetNtracks(oldN + 1);
	//G4cout << "    number of tracks before" << oldN << G4endl;

	//update number of back scattering tracks
	if(is_backtrack) {
	  G4int oldNback = (*TrackerCollection)[ThitXID[NChannel]]->GetNtracksBack();
	  (*TrackerCollection)[ThitXID[NChannel]]->SetNtracksBack(oldNback + 1);
	  //G4cout << "    number of back tracks before" << oldNback << G4endl;
	}
      }
      //G4cout << "  X more hit (" << (*TrackerCollection)[ThitXID[NChannel]]->GetNtracks() << "): track ID " << aStep->GetTrack()->GetTrackID() 
      //     <<  " edp " << edep<< " prim edp " << (*TrackerCollection)[ThitXID[NChannel]]->GetEdepSilPrim() << " NChannel " << NChannel<< G4endl;
    }
  }
  
  if (PlaneName == "STKDetectorY") {
    // The hit is on an Y silicon plane    
    //G4cout << "   Y layer " << " hitYid " << ThitYID[NChannel] << G4endl;
    // This is a new hit
    if (ThitYID[NChannel]==-1) {       
	DmpSimuStkHit* TrackerHit = new DmpSimuStkHit;
	TrackerHit->SetPlaneType(0);
	TrackerHit->AddSil(edep);
	TrackerHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	TrackerHit->SetNSilPlane(LayerNumber);
	TrackerHit->SetNSilBlock(BlockNumber);
	TrackerHit->SetNStrip(StripNumber);
	TrackerHit->SetNtracks(1);
	//count back scattering tracks
	if(is_backtrack) TrackerHit->SetNtracksBack(1);

	//current track ID
	TrackerHit->SetTrackID(trackID);
	if(isPrim) {
	  TrackerHit->AddSilPrim(edep);
	  TrackerHit->SetPrimTrackID(trackID);
	  TrackerHit->SetNtracksPrim(1);
	}
	ThitYID[NChannel] = TrackerCollection->insert(TrackerHit)-1;
	//G4cout << "Y new strip: track ID " << aStep->GetTrack()->GetTrackID() <<  " edp " << edep<< " prim edp " << TrackerHit->GetEdepSilPrim() << " NChannel " << NChannel<< " isPrim " << isPrim <<G4endl;
    }
    else  {// This is not new strip
      (*TrackerCollection)[ThitYID[NChannel]]->AddSil(edep);
      if(isPrim) {
	  (*TrackerCollection)[ThitYID[NChannel]]->AddSilPrim(edep);
      }
      G4int oldID = (*TrackerCollection)[ThitYID[NChannel]]->GetTrackID();
      if(oldID != trackID) {
	if(isPrim) {
	  G4int oldPrimID = (*TrackerCollection)[ThitYID[NChannel]]->GetPrimTrackID();
	  (*TrackerCollection)[ThitYID[NChannel]]->SetPrimTrackID(oldPrimID*100 + trackID);
	  G4int oldP = (*TrackerCollection)[ThitYID[NChannel]]->GetNtracksPrim();
	  (*TrackerCollection)[ThitYID[NChannel]]->SetNtracksPrim(oldP + 1);
	  
	}
	//save old ID if not primary track
	bool oldPrim = false;
	if((oldID == 2 || oldID == 3) && isPhotonRun) oldPrim = true;
	else if (oldID == 1) oldPrim = true;
	if(!oldPrim) (*TrackerCollection)[ThitYID[NChannel]]->SetTrackID1(oldID);
	
	//update current track ID
	(*TrackerCollection)[ThitYID[NChannel]]->SetTrackID(trackID);
	//update number of tracks
	G4int oldN = (*TrackerCollection)[ThitYID[NChannel]]->GetNtracks();
	(*TrackerCollection)[ThitYID[NChannel]]->SetNtracks(oldN + 1);
	
	//update number of back scattering tracks
	if(is_backtrack) {
	  G4int oldNback = (*TrackerCollection)[ThitYID[NChannel]]->GetNtracksBack();
	  (*TrackerCollection)[ThitYID[NChannel]]->SetNtracksBack(oldNback + 1);
	}
      }
      //G4cout << "   Y more hit (" << (*TrackerCollection)[ThitYID[NChannel]]->GetNtracks() << "): track ID " << aStep->GetTrack()->GetTrackID() 
      //     <<  " edp " << edep<< " prim edp " << (*TrackerCollection)[ThitYID[NChannel]]->GetEdepSilPrim() << " NChannel " << NChannel<< G4endl;
    }
  }
  
  return true;
}

void DmpStkSensitiveDetector::EndOfEvent(G4HCofThisEvent* HCE)
{
  //G4cout << "DmpStkSensitiveDetector::EndOfEvent called: register the DmpStkHitsCollection " << G4endl;
  static G4int HCID = -1;
  if(HCID<0)
    { 
      HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
  HCE->AddHitsCollection(HCID,TrackerCollection);


  for (G4int i=0;i<NbOfTKRChannels;i++) 
    {
      ThitXID[i] = -1;
      ThitYID[i] = -1;
    };
}

void DmpStkSensitiveDetector::clear()
{} 

void DmpStkSensitiveDetector::DrawAll()
{} 

void DmpStkSensitiveDetector::PrintAll()
{} 













