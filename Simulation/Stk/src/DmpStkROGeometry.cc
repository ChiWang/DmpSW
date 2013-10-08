#include "DmpStkROGeometry.hh"

#include "G4RunManager.hh"
#include "DmpStkDummySD.hh"
#include "DmpDetectorConstruction.hh"
#include "DmpStkDetectorDescription.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SDManager.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
 

DmpStkROGeometry::DmpStkROGeometry()
  : G4VReadOutGeometry()
{
}
DmpStkROGeometry::DmpStkROGeometry(G4String aString)
  :G4VReadOutGeometry(aString)
{
 G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());
}

DmpStkROGeometry::~DmpStkROGeometry()
{
}

G4VPhysicalVolume* DmpStkROGeometry::Build()
{
  // A dummy material is used to fill the volumes of the readout geometry.
  // ( It will be allowed to set a NULL pointer in volumes of such virtual
  // division in future, since this material is irrelevant for tracking.)
  G4Material* dummyMat  = new G4Material(name="dummyMat", 1., 1.*g/mole, 1.*g/cm3);
  
  //Builds the ReadOut World:

  G4double WorldSizeXY = dmpDetector->GetWorldSizeXY();
  G4double WorldSizeZ  = dmpDetector->GetWorldSizeZ();
  
  G4Box* ROWorldBox = new 
    G4Box("ROWorldBox",WorldSizeXY/2,WorldSizeXY/2,WorldSizeZ/2); 
  
  G4LogicalVolume* ROWorldLog = new G4LogicalVolume(ROWorldBox, dummyMat,
						    "ROWorldLogical");
  G4PVPlacement* ROWorldPhys = 
    new G4PVPlacement(0,G4ThreeVector(),"ROWorldPhysical",
		      ROWorldLog,0,false,0);
  
  // Payload RO volume:
  
  G4double PayloadSizeXY = dmpDetector->GetPayloadSizeXY();
  G4double PayloadSizeZ  = dmpDetector->GetPayloadSizeZ();
  
  G4VSolid* solidPayloadRO
    = new G4Box("Payload RO",		
		PayloadSizeXY/2,
		PayloadSizeXY/2,
		PayloadSizeZ/2);
  
  G4LogicalVolume* logicPayloadRO = new 
    G4LogicalVolume(solidPayloadRO,dummyMat,"Payload RO",0,0,0);  
  
  G4VPhysicalVolume* physiPayloadRO =
    new G4PVPlacement(0, G4ThreeVector(), 
		      "Payload RO", logicPayloadRO,ROWorldPhys,false, 0);
  
  // -------------------------------
  // Tracker readout division:
  // -------------------------------
  // TRK Layers of Silicon MicroStrips
 
  
  G4cout << "DmpStkROGeometry::Build(): building tracker readout geometry " << G4endl;
  G4double STKSizeXY       = dmpDetector->GetSTKSizeXY();
  G4double STKSizeZ        = dmpDetector->GetSTKSizeZ();
  
  G4VSolid*   ROsolidTKR =
    new G4Box("ReadOutTKR", STKSizeXY/2,STKSizeXY/2,STKSizeZ/2); 
  
  G4LogicalVolume*  ROlogicTKR =
    new G4LogicalVolume(ROsolidTKR,dummyMat, "ReadOutTKR",0,0,0);	
						       
  G4double STKCenter =  dmpDetector->GetSTKCenter();
  G4cout << "    RO TKR size XY/Z: " << STKSizeXY << "/" << STKSizeZ << " placed at z= "<< STKCenter << G4endl;
  G4VPhysicalVolume* ROphysiTKR = 
    new G4PVPlacement(0, G4ThreeVector(0,0,STKCenter), "ReadOutTKR",ROlogicTKR,physiPayloadRO, false, 0);		
  
  // STK Layers
  
  G4double TKRSiliconThickness =  dmpDetector->GetStkDetectorDescription()->GetTKRSiliconThickness();
  G4int NbOfTKRLayers          =  dmpDetector->GetStkDetectorDescription()->GetNbOfTKRLayers();
  G4double TKRLayerDistance    =  dmpDetector->GetStkDetectorDescription()->GetTKRLayerDistance();
  G4double TKRViewsDistance    =  dmpDetector->GetStkDetectorDescription()->GetTKRViewsDistance();  
  G4double TKRBlockXY          =  dmpDetector->GetStkDetectorDescription()->GetTKRBlockXY();
  G4double TKRCenterGap        =  dmpDetector->GetStkDetectorDescription()->GetTKRCenterGap();  
  
  G4VSolid*  solidTKRDetectorYRO = new G4Box
    ("STKDetectorYRO",TKRBlockXY/2,TKRBlockXY/2,TKRSiliconThickness/2); 
  
  G4LogicalVolume* logicTKRDetectorYRO =
    new G4LogicalVolume(solidTKRDetectorYRO,dummyMat, "STKDetectorYRO",0,0,0);

  G4VSolid*  solidTKRDetectorXRO = new G4Box
    ("STKDetectorXRO",TKRBlockXY/2,TKRBlockXY/2,TKRSiliconThickness/2); 
  
  G4LogicalVolume* logicTKRDetectorXRO =
    new G4LogicalVolume(solidTKRDetectorXRO,dummyMat, "STKDetectorXRO",0,0,0);
  G4int i=0;
  G4int j1=0;
  G4int j2=0;
  G4int nb=0;
  G4VPhysicalVolume* physiTKRDetectorXRO = 0;
  G4VPhysicalVolume* physiTKRDetectorYRO = 0;
  
  for (i = 0; i < NbOfTKRLayers; i++)
    {
    for (j1 = 0; j1 < 2; j1++) {
      for (j2 = 0; j2 < 2; j2++) {
	nb = i*4 + j1*2 + j2;
	G4double xcenter = -STKSizeXY/2 + TKRBlockXY/2 + j1*TKRCenterGap + j1*TKRBlockXY;  
	G4double ycenter = -STKSizeXY/2 + TKRBlockXY/2 + j2*TKRCenterGap + j2*TKRBlockXY; 
	if(i==0) G4cout << "         Block " << j1 << "-" << j2 << " placed at x= " << xcenter << ", y= " << ycenter << G4endl;

	physiTKRDetectorYRO = 
	  new G4PVPlacement(0,G4ThreeVector(xcenter,ycenter,-STKSizeZ/2
					  +TKRSiliconThickness/2 
					  +(i)*TKRLayerDistance),
			  "STKDetectorYRO",		
			  logicTKRDetectorYRO,
			  ROphysiTKR,
			  false,	
			  nb);	
      
	physiTKRDetectorXRO = 
	  new G4PVPlacement(0,G4ThreeVector(xcenter,ycenter,
					  -STKSizeZ/2+
					  TKRSiliconThickness/2 +
					  TKRViewsDistance+
					  TKRSiliconThickness+
					  (i)*TKRLayerDistance),
			  "STKDetectorXRO",		
			  logicTKRDetectorXRO,
			  ROphysiTKR,
			  false,	
			  nb);	

      }
    }

      G4cout << "      RO  Layer " << i << G4endl;
      G4cout << "         RO y-layer placed at z= " << -STKSizeZ/2+TKRSiliconThickness/2+(i)*TKRLayerDistance << G4endl;
      G4cout << "         RO x-layer placed at z= " << -STKSizeZ/2+TKRSiliconThickness/2+TKRViewsDistance+TKRSiliconThickness+(i)*TKRLayerDistance << G4endl;
      
    }
  

  // Silicon Tiles 
  // some problems with the RO tree

  G4double TKRActiveTileXY =  dmpDetector->GetStkDetectorDescription()->GetTKRActiveTileXY();
  G4double TKRActiveTileZ  =  dmpDetector->GetStkDetectorDescription()->GetTKRActiveTileZ();  

  G4VSolid * solidTKRActiveTileXRO = new
    G4Box("Active Tile X", TKRActiveTileXY/2,TKRActiveTileXY/2,TKRActiveTileZ/2);

  G4VSolid * solidTKRActiveTileYRO = new
    G4Box("Active Tile Y", TKRActiveTileXY/2,TKRActiveTileXY/2,TKRActiveTileZ/2);
  
  
  G4LogicalVolume* logicTKRActiveTileXRO = 
    new G4LogicalVolume(solidTKRActiveTileXRO, dummyMat,"Active Tile",0,0,0);

  G4LogicalVolume* logicTKRActiveTileYRO = 
    new G4LogicalVolume(solidTKRActiveTileYRO, dummyMat,"Active Tile",0,0,0);
    
  G4int j=0;
  G4int k=0;
  
  G4int NbOfTKRTiles        = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRTiles();
  G4double SiliconGuardRing = dmpDetector->GetStkDetectorDescription()->GetSiliconGuardRing();
  G4double TilesSeparation  = dmpDetector->GetStkDetectorDescription()->GetTilesSeparation();
  
  G4VPhysicalVolume* physiTKRActiveTileXRO = 0;
  G4VPhysicalVolume* physiTKRActiveTileYRO = 0;

  G4double x=0.;
  G4double y=0.;
  G4double z=0.;

  for (i=0;i< NbOfTKRTiles; i++)
    { 
      for (j=0;j< NbOfTKRTiles; j++)
	{
	  k = i*NbOfTKRTiles + j;
	  
	  //x = -TKRBlockXY/2+TilesSeparation+SiliconGuardRing+TKRActiveTileXY/2+
	  x = -TKRBlockXY/2+SiliconGuardRing+TKRActiveTileXY/2+
	    (j)*((2*SiliconGuardRing)+TilesSeparation+TKRActiveTileXY);
          //y = -TKRBlockXY/2+TilesSeparation+SiliconGuardRing+TKRActiveTileXY/2+
	  y = -TKRBlockXY/2+SiliconGuardRing+TKRActiveTileXY/2+
	    (i)*((2*SiliconGuardRing)+TilesSeparation+TKRActiveTileXY);
          z = 0.;

	  G4cout << "       placing RO y-tile " << k << " at x = " << x << " y = " << y <<  G4endl;

	  physiTKRActiveTileXRO =
	    new G4PVPlacement(0,
			      G4ThreeVector(x,y,z),
			      "Active Tile X",		
			      logicTKRActiveTileXRO,
			      physiTKRDetectorXRO,
			      false,	
			      k);	

	  //x = -TKRBlockXY/2+TilesSeparation+SiliconGuardRing+TKRActiveTileXY/2+
	  x = -TKRBlockXY/2+SiliconGuardRing+TKRActiveTileXY/2+
	    (i)*((2*SiliconGuardRing)+TilesSeparation+TKRActiveTileXY);
          //y = -TKRBlockXY/2+TilesSeparation+SiliconGuardRing+TKRActiveTileXY/2+
          y = -TKRBlockXY/2+SiliconGuardRing+TKRActiveTileXY/2+
	    (j)*((2*SiliconGuardRing)+TilesSeparation+TKRActiveTileXY);
          z = 0.;

	  G4cout << "       placing RO x-tile " << k << " at x = " << x << " y = " << y <<  G4endl;

      	  physiTKRActiveTileYRO =
	    new G4PVPlacement(0,
			      G4ThreeVector(x,y,z),
			      "Active Tile Y",		
			      logicTKRActiveTileYRO,
			      physiTKRDetectorYRO,
			      false,	
			      k);
	  	
	}
    }
  
  
  // Silicon Strips 
  // some problems with the RO tree
  
  G4double TKRXStripX=0.;
  G4double TKRYStripY=0.;
  G4double TKRYStripX=0.; 
  G4double TKRXStripY=0.;
  
  TKRXStripX = TKRYStripY = dmpDetector->GetStkDetectorDescription()->GetTKRSiliconPitch();
  TKRYStripX = TKRXStripY = dmpDetector->GetStkDetectorDescription()->GetTKRActiveTileXY();
  G4double TKRZStrip      = dmpDetector->GetStkDetectorDescription()->GetTKRSiliconThickness();
  G4int NbOfTKRStrips     = dmpDetector->GetStkDetectorDescription()->GetNbOfTKRStrips();
  G4cout << "    RO X strip (measure x) size X/Y/Z: " << TKRXStripX << "/" << TKRXStripY << "/" << TKRZStrip << G4endl;
  G4cout << "    RO Y strip (measure y) size X/Y/Z: " << TKRYStripX << "/" << TKRYStripY << "/" << TKRZStrip << G4endl;
  G4cout << "    Number of RO strips on a tile: " << NbOfTKRStrips << G4endl;

  
  G4VSolid* solidTKRStripX = new G4Box("Strip X",			
				       TKRXStripX/2,TKRYStripX/2,
				       TKRZStrip/2); 
  
  G4LogicalVolume* logicTKRStripX = 
    new G4LogicalVolume(solidTKRStripX,dummyMat,"Strip X",0,0,0);	 
  
		
  G4VSolid* solidTKRStripY = new G4Box("Strip Y",			
				       TKRXStripY/2,TKRYStripY/2,
				       TKRZStrip/2); 
  

  G4LogicalVolume* logicTKRStripY = 
    new G4LogicalVolume(solidTKRStripY,dummyMat,"Strip Y",0,0,0);	 
							
						      
  G4double TKRSiliconPitch = dmpDetector->GetStkDetectorDescription()->GetTKRSiliconPitch();

  for (i=0;i< NbOfTKRStrips; i++)
    {  
      new G4PVPlacement(0,G4ThreeVector(-TKRActiveTileXY/2 +TKRSiliconPitch/2 +
				      (i)*TKRSiliconPitch, 0., 0.),
		      "Strip X",		
		      logicTKRStripX,
		      physiTKRActiveTileXRO,
		      false,	
		      i);	

	
      new G4PVPlacement(0,G4ThreeVector(0.,-TKRActiveTileXY/2 
				      +TKRSiliconPitch/2 +
				      (i)*TKRSiliconPitch, 0.),
		      "Strip Y",		
		      logicTKRStripY,
		      physiTKRActiveTileYRO,
		      false,	
		      i);	
      
      



    }
  

  //Flags the strip as sensitive .The pointer here serves
  // as a flag only to check for sensitivity.
  // (Could we make it by a simple cast of a non-NULL value ?)
  
  DmpStkDummySD * dummySensi = new DmpStkDummySD("Orpo");  
  logicTKRStripX->SetSensitiveDetector(dummySensi);
  logicTKRStripY->SetSensitiveDetector(dummySensi);
    
  return ROWorldPhys;
}










