// Description: This class describes the detector geometry of the DAMPE STK detector
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpStkDetectorDescription.hh"
//#include "DmpStkDetectorMessenger.hh"
#include "DmpStkSensitiveDetector.hh"
#include "DmpStkROGeometry.hh"

#include "G4Material.hh"
#include "G4ProductionCuts.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4TransportationManager.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4RegionStore.hh"

DmpStkDetectorDescription::DmpStkDetectorDescription()
  :solidTKR(0),logicTKR(0),physiTKR(0),
   solidTKRDetectorX(0),logicTKRDetectorX(0),physiTKRDetectorX(0),
   solidTKRDetectorY(0),logicTKRDetectorY(0),physiTKRDetectorY(0),
   solidPlane(0),logicPlane(0),physiPlane(0),
   solidPlaneThinW(0),logicPlaneThinW(0),physiPlaneThinW(0),
   solidPlaneThickW(0),logicPlaneThickW(0),physiPlaneThickW(0),
   solidConverter(0),logicConverter(0),physiConverter(0),
   solidThickConverter(0),logicThickConverter(0),physiThickConverter(0),
   stkSensitiveDetector(0),aTKRRegion(0)
{
  // default parameter values of the payload
  
  //tungsten converter hickness
  ConverterThickness = 1000.*micrometer;
  //ThickConverterThickness = 2000.*micrometer;
  ThickConverterThickness = 1000.*micrometer;

  //SSD geometry
  TKRSiliconThickness = 320.*micrometer;//thickness
  TKRSiliconTileXY = 9.5*cm;//size 
  TKRSiliconPitch = 121.*micrometer;  //physical pitch
  //TKRSiliconPitch = 242.*micrometer; //readout pitch  
  SiliconGuardRing = 1.036*mm; //guard ring thickness
  NbOfTKRStrips = 768;

  //ladder geometry
  NbOfTKRTiles = 4;
  //NbOfWTKRTiles = 4; //number of SSD covered by a W plate
  NbOfWTKRTiles = 2;
  TilesSeparation = 80.*micrometer;
  TKRWRecess = 1.*mm;
  //TKRWRecess = 0.*mm;

  //tracker geometry 
  TKRLayerDistance = 3.2*cm;
  TKRViewsDistance = 2.*mm;
  //TKRCenterGap = 0.*mm;
  TKRCenterGap = 80.*micrometer;
  TKRTungstenDistance = 1.6*mm; //distance from converter to SSD

  NbOfTKRLayers = 6;
  NbOfTKRBlocks = 4;

  // create commands for interactive definition of the payload
  //stkDetectorMessenger = new DmpStkDetectorMessenger(this);

}

DmpStkDetectorDescription::~DmpStkDetectorDescription()
{ 
  //delete stkDetectorMessenger;
}

void DmpStkDetectorDescription::DefineMaterials()
{ 
  
  G4String name, symbol;    
  G4double a, z, density;            
  
  G4int ncomponents;
  G4double fractionmass;
  G4double temperature, pressure;

  a = 28.09*g/mole;
  G4Element* Silicon = new G4Element(name="Silicon", symbol="Si", z=14., a);
  
  density = 19.3*g/cm3;
  a = 183.84*g/mole;
  G4Material* W = new G4Material(name="Tungsten", z=74., a, density);
  
  density = 2.333*g/cm3;  
  G4Material* Si = new G4Material(name="Silicon", density, ncomponents=1);
  Si->AddElement(Silicon, fractionmass=1.);
  
  density     = universe_mean_density;    //from PhysicalConstants.h
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  G4Material* vacuum = new G4Material(name="Galactic", z=1., a=1.01*g/mole, density,kStateGas,temperature,pressure);
  
  G4cout << "DmpStkDetectorDescriotion::DefineMaterials: dump material defined " << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  
  ConverterMaterial = W;
  defaultMaterial  = vacuum;
  TKRMaterial = Si;

}

