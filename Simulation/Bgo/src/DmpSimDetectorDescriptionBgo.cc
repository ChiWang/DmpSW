// Description: This class describes the detector geometry of the DAMPE BGO detector
//
// Author(s):
//  - creation by X.Wu, 13/07/2013

#include "DmpSimDetectorDescriptionBgo.hh"
//#include "DmpBgoDetectorMessenger.hh"
#include "DmpSimSensitiveDetectorBgo.hh"
//#include "DmpBgoROGeometry.hh"

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

DmpSimDetectorDescriptionBgo::DmpSimDetectorDescriptionBgo()
  :solidCALLayerX(0),logicCALLayerX(0),physiCALLayerX(0),
   solidCALLayerY(0),logicCALLayerY(0),physiCALLayerY(0),
   solidCALDetectorX(0),logicCALDetectorX(0),physiCALDetectorX(0),
   solidCALDetectorY(0),logicCALDetectorY(0),physiCALDetectorY(0),
   bgoSensitiveDetector(0),
   aBgoRegion(0)
{
  // default parameter values of the payload
  
  // create commands for interactive definition of the payload
  //bgoDetectorMessenger = new DmpBgoDetectorMessenger(this);

  //DAMPE BGO calorimeter 
  CALBarLength       = 60*cm; 
  CALBarThickness    = 2.5*cm; 
  CALLayerSeparation = 4*mm;
  CALBarsSeparation  = 2.5*mm;
  NbOfCALBars        = 22; 
  NbOfCALLayers      = 7;

}

DmpSimDetectorDescriptionBgo::~DmpSimDetectorDescriptionBgo()
{ 
  //delete bgoDetectorMessenger;
}

void DmpSimDetectorDescriptionBgo::DefineMaterials()
{ 

  G4String name, symbol;    
  G4double a, z, density;            
  G4double temperature, pressure;

  //
  // use G4-NIST materials data base for BGO
  //
  G4NistManager* man = G4NistManager::Instance();
  G4Material* BGO = man->FindOrBuildMaterial("G4_BGO");

  //
  // examples of vacuum
  //  
  density     = universe_mean_density;    //from PhysicalConstants.h
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  G4Material* vacuum = new G4Material(name="Galactic", z=1., a=1.01*g/mole, density,kStateGas,temperature,pressure);

  G4cout << "DmpBgoDetectorDescriotion::DefineMaterials: dump material defined " << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  defaultMaterial  = vacuum;
  CALMaterial = BGO;

}

