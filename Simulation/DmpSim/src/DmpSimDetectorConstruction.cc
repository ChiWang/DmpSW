// Description: This class hinerits from G4VUserDetectorConstruction. It is used to
// manage the detector geometry description of the DAMPE detector
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpSimDetectorConstruction.hh"
#include "DmpSimDetectorMessenger.hh"

#include "DmpSimDetectorDescriptionPsd.hh"
#include "DmpSimDetectorDescriptionStk.hh"
#include "DmpSimDetectorDescriptionBgo.hh"

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

DmpSimDetectorConstruction::DmpSimDetectorConstruction()
  :solidWorld(0),logicWorld(0),physiWorld(0),
   solidPayload(0),logicPayload(0),physiPayload(0),
   solidPSD(0),logicPSD(0),physiPSD(0),
   solidSTK(0),logicSTK(0),physiSTK(0),
   solidBGO(0),logicBGO(0),physiBGO(0)
{
  PSDSTKDistance = 3.*cm; //distance from the top of the first support plane 
  BGOSTKDistance = 5.*cm; //distance from the bottom silicon active layer, 47mm(+/- 5mm). 

  // create commands for interactive definition of the payload
  detectorMessenger = new DmpSimDetectorMessenger(this);

  dmpPsdDetectorDescription = new DmpSimDetectorDescriptionPsd();
  dmpStkDetectorDescription = new DmpSimDetectorDescriptionStk();
  dmpBgoDetectorDescription = new DmpSimDetectorDescriptionBgo();

}

DmpSimDetectorConstruction::~DmpSimDetectorConstruction()
{ 
  delete detectorMessenger;
}

G4VPhysicalVolume* DmpSimDetectorConstruction::Construct()
{
  DefineMaterials();
  return ConstructPayload();
}

void DmpSimDetectorConstruction::DefineMaterials()
{ 
  
  G4String name, symbol;    
  G4double a, z, density;            
  G4double temperature, pressure;

  //
  // examples of vacuum
  //  
  density     = universe_mean_density;    //from PhysicalConstants.h
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  G4Material* vacuum = new G4Material(name="Galactic", z=1., a=1.01*g/mole, density,kStateGas,temperature,pressure);

  G4cout << "DmpSimDetectorConstruction::DefineMaterials: dump material defined " << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  
  //default materials of the payload
  defaultMaterial  = vacuum;
}