void DmpStkDetectorDescription::Construct(G4double TKRcenter, G4VPhysicalVolume* physi, G4LogicalVolume* logi )
{
  physiTKR = physi;
  logicTKR = logi;

  DefineMaterials();

  // compute the global definitions: World, Payload, PSD, STK, BGO, NUD
  ComputeParameters();
  
  // Tracker Structure (Plane + TKRDetectorX + TKRDetectorY, Converter to be inserted into Plane later) 

  G4cout << "    TKR support tray size XY/Z: " << TKRSizeXY << "/" << TKRSupportThickness << G4endl;
  solidPlane = new G4Box("Plane",			
			 TKRSizeXY/2,TKRSizeXY/2,TKRSupportThickness/2); 
  
  logicPlane = new G4LogicalVolume(solidPlane,
				   defaultMaterial, 
				   "Plane");	
  
  G4cout << "    TKR tray (for 2mm W) size XY/Z: " << TKRSizeXY << "/" << TKRSupportThickness << G4endl;
  solidPlaneThickW = new G4Box("PlaneThickW",			
			 TKRSizeXY/2,TKRSizeXY/2,TKRSupportThickness/2); 
  
  logicPlaneThickW = new G4LogicalVolume(solidPlaneThickW,
				   defaultMaterial, 
				   "PlaneThickW");	

  G4cout << "    TKR tray (for 1mm W ) size XY/Z: " << TKRSizeXY << "/" << TKRSupportThickness << G4endl;
  solidPlaneThinW = new G4Box("PlaneThinW",			
			 TKRSizeXY/2,TKRSizeXY/2,TKRSupportThickness/2); 
  
  logicPlaneThinW = new G4LogicalVolume(solidPlaneThinW,
				   defaultMaterial, 
				   "PlaneThinW");	
  

  G4cout << "    TKR si block size XY/Z: " << TKRBlockXY << "/" << TKRSiliconThickness << G4endl;
  solidTKRDetectorY = new G4Box
    ("STKDetectorY",TKRBlockXY/2,TKRBlockXY/2,TKRSiliconThickness/2); 
  
  logicTKRDetectorY = new G4LogicalVolume(solidTKRDetectorY,
					  defaultMaterial, 
					  "STKDetector Y");	  
  
  solidTKRDetectorX = new G4Box
    ("STKDetectorX",TKRBlockXY/2,TKRBlockXY/2,TKRSiliconThickness/2); 
  
  logicTKRDetectorX = new G4LogicalVolume(solidTKRDetectorX,
					  defaultMaterial, 
					  "STKDetector X");	
 
  
  //Tungsten plates covers 2x2 sensors
  G4cout << "    TKR W plate size XY/Z: " << TKRWBlockXY << "/" << ConverterThickness << G4endl;
  solidConverter = new G4Box
    ("Converter",TKRWBlockXY/2,TKRWBlockXY/2,ConverterThickness/2); 
  
  logicConverter = new G4LogicalVolume(solidConverter,
				       ConverterMaterial, 
				       "Converter");	

  G4cout << "    TKR thick W plate size XY/Z: " << TKRWBlockXY << "/" << ThickConverterThickness << G4endl;
  solidThickConverter = new G4Box
    ("ThickConverter",TKRWBlockXY/2,TKRWBlockXY/2,ThickConverterThickness/2); 
  
  logicThickConverter = new G4LogicalVolume(solidThickConverter,
				       ConverterMaterial, 
				       "ThickConverter");	
  
  G4int i=0;
  G4int j1=0;
  G4int j2=0;
  G4int nb=0;
  G4int nw1=0;
  G4int nw2=0;
  

  G4cout << "    Adding tracker layers to TKR , 4 block per layer ...... " << G4endl;
  for (i = 0; i < NbOfTKRLayers; i++) {
    
    for (j1 = 0; j1 < 2; j1++) {
      for (j2 = 0; j2 < 2; j2++) {
	nb = i*4 + j1*2 + j2;
	G4double xcenter = -TKRSizeXY/2 + TKRBlockXY/2 + j1*TKRCenterGap + j1*TKRBlockXY;  
	G4double ycenter = -TKRSizeXY/2 + TKRBlockXY/2 + j2*TKRCenterGap + j2*TKRBlockXY; 
	if(i==0) G4cout << "         Block " << j1 << "-" << j2 << " (" << j1*2+j2 <<") placed at x= " << xcenter << ", y= " << ycenter << G4endl;

	physiTKRDetectorY = 
	  new G4PVPlacement(0,G4ThreeVector(xcenter,ycenter,-TKRSizeZ/2
					    +TKRSiliconThickness/2 
					    +(i)*TKRLayerDistance),
			    "STKDetectorY",		
			    logicTKRDetectorY,
			    physiTKR,
			    false,	
			    nb);
	
	physiTKRDetectorX = 
	  new G4PVPlacement(0,G4ThreeVector(xcenter,ycenter,
					    -TKRSizeZ/2+
					    TKRSiliconThickness/2 +
					    TKRViewsDistance+
					    TKRSiliconThickness+
					    (i)*TKRLayerDistance),
			    "STKDetectorX",		
			    logicTKRDetectorX,
			    physiTKR,
			    false,	
			    nb);
      }
    }
    G4double centerYLayer = -TKRSizeZ/2+TKRSiliconThickness/2+(i)*TKRLayerDistance;
    G4double centerXLayer = -TKRSizeZ/2+TKRSiliconThickness/2+(i)*TKRLayerDistance+TKRViewsDistance+TKRSiliconThickness; 
    G4double globalYLayer = centerYLayer + TKRcenter;
    G4double globalXLayer = centerXLayer + TKRcenter;

    G4cout << "       Layer " << i << G4endl;
    G4cout << "         Si y-layer placed at z= " << centerYLayer << " global z= " << globalYLayer << G4endl;
    G4cout << "                         from z= " << centerYLayer-TKRSiliconThickness/2 << " to " << centerYLayer+TKRSiliconThickness/2 << G4endl;
    G4cout << "         Si x-layer placed at z= " << centerXLayer << " global z= " << globalXLayer << G4endl;
    G4cout << "                         from z= " << centerXLayer-TKRSiliconThickness/2 << " to " << centerXLayer+TKRSiliconThickness/2 << G4endl;
    //support structure
    G4double centerPlane = -TKRSizeZ/2+(i)*TKRLayerDistance+2*TKRSiliconThickness +TKRViewsDistance+TKRSupportThickness/2;
    G4double globalPlane = centerPlane + TKRcenter;
    G4cout << "         Support structure  placed at z= " << centerPlane << " global z= " << globalPlane << G4endl;
    G4cout << "                                 from z= " << centerPlane-TKRSupportThickness/2 << " to " << centerPlane+TKRSupportThickness/2 << G4endl;
    if(i<2 || i>4) {    
      physiPlane =
	new G4PVPlacement(0,G4ThreeVector(0.,0.,
					  -TKRSizeZ/2+
					  2*TKRSiliconThickness +
					  TKRViewsDistance+
					  TKRSupportThickness/2+
					  (i)*TKRLayerDistance),
			  "Plane",		
			  logicPlane,
			  physiTKR,
			  false,	
			  i);	
    }
    else {
      G4double zcenter = 0.;
    
      if(i==4) {
	physiPlaneThinW =
	  new G4PVPlacement(0,G4ThreeVector(0.,0.,
					    -TKRSizeZ/2+
					    2*TKRSiliconThickness +
					    TKRViewsDistance+
					    TKRSupportThickness/2+
					    (i)*TKRLayerDistance),
			    "PlaneThinW",		
			    logicPlaneThinW,
			    physiTKR,
			    false,	
			    i);	
	zcenter = -TKRSupportThickness/2 + ConverterThickness/2 + TKRTungstenDistance;
	G4double globalz = zcenter + globalPlane;        
	G4cout << "    Placing thin  tungsten plates into support structure at z=  " << zcenter << " global z= " << globalz << G4endl;
      }
      else {
	physiPlaneThickW =
	  new G4PVPlacement(0,G4ThreeVector(0.,0.,
					    -TKRSizeZ/2+
					    2*TKRSiliconThickness +
					    TKRViewsDistance+
					    TKRSupportThickness/2+
					    (i)*TKRLayerDistance),
			    "PlaneThickW",		
			    logicPlaneThickW,
			    physiTKR,
			    false,	
			    i);	
	zcenter = -TKRSupportThickness/2 + ThickConverterThickness/2 + TKRTungstenDistance;        
	G4double globalz = zcenter + globalPlane;        
	G4cout << "    Placing thick tungsten plates into support structure at z=  " << zcenter << " global z= " << globalz << G4endl;
      }
      //place tungten plates into support structure
      int nWrow = 8/NbOfWTKRTiles;
      for (j1 = 0; j1 < nWrow; j1++) {
	for (j2 = 0; j2 < nWrow; j2++) {
	  //G4double xcenter = -TKRSizeXY/2 + TKRWBlockXY/2 + TKRWRecess + j1*TKRCenterGap + j1*(TKRWBlockXY+2*TKRWRecess+TilesSeparation);  
	  //G4double ycenter = -TKRSizeXY/2 + TKRWBlockXY/2 + TKRWRecess + j2*TKRCenterGap + j2*(TKRWBlockXY+2*TKRWRecess+TilesSeparation); 
	  G4double xcenter = -TKRSizeXY/2 + TKRWBlockXY/2 + TKRWRecess + j1*(TKRWBlockXY+2*TKRWRecess+TilesSeparation);  
	  G4double ycenter = -TKRSizeXY/2 + TKRWBlockXY/2 + TKRWRecess + j2*(TKRWBlockXY+2*TKRWRecess+TilesSeparation); 
	  if(i==2) G4cout << "         plates " << j1 << "-" << j2 << " (" << j1*nWrow+j2 << ") placed at x= " << xcenter << ", y= " << ycenter << G4endl;

	  if(i==4) {
	    new G4PVPlacement(0,G4ThreeVector(xcenter,ycenter,zcenter),
			      "Converter",		
			      logicConverter,
			      physiPlaneThinW,
			      false,	
			      nw1);
	    ++nw1;
	  }
	  else {
	    new G4PVPlacement(0,G4ThreeVector(xcenter,ycenter,zcenter),
			      "ThickConverter",		
			      logicThickConverter,
			      physiPlaneThickW,
			      false,	
			      nw2);
	    ++nw2;
	  }
	}
      }
    }
  }
  G4cout << "  Total number of si block placed per view: " << nb+1 << G4endl;
  G4cout << "  Total number of thin W plates placed : " << nw1 << G4endl;
  G4cout << "  Total number of thickW plated placed : " << nw2 << G4endl;
  G4cout << G4endl;

  G4cout << " ===  Placng active tiles on tracker : y-tile in direction y, x-tile in direction x" << G4endl;

  G4cout << "    TKR Tile active area XY/Z: " << TKRActiveTileXY << "/" << TKRActiveTileZ << G4endl;
  G4cout << "    TKR TilesSeparation: " << TilesSeparation << " GuardRing: " << SiliconGuardRing << G4endl;
  
  G4VSolid * solidTKRActiveTileX = new
    G4Box("Active Tile X", TKRActiveTileXY/2,
	  TKRActiveTileXY/2,TKRActiveTileZ/2);
  
  
  G4VSolid * solidTKRActiveTileY = new
    G4Box("Active Tile Y", TKRActiveTileXY/2,
	  TKRActiveTileXY/2,TKRActiveTileZ/2);
  
  
  G4LogicalVolume* logicTKRActiveTileX = 
    new G4LogicalVolume(solidTKRActiveTileX, TKRMaterial,
			"Active Tile X",0,0,0);
  
  
  G4LogicalVolume* logicTKRActiveTileY = 
    new G4LogicalVolume(solidTKRActiveTileY, TKRMaterial,
			"Active Tile Y",0,0,0);
  
  
  G4int j=0;
  G4int k=0;
  
  G4double x=0.;
  G4double y=0.;
  G4double z=0.;
  
  for (i=0;i< NbOfTKRTiles; i++)
    { 
      for (j=0;j< NbOfTKRTiles; j++)
	{
	  k = i*NbOfTKRTiles + j;
	  
	  
	  //x = -TKRBlockXY/2+TilesSeparation+SiliconGuardRing+
	  x = -TKRBlockXY/2+SiliconGuardRing+TKRActiveTileXY/2
	    +(i)*((2*SiliconGuardRing)+TilesSeparation+TKRActiveTileXY);
	  //y = -TKRBlockXY/2+TilesSeparation+SiliconGuardRing+
	  y = -TKRBlockXY/2+SiliconGuardRing+TKRActiveTileXY/2
	    +(j)*((2*SiliconGuardRing)+TilesSeparation+TKRActiveTileXY);
	  z = 0.;
	  
	  G4cout << "       Placing y-tile " << k << " at x = " << x << " y = " << y <<  G4endl;

	  new G4PVPlacement(0,
			      G4ThreeVector(x,y,z),
			      "Active Tile Y",		
			      logicTKRActiveTileY,
			      physiTKRDetectorY,
			      false,	
			      k);
	  

	  //x = -TKRBlockXY/2+TilesSeparation+SiliconGuardRing+
	  x = -TKRBlockXY/2+SiliconGuardRing+TKRActiveTileXY/2
	    +(j)*((2*SiliconGuardRing)+TilesSeparation+TKRActiveTileXY);
	  //y = -TKRBlockXY/2+TilesSeparation+SiliconGuardRing+
	  y = -TKRBlockXY/2+SiliconGuardRing+TKRActiveTileXY/2
	    +(i)*((2*SiliconGuardRing)+TilesSeparation+TKRActiveTileXY);
	  z = 0.;
	      
	  G4cout << "       Placing x-tile " << k << " at x = " << x << " y = " << y <<  G4endl;

	  new G4PVPlacement(0,
			      G4ThreeVector(x,y,z),
			      "Active Tile X",		
			      logicTKRActiveTileX,
			      physiTKRDetectorX,
			      false,	
			      k);	
	  
	}
    }
  G4cout << "  Total number of tiles placed : " << k+1 << G4endl;
  G4cout << G4endl;

  // Cuts by Regions 
  G4String regName[] = {"Tracker"};
  if (aTKRRegion) delete aTKRRegion;

  aTKRRegion = new G4Region(regName[0]);
  logicTKR->SetRegion(aTKRRegion);
  aTKRRegion->AddRootLogicalVolume(logicTKR);
  
  G4double cutValue[] = {0.01*mm};//10um
  //G4double cutValue[] = {0.1*mm}; //100um
 
  G4Region* reg = G4RegionStore::GetInstance()->GetRegion(regName[0]);
  G4cout <<"DmpStkDetectorDescription: setting production cut for region: " << reg->GetName() << ", value: " << cutValue[0]<< G4endl;
  G4ProductionCuts* cuts = new G4ProductionCuts;
  cuts->SetProductionCut(cutValue[0]);
  reg->SetProductionCuts(cuts);
  
  //Sensitive Detector Manager
  G4SDManager* SDman = G4SDManager::GetSDMpointer();                               
  if(!stkSensitiveDetector) {
    stkSensitiveDetector = new DmpStkSensitiveDetector("StkSD");
    SDman->AddNewDetector( stkSensitiveDetector );		
  }
                                 
  //STK Readout geometry: in the STK 4-SSD are wire-bonded to form a ladder  
  G4String ROgeometryName = "TrackerROGeom";
  G4VReadOutGeometry* stkRO = 
    new DmpStkROGeometry(ROgeometryName);
  stkRO->BuildROGeometry();
  stkSensitiveDetector->SetROgeometry(stkRO);

  if (logicTKRActiveTileX)
    logicTKRActiveTileX->SetSensitiveDetector(stkSensitiveDetector);
  if (logicTKRActiveTileY)
    logicTKRActiveTileY->SetSensitiveDetector(stkSensitiveDetector);

  //                                        
  // Visualization attributes
  //
  // Invisible Volume
  logicTKRActiveTileX->SetVisAttributes(G4VisAttributes::Invisible);  
  logicTKRActiveTileY->SetVisAttributes(G4VisAttributes::Invisible);  
  logicPlane->SetVisAttributes(G4VisAttributes::Invisible);  
  //logicConverter->SetVisAttributes(G4VisAttributes::Invisible);
  
  // Some visualization styles
  G4VisAttributes* VisAtt2= new G4VisAttributes(G4Colour(0.2,0.3,0.8));
  VisAtt2->SetVisibility(true);
  VisAtt2->SetForceSolid(FALSE);

  // Visible Volumes
  logicTKRDetectorX->SetVisAttributes(VisAtt2);
  logicTKRDetectorY->SetVisAttributes(VisAtt2);

  G4cout << "DmpStkDetectorDescription construction completed !!! " << G4endl;
  return;
}

