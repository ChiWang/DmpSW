// Description: This class hinerits from G4VUserDetectorConstruction. It is used to
// manage the detector geometry description of the DAMPE detector
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpDetectorConstruction.hh"
#include "DmpDetectorMessenger.hh"

#include "DmpPsdDetectorDescription.hh"
#include "DmpStkDetectorDescription.hh"
#include "DmpBgoDetectorDescription.hh"

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




#define PSD_POSITION_GDML_NAME  "psd_z_offset"
#define STK_POSITION_GDML_NAME  "stk_z_offset"
#define BGO_POSITION_GDML_NAME  "bgo_z_offset"
#define WORLD_SIZE_Z_GDML_NAME  "world_size"
#define WORLD_SIZE_XY_GDML_NAME "world_size"


DmpDetectorConstruction::DmpDetectorConstruction()
  :solidWorld(0),logicWorld(0),physiWorld(0),
   //solidHalfPosWorld(0),logicHalfPosWorld(0),physiHalfPosWorld(0),
   //solidHalfNegWorld(0),logicHalfNegWorld(0),physiHalfNegWorld(0),
   solidPayload(0),logicPayload(0),physiPayload(0),
   solidPSD(0),logicPSD(0),physiPSD(0),
   solidSTK(0),logicSTK(0),physiSTK(0),
   solidBGO(0),logicBGO(0),physiBGO(0)
{

	// create commands for interactive definition of the payload
  detectorMessenger = new DmpDetectorMessenger(this);
}

DmpDetectorConstruction::~DmpDetectorConstruction()
{ 
  delete detectorMessenger;
}

G4VPhysicalVolume* DmpDetectorConstruction::Construct()
{
	/*
	 * Construct detector from GDML description
	 */
	return ConstructGDML();
}

G4VPhysicalVolume* DmpDetectorConstruction::ConstructGDML(){
	/*   Switch to top working directory, where Geometry folder resides 	 */
    chdir("../../../");//from ./Simulation/DmpSim/test TO ./

	/*   Construct geometry 	 */
	fParser = new G4GDMLParser();
	fParser->Read("./Geometry/DAMPE.gdml");

	/*   Parse GDML information for subdetectors  */
    dmpPsdDetectorDescription = new DmpPsdDetectorDescription(fParser);
	dmpStkDetectorDescription = new DmpStkDetectorDescription(fParser);
	dmpBgoDetectorDescription = new DmpBgoDetectorDescription(fParser);

	/*   Compute payload parameters	 */
	ComputePayloadParameters();

	/*   Once the tracking geometry is defined, build parallel eradout geometries  */
    dmpPsdDetectorDescription->defineSensitiveDetector(); // ?
	dmpStkDetectorDescription->defineSensitiveDetector();
	dmpBgoDetectorDescription->defineSensitiveDetector(); // ?

	/*   Switch back to current working directory	 */
	chdir("./Simulation/DmpSim/test");

    /*   Return world volume     */
	physiWorld = fParser->GetWorldVolume();
	return physiWorld;
}


void DmpDetectorConstruction::UpdateGeometry()
{
  //  delete payloadSD;
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructGDML());
  G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  G4RegionStore::GetInstance()->UpdateMaterialList(physiWorld);

}

void DmpDetectorConstruction::ComputePayloadParameters()
{
	// get the parameters of PSD, STK, BGO, NUD
	dmpPsdDetectorDescription->ComputeParameters();
	//dmpStkDetectorDescription->ComputeParameters();
	dmpBgoDetectorDescription->ComputeParameters();

	PSDSizeZ  = dmpPsdDetectorDescription->GetSizeZ();
	PSDSizeXY = dmpPsdDetectorDescription->GetSizeXY();

	STKSizeZ  = dmpStkDetectorDescription->GetSizeZ();
	STKSizeXY = dmpStkDetectorDescription->GetSizeXY();

	BGOSizeZ  = dmpBgoDetectorDescription->GetSizeZ();
	BGOSizeXY = dmpBgoDetectorDescription->GetSizeXY();

	PSDCenter = fParser->GetConstant(PSD_POSITION_GDML_NAME)*mm;
	STKCenter = fParser->GetConstant(STK_POSITION_GDML_NAME)*mm;
	BGOCenter = fParser->GetConstant(BGO_POSITION_GDML_NAME)*mm;
	// compute the global definitions: World, Payload, PSD, STK, BGO, NUD

	//PayloadSizeZ = 1.1*(STKSizeZ + BGOSizeZ + PSDSTKDistance + BGOSTKDistance + PSDSizeZ);
	PayloadSizeZ = 1.1 * ((fParser->GetConstant(BGO_POSITION_GDML_NAME)*mm + BGOSizeZ/2) - (fParser->GetConstant(PSD_POSITION_GDML_NAME)*mm -PSDSizeZ/2));
	PayloadSizeXY = (PSDSizeXY);

	// World
	WorldSizeZ  = fParser->GetConstant(WORLD_SIZE_Z_GDML_NAME) *mm;
	WorldSizeXY = fParser->GetConstant(WORLD_SIZE_XY_GDML_NAME)*mm;



	G4cout << "DmpDetectorConstruction: calculated Payload size " << G4endl;
	G4cout << "       Payload size XY = PSDSizeXY: "  << PayloadSizeXY << G4endl;
	G4cout << "       PayloadSizeZ = "<<PayloadSizeZ<<"\n";
	G4cout << "       BGOSizeZ = "<<BGOSizeZ<<"\n";
	G4cout << "       BGO size XY/Z: " << BGOSizeXY << "/" << BGOSizeZ << " placed at z= "<< BGOCenter << G4endl;
	G4cout << "       BGOCenter = "<<BGOCenter<<"\n";
	G4cout << "       PSDSizeZ = "<<PSDSizeZ<<"\n";
	G4cout << "       PSD size XY/Z: " << PSDSizeXY << "/" << PSDSizeZ << " placed at z= "<< PSDCenter << G4endl;
	G4cout << "       PSDCenter = "<<PSDCenter<<"\n";
	G4cout << "       STKSizeZ = "<<STKSizeZ<<"\n";
	G4cout << "       STK size XY: " << STKSizeXY<< G4endl;
	G4cout << "       STKCenter = "<<STKCenter<<"\n";
	G4cout << "       world size XY/Z: " << WorldSizeXY << "/" << WorldSizeZ << G4endl;

}

