G4VPhysicalVolume* DmpSimDetectorConstruction::ConstructPayload()
{
  // get the parameters of PSD, STK, BGO, NUD
  dmpPsdDetectorDescription->ComputeParameters();
  dmpStkDetectorDescription->ComputeParameters();
  dmpBgoDetectorDescription->ComputeParameters();
  
  PSDSizeZ  = dmpPsdDetectorDescription->GetSizeZ();
  PSDSizeXY = dmpPsdDetectorDescription->GetSizeXY();

  STKSizeZ  = dmpStkDetectorDescription->GetSizeZ();
  STKSizeXY = dmpStkDetectorDescription->GetSizeXY();
  
  BGOSizeZ  = dmpBgoDetectorDescription->GetSizeZ();
  BGOSizeXY = dmpBgoDetectorDescription->GetSizeXY();
  
  // compute the global definitions: World, Payload, PSD, STK, BGO, NUD
  PayloadSizeZ = 1.1*(STKSizeZ + BGOSizeZ + PSDSTKDistance + BGOSTKDistance + PSDSizeZ);
  PayloadSizeXY = (PSDSizeXY);
  G4cout << "DmpSimDetectorConstruction: calculated Payload size " << G4endl;
  G4cout << "       Payload size XY = PSDSizeXY: "  << PayloadSizeXY << G4endl;
  G4cout << "       Payload size Z  = 1.1*(STKSizeZ + BGOSizeZ + PSDSTKDistance + BGOSTKDistance+PSDSizeXY): " << PayloadSizeZ << G4endl;
  
  WorldSizeZ = 1.5*PayloadSizeZ; WorldSizeXY = 1.5*PayloadSizeXY;

  PSDCenter =  -PayloadSizeZ/2+BGOSizeZ+BGOSTKDistance+STKSizeZ+PSDSTKDistance+PSDSizeZ/2;
  STKCenter = -PayloadSizeZ/2+BGOSizeZ+BGOSTKDistance+STKSizeZ/2;
  BGOCenter = -PayloadSizeZ/2+BGOSizeZ/2;

  //     
  // World
  //
  solidWorld = new G4Box("World", WorldSizeXY/2,WorldSizeXY/2,WorldSizeZ/2);  
  logicWorld = new G4LogicalVolume(solidWorld, defaultMaterial, "World");		
  physiWorld = new G4PVPlacement(0,G4ThreeVector(),"World",logicWorld, 0,false,0);
			
  //
  // Payload
  //
  solidPayload = new G4Box("Payload", PayloadSizeXY/2, PayloadSizeXY/2, PayloadSizeZ/2);
  logicPayload = new G4LogicalVolume(solidPayload, defaultMaterial, "Payload");  
  physiPayload = new G4PVPlacement(0, G4ThreeVector(), "Payload", logicPayload, physiWorld, false, 0);		

  G4cout << "    world size XY/Z: " << WorldSizeXY << "/" << WorldSizeZ << G4endl;
  G4cout << "    payload size XY/Z: " << PayloadSizeXY << "/" << PayloadSizeZ  << G4endl;
  G4cout << "             from z =  " << -PayloadSizeZ/2 << " to " << PayloadSizeZ/2  << G4endl;

  G4cout << " Placing detector ... " << G4endl;
  //                               
  // PSD
  //
  solidPSD = new G4Box("PSD", PSDSizeXY/2, PSDSizeXY/2, PSDSizeZ/2); 
  logicPSD = new G4LogicalVolume(solidPSD,defaultMaterial,"PSD"); 
  physiPSD = new G4PVPlacement(0, G4ThreeVector(0,0,PSDCenter), "PSD", logicPSD, physiPayload, false, 0);	

  //                                 
  // Tracker (STK)
  //  
  solidSTK = new G4Box("STK", STKSizeXY/2, STKSizeXY/2, STKSizeZ/2); 
  logicSTK = new G4LogicalVolume(solidSTK, defaultMaterial, "STK");	
  physiSTK = new G4PVPlacement(0, G4ThreeVector(0,0,STKCenter), "STK", logicSTK, physiPayload, false, 0);	

  //                                 
  // Calorimeter (BGO)
  // 
  solidBGO = new G4Box("BGO", BGOSizeXY/2, BGOSizeXY/2, BGOSizeZ/2); 
  logicBGO = new G4LogicalVolume(solidBGO, defaultMaterial, "BGO");	
  physiBGO = new G4PVPlacement(0, G4ThreeVector(0,0,BGOCenter), "BGO", logicBGO, physiPayload, false, 0);	


  G4cout << "    PSD size XY/Z: " << PSDSizeXY << "/" << PSDSizeZ << " placed at z= "<< PSDCenter << G4endl;
  G4cout << "         from z =  " << PSDCenter-PSDSizeZ/2<< " to " <<  PSDCenter+PSDSizeZ/2  << G4endl;
  G4cout << "         distance between PSD and tracker: " << PSDSTKDistance << G4endl;

  G4cout << "    STK size XY: " << STKSizeXY<< " placed at xy= "<< 0;
  G4cout << ";   from XY =  "   <<  -STKSizeXY/2 << " to " <<  STKSizeXY/2 << G4endl;
  G4cout << "    STK size  Z: " << STKSizeZ << " placed at z= "<< STKCenter;
  G4cout << ";   from z =  "    << STKCenter-STKSizeZ/2 << " to " <<  STKCenter+STKSizeZ/2  << G4endl;
  G4cout << "         distance between tracker and Cal: " << BGOSTKDistance << G4endl;
   
  G4cout << "    BGO size XY/Z: " << BGOSizeXY << "/" << BGOSizeZ << " placed at z= "<< BGOCenter << G4endl;
  G4cout << "         from z =  " << BGOCenter-BGOSizeZ/2 << " to " << BGOCenter+BGOSizeZ/2  << G4endl;

  //construct sub-detectors
  dmpStkDetectorDescription->Construct(STKCenter, physiSTK, logicSTK);
  dmpBgoDetectorDescription->Construct(physiBGO, logicBGO);
  dmpPsdDetectorDescription->Construct(physiPSD, logicPSD);

  //                                        
  // Visualization attributes
  //
  
  // Invisible Volume
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  logicPayload->SetVisAttributes (G4VisAttributes::Invisible);
  logicSTK->SetVisAttributes(G4VisAttributes::Invisible);  
  
  //
  //always return the physical World
  //
  return physiWorld;
}

void DmpSimDetectorConstruction::UpdateGeometry()
{
  //  delete payloadSD;
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructPayload());
  G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  G4RegionStore::GetInstance()->UpdateMaterialList(physiWorld);

}

void DmpSimDetectorConstruction::ComputePayloadParameters()
{
  // now not used
}

