void DmpStkDetectorDescription::SetConverterThickness(G4double val)
{
  ConverterThickness = val;
}  

void DmpStkDetectorDescription::SetThickConverterThickness(G4double val)
{
  ThickConverterThickness = val;
}  

void DmpStkDetectorDescription::SetTKRCenterGap(G4double val)
{
  TKRCenterGap = val;
}  

void DmpStkDetectorDescription::SetTKRSiliconThickness(G4double val)
{
  TKRSiliconThickness = val;
}  

void DmpStkDetectorDescription::SetTKRSiliconPitch(G4double val)
{
  TKRSiliconPitch = val;
}  


void DmpStkDetectorDescription::SetTKRTileSizeXY(G4double val)
{
  TKRSiliconTileXY = val;
}  


void DmpStkDetectorDescription::SetNbOfTKRLayers(G4int val)
{
  NbOfTKRLayers = val;
}


void DmpStkDetectorDescription::SetNbOfTKRTiles(G4int val)
{
  NbOfTKRTiles = val;
}

void DmpStkDetectorDescription::SetTKRLayerDistance(G4double val)
{
  TKRLayerDistance = val;
}

void DmpStkDetectorDescription::SetTKRViewsDistance(G4double val)
{
  TKRViewsDistance = val;
}

void DmpStkDetectorDescription::SetTKRTungstenDistance(G4double val)
{
  TKRTungstenDistance = val;
}