void DmpSimDetectorDescriptionBgo::Construct(G4VPhysicalVolume* physi, G4LogicalVolume* logi )
{
  physiCAL = physi;
  logicCAL = logi;

  DefineMaterials();


  // Calorimeter Structure (CALLayerX + CALLayerY)
  
  G4double CALLayerThickness = CALBarThickness + CALLayerSeparation; 
  G4cout << "    CAL layer size XY/Z: " << CALSizeXY << "/" << CALLayerThickness << G4endl;
  solidCALLayerX = new G4Box("BGOLayerX", CALSizeXY/2,CALSizeXY/2, CALLayerThickness/2);   
  logicCALLayerX = new G4LogicalVolume(solidCALLayerX, defaultMaterial, "BGOLayerX");	

  solidCALLayerY = new G4Box("BGOLayerY", CALSizeXY/2,CALSizeXY/2, CALLayerThickness/2); 
  logicCALLayerY = new G4LogicalVolume(solidCALLayerY, defaultMaterial, "BGOLayerY");	

  G4cout << "    Adding calorimeter layers ...... " << G4endl;
  G4int i=0;
  for (i = 0; i < NbOfCALLayers; i++)
    {
      
     G4cout << "       Layer " << i << G4endl;
     G4cout << "         Cal y-layer placed at z= " << -CALSizeZ/2+CALLayerThickness/2+(i)*2*CALLayerThickness << G4endl;
     G4cout << "         Cal x-layer placed at z= " << -CALSizeZ/2+CALLayerThickness/2+CALLayerThickness+(i)*2*CALLayerThickness << G4endl;
      physiCALLayerY = 
	new G4PVPlacement(0,G4ThreeVector(0,0,
					  -CALSizeZ/2+
					  CALLayerThickness/2 +
					  (i)*2*CALLayerThickness),
			  "BGOLayerY", logicCALLayerY, physiCAL, false,	i);	
      
      physiCALLayerX = 
	new G4PVPlacement(0,G4ThreeVector(0,0,
					  -CALSizeZ/2+
					  CALLayerThickness/2 + 
					  CALLayerThickness +
					  (i)*2*CALLayerThickness),
			  "BGOLayerX", logicCALLayerX, physiCAL, false,	i);	
      
    }
  
  // Calorimeter Layer Structure (CALDetectorX + CALDetectorY): CALDetectorX means bar direction X, measure Y coordinate
  //                                                            CALDetectorY means bar direction Y, measure X coordinate
  solidCALDetectorX = new G4Box("BGODetectorX",			
				//				CALBarX/2,CALBarY/2,CALBarThickness/2); 
				CALBarLength/2,CALBarThickness/2,CALBarThickness/2); 
  
  logicCALDetectorX = new G4LogicalVolume(solidCALDetectorX, CALMaterial, "BGODetectorX");	
  solidCALDetectorY = new G4Box("BGODetectorY",	CALBarThickness/2,CALBarLength/2,CALBarThickness/2); 
  logicCALDetectorY = new G4LogicalVolume(solidCALDetectorY, CALMaterial, "BGODetectorY");	
  
  for (i = 0; i < NbOfCALBars; i++)
    {
      
      G4cout << "       Placing y-bar " << i << " at x = " << -CALSizeXY/2+ CALBarsSeparation + CALBarThickness/2 + (i)*(CALBarThickness+CALBarsSeparation) << " y = 0 " << G4endl;
      G4cout << "       Placing x-bar " << i << " at x = " << 0 << " y = " << -CALSizeXY/2+ CALBarsSeparation + CALBarThickness/2 + (i)*(CALBarThickness+CALBarsSeparation) << G4endl;
      physiCALDetectorY = 
	new G4PVPlacement(0,
			  G4ThreeVector(-CALSizeXY/2+ CALBarsSeparation + CALBarThickness/2 + (i)*(CALBarThickness+CALBarsSeparation), 0, 0),
			  "BGODetectorY", logicCALDetectorY, physiCALLayerY, false, i);	
      
      physiCALDetectorX = 
	new G4PVPlacement(0,
			  G4ThreeVector(0,-CALSizeXY/2+ CALBarsSeparation + CALBarThickness/2 + (i)*(CALBarThickness+CALBarsSeparation), 0),
			  "BGODetectorX", logicCALDetectorX, physiCALLayerX, false, i);	
      
    }


  // Cuts by Regions, use defult for BGO 
  G4String regName[] = {"Calorimeter"};
  if (aBgoRegion) delete aBgoRegion;

  aBgoRegion = new G4Region(regName[0]);
  logicCAL->SetRegion(aBgoRegion);
  aBgoRegion->AddRootLogicalVolume(logicCAL);
  
  //Sensitive Detector Manager
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if(!bgoSensitiveDetector) {
    bgoSensitiveDetector = new DmpSimSensitiveDetectorBgo("BgoSD");
    SDman->AddNewDetector( bgoSensitiveDetector );		
  }
  if (logicCALDetectorX)
    logicCALDetectorX->SetSensitiveDetector(bgoSensitiveDetector); // BarX
  if (logicCALDetectorY)
    logicCALDetectorY->SetSensitiveDetector(bgoSensitiveDetector); // BarY


  //                                        
  // Visualization attributes
  //

  // Some visualization styles
  G4VisAttributes* VisAtt1= new G4VisAttributes(G4Colour(0.3,0.8,0.1));
  VisAtt1->SetVisibility(true);
  VisAtt1->SetForceSolid(TRUE);

  // Invisible Volume
  
  // Visible Volumes
  logicCALDetectorX->SetVisAttributes(VisAtt1);
  logicCALDetectorY->SetVisAttributes(VisAtt1);

  G4cout << "DmpSimDetectorDescriptionBgo construction completed !!! " << G4endl;
  return;
}

void DmpSimDetectorDescriptionBgo::ComputeParameters()
{
  // Compute derived parameters of the payload
  CALSizeXY = CALBarThickness*NbOfCALBars + (NbOfCALBars+1)*CALBarsSeparation;
  CALSizeZ = 2.*NbOfCALLayers*CALBarThickness + (2.*NbOfCALLayers+1)*CALLayerSeparation;

  CALBarX = CALBarLength;
  CALBarY = CALBarThickness;
  CALBarZ = CALBarThickness;

  G4cout << "DmpSimDetectorDescriptionBgo::ComputeParameters: calculated BGO parameters " << G4endl;
  G4cout << "       caloremeter size XY/Z: " << CALSizeXY << "/" << CALSizeZ << G4endl;
  G4cout << "       number of double layers: " << NbOfCALLayers << "  " << " number of bars per layer: " << NbOfCALBars << G4endl;
  G4cout << "       bar length/width/thickness: "<< CALBarX << "/" << CALBarY << "/" << CALBarZ << G4endl;
  G4cout << "       separation between layerss: "<<  CALBarsSeparation << G4endl;
  G4cout << "       separation between bars:    "<<  CALLayerSeparation << G4endl;

}

















