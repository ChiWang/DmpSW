// Description: This class describes the detector geometry of the DAMPE PSD detector
//
// Author(s):
//  - creation by X.Wu, 13/07/2013

#include "DmpSimDetectorDescriptionPsd.hh"
//#include "DmpPsdDetectorMessenger.hh"
#include "DmpSimSensitiveDetectorPsd.hh"
//#include "DmpPsdROGeometry.hh"

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

DmpSimDetectorDescriptionPsd::DmpSimDetectorDescriptionPsd()
  :solidPSD(0),logicPSD(0),physiPSD(0),
   solidPSDDetector(0),logicPSDDetector(0),physiPSDDetector(0),
   psdSensitiveDetector(0),
   aPsdRegion(0)
{
  // default parameter values of the payload
  
  // create commands for interactive definition of the payload
  //psdDetectorMessenger = new DmpPsdDetectorMessenger(this);

  //DAMPE PSD 
  PSDThickness        = 1.*cm;
  NbOfPSDStrips       = 1;

}

DmpSimDetectorDescriptionPsd::~DmpSimDetectorDescriptionPsd()
{ 
  //delete psdDetectorMessenger;
}

void DmpSimDetectorDescriptionPsd::DefineMaterials()
{ 

  G4String name, symbol;    
  G4double a, z, density;            
  
  G4int ncomponents, natoms;
  G4double temperature, pressure;

  //
  // define Elements
  //
  
  a = 1.01*g/mole;
  G4Element* H  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);
  
  a = 12.01*g/mole;
  G4Element* C  = new G4Element(name="Carbon"  ,symbol="C" , z= 6., a);

  density = 1.032*g/cm3;
  G4Material* Sci = new G4Material(name="Scintillator", density, ncomponents=2);
  Sci->AddElement(C, natoms=9);
  Sci->AddElement(H, natoms=10);

  //
  // examples of vacuum
  //  
  density     = universe_mean_density;    //from PhysicalConstants.h
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  G4Material* vacuum = new G4Material(name="Galactic", z=1., a=1.01*g/mole, density,kStateGas,temperature,pressure);

  G4cout << "DmpPsdDetectorDescriotion::DefineMaterials: dump material defined " << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  defaultMaterial  = vacuum;
  PSDMaterial = Sci;

}

void DmpSimDetectorDescriptionPsd::Construct(G4VPhysicalVolume* physi, G4LogicalVolume* logi )
{
  physiPSD = physi;
  logicPSD = logi;
  
  DefineMaterials();
  solidPSDDetector = new G4Box("PSD", PSDSizeXY/2, PSDSizeXY/2, PSDSizeZ/2); 
  logicPSDDetector = new G4LogicalVolume(solidPSDDetector, PSDMaterial, "PSDDetector");
  physiPSDDetector = new G4PVPlacement(0, G4ThreeVector(0,0,0), "PSD", logicPSDDetector, physiPSD, false, 0);	
  
  // Cuts by Regions, use defult for PSD 
  G4String regName[] = {"PSD"};
  if (aPsdRegion) delete aPsdRegion;

  aPsdRegion = new G4Region(regName[0]);
  logicPSD->SetRegion(aPsdRegion);
  aPsdRegion->AddRootLogicalVolume(logicPSD);
  
  //Sensitive Detector Manager
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if(!psdSensitiveDetector) {
    psdSensitiveDetector = new DmpSimSensitiveDetectorPsd("PsdSD");
    SDman->AddNewDetector( psdSensitiveDetector );		
   }
  if (logicPSDDetector)
    logicPSDDetector->SetSensitiveDetector(psdSensitiveDetector); // PSD

  //                                        
  // Visualization attributes
  //

  // Some visualization styles
  G4VisAttributes* VisAtt3= new G4VisAttributes(G4Colour(0.8,0.2,0.3));
  VisAtt3->SetVisibility(true);
  VisAtt3->SetForceWireframe(TRUE);
  
  // Visible Volumes
  logicPSDDetector->SetVisAttributes(VisAtt3);  

  G4cout << "DmpSimDetectorDescriptionPsd construction completed !!! " << G4endl;
  return;
}

void DmpSimDetectorDescriptionPsd::ComputeParameters()
{
  // Compute derived parameters of the payload
  PSDSizeXY = 90*cm; //DAMPE
  PSDSizeZ = 2*PSDThickness;//DAMPE
  G4cout << "DmpSimDetectorDescriptionPsd::ComputeParameters: calculated PSD parameters " << G4endl;
  G4cout << "       PSD size XY/Z: " << PSDSizeXY << "/" << PSDSizeZ << G4endl;

}

