void DmpStkDetectorDescription::ComputeParameters()
{
  // Compute derived parameters of the payload

  //TKRSupportThickness =TKRLayerDistance -2.*TKRSiliconThickness 
  //  - TKRViewsDistance - ConverterThickness;
  TKRSupportThickness =TKRLayerDistance -2.*TKRSiliconThickness - TKRViewsDistance;
  //TKRSizeXY = NbOfTKRTiles*TKRSiliconTileXY + (NbOfTKRTiles+1)*TilesSeparation;
  //TKRBlockXY = NbOfTKRTiles*TKRSiliconTileXY + (NbOfTKRTiles+1)*TilesSeparation;
  TKRBlockXY = NbOfTKRTiles*TKRSiliconTileXY + (NbOfTKRTiles-1)*TilesSeparation;
  TKRWBlockXY = NbOfWTKRTiles*(TKRSiliconTileXY - TKRWRecess) + (NbOfWTKRTiles-1)*TilesSeparation;
  TKRSizeXY = (NbOfTKRBlocks/2)*TKRBlockXY + TKRCenterGap;
  TKRSizeZ = NbOfTKRLayers*TKRLayerDistance; 
  G4cout << "DmpStkDetectorDescription::ComputeParameters: calculated STK size " << G4endl;
  G4cout << "       Sensor size: " << TKRSiliconTileXY << G4endl;
  G4cout << "       Number of sensors: " << NbOfTKRTiles << G4endl;
  G4cout << "       Number of block: " << NbOfTKRBlocks << G4endl;
  G4cout << "       Tile separation: " << TilesSeparation << G4endl;
  G4cout << "       Center gap: " <<  TKRCenterGap << G4endl;
  //G4cout << "       TKR block size =nsen x size + (nsen+1) x sep  = " << TKRBlockXY << G4endl;
  G4cout << "       TKR block size =nsen x size + (nsen-1) x sep  = " << TKRBlockXY << G4endl;
  G4cout << "       TKR size = 2 x block + gap = " << TKRSizeXY << G4endl;
  G4cout << "       TKR W plate size =nsen x (size-recess) + (nsen-1) x sep  = " << TKRWBlockXY << G4endl;

    
  TKRActiveTileXY = TKRSiliconTileXY - 2*SiliconGuardRing;
  TKRActiveTileZ = TKRSiliconThickness;
  if(NbOfTKRStrips != TKRActiveTileXY/TKRSiliconPitch) {
    G4cout << "Warning!!! number of strips per ladder mismatch! " << NbOfTKRStrips << " vs " << TKRActiveTileXY/TKRSiliconPitch << G4endl;
  }

  NbOfTKRStrips = TKRActiveTileXY/TKRSiliconPitch;
  G4cout << "DmpStkDetectorDescription::ComputeParameters: calculated Si sensor parameters " << G4endl;
  G4cout << "       Input GuardRing width: " << SiliconGuardRing << G4endl;
  G4cout << "       Input Pitch width: " << TKRSiliconPitch << G4endl;
  G4cout << "       Active area = sensor_size - 2xGuradRing = " << TKRActiveTileXY << G4endl;
  G4cout << "       Nstrip = Active area/Pitch = " << NbOfTKRStrips << G4endl;

  //SiliconGuardRing = TKRActiveTileXY - NbOfTKRStrips*TKRSiliconPitch;
  SiliconGuardRing = 0.5*(TKRSiliconTileXY - NbOfTKRStrips*TKRSiliconPitch);
  TKRActiveTileXY = TKRSiliconTileXY - 2*SiliconGuardRing;
  G4cout << "       Recaculated GuradRing in case of integer roundup: " << SiliconGuardRing << G4endl;
  G4cout << "       Recaculated TKRActiveTileXY in case of integer roundup: " << TKRActiveTileXY << G4endl;

  TKRXStripX = TKRYStripY = TKRSiliconPitch;
  TKRYStripX = TKRXStripY = TKRActiveTileXY;
  TKRZStrip = TKRSiliconThickness;

}

















