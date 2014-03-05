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

#include <assert.h>
#include "G4VisAttributes.hh"

#define STKRO_NAME_PREFIX             ""   //"STKRO_"


DmpStkROGeometry::DmpStkROGeometry()
  : G4VReadOutGeometry()
{
}
DmpStkROGeometry::DmpStkROGeometry(G4String aString, G4GDMLParser* aParser)
  :G4VReadOutGeometry(aString)
{
	fParser = aParser;
	G4RunManager* runManager = G4RunManager::GetRunManager();
	dmpDetector =(DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

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
  


  /*
   *   Builds the ReadOut World:
   */

  G4double WorldSizeXY = dmpDetector->GetWorldSizeXY();
  G4double WorldSizeZ  = dmpDetector->GetWorldSizeZ();
  
  G4Box* ROWorldBox = new 
    G4Box("ROWorldBox",WorldSizeXY/2,WorldSizeXY/2,WorldSizeZ/2); 
  
  G4LogicalVolume* ROWorldLog = new G4LogicalVolume(ROWorldBox, dummyMat,
						    "STKRO_World_logical");

  G4PVPlacement* ROWorldPhys = 
    new G4PVPlacement(
            0,
            G4ThreeVector(),
            "STKRO_World_physical",
            ROWorldLog,
            //fParser->GetWorldVolume(),
            0,  // To visualize readout geometry, replace "0" with fParser->GetWorldVolume(),
            false,
            0);
  


  /*
   *   Builds readout STK
   */
  G4VPhysicalVolume* physSTK = 0;
  for(G4int i=0; i<fParser->GetWorldVolume()->GetLogicalVolume()->GetNoDaughters();i++){
	  G4VPhysicalVolume* physVol = fParser->GetWorldVolume()->GetLogicalVolume()->GetDaughter(i);
	  //G4cout<< "physVol->GetName()"<<physVol->GetName()<<G4endl;
	  if(physVol->GetName()!= dmpDetector->GetStkDetectorDescription()->GetPhysSTKVolumeNameGDML()) continue;
	  physSTK = physVol;
  }
  if(!physSTK){
	  G4cerr<<"ERROR [DmpStkROGeometry::Build]: unable to find STK physical volume"<<G4endl;
	  throw;
  }
  G4LogicalVolume* logSTKRO = new G4LogicalVolume(physSTK->GetLogicalVolume()->GetSolid(), dummyMat, G4String(STKRO_NAME_PREFIX)+"STK_logical" );
  G4PVPlacement* physSTKRO = new G4PVPlacement(
          physSTK->GetRotation(),
		  physSTK->GetTranslation(),
		  G4String(STKRO_NAME_PREFIX)+"STK_physical",
		  logSTKRO,
		  ROWorldPhys,
		  false,
		  0);


  /*
   *   Readout silicon mother volume
   */
  G4VPhysicalVolume* physSiSTK = 0;
  for(G4int i=0; i<physSTK->GetLogicalVolume()->GetNoDaughters();i++){
        G4VPhysicalVolume* physVol = physSTK->GetLogicalVolume()->GetDaughter(i);
        if(physVol->GetName()!= dmpDetector->GetStkDetectorDescription()->GetPhysSTKSiMotherVolumeNameGDML()) continue;
        physSiSTK = physVol;
  }
  if(!physSiSTK){
      G4cerr<<"ERROR [DmpStkROGeometry::Build]: unable to find Silicon Mother physical volume"<<G4endl;
      throw;
  }
  G4LogicalVolume* logSTKSiRO = new G4LogicalVolume(physSiSTK->GetLogicalVolume()->GetSolid(), dummyMat, G4String(STKRO_NAME_PREFIX)+"stk-si_logical" );
  G4PVPlacement* physSTKSiRO = new G4PVPlacement(
          physSiSTK->GetRotation(),
          physSiSTK->GetTranslation(),
          G4String(STKRO_NAME_PREFIX)+"stk-si_physical",
          logSTKSiRO,
          physSTKRO,
          false,
          0);


  /*
   *  Readout silicon tiles
   */
  G4double SiliconGuardRing = dmpDetector->GetStkDetectorDescription()->GetSiliconGuardRing();
  bool siliconTileFound = false;
  for(G4int i=0; i<physSiSTK->GetLogicalVolume()->GetNoDaughters();i++){
      G4VPhysicalVolume* physVol = physSiSTK->GetLogicalVolume()->GetDaughter(i);
      if(
              !(dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTileX(physVol->GetName()))&&
              !(dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTileY(physVol->GetName()))
              ){
          continue;
      }
      siliconTileFound = true;
      G4double Xmax = ((G4TessellatedSolid*)(physVol->GetLogicalVolume()->GetSolid()))->GetMaxXExtent();
      G4double Xmin = ((G4TessellatedSolid*)(physVol->GetLogicalVolume()->GetSolid()))->GetMinXExtent();
      G4double Ymax = ((G4TessellatedSolid*)(physVol->GetLogicalVolume()->GetSolid()))->GetMaxYExtent();
      G4double Ymin = ((G4TessellatedSolid*)(physVol->GetLogicalVolume()->GetSolid()))->GetMinYExtent();
      G4double Zmax = ((G4TessellatedSolid*)(physVol->GetLogicalVolume()->GetSolid()))->GetMaxZExtent();
      G4double Zmin = ((G4TessellatedSolid*)(physVol->GetLogicalVolume()->GetSolid()))->GetMinZExtent();

      Xmax-=SiliconGuardRing;
      Xmin+=SiliconGuardRing;
      Ymax-=SiliconGuardRing;
      Ymin+=SiliconGuardRing;

      G4Box* solidActiveTile = new G4Box("ActiveTileBox", (Xmax - Xmin)/2, (Ymax - Ymin)/2, (Zmax - Zmin)/2);
      G4LogicalVolume* logActiveTile = new G4LogicalVolume(solidActiveTile, dummyMat, G4String(STKRO_NAME_PREFIX)+physVol->GetLogicalVolume()->GetName());
      //G4ThreeVector placementActiveTile(physVol->GetTranslation().x + (Xmax+Xmin)/2, physVol->GetTranslation().y+ (Ymax+Ymin)/2, physVol->GetTranslation().z+ (Zmax+Zmin)/2);
      G4ThreeVector placementActiveTile((Xmax+Xmin)/2, (Ymax+Ymin)/2, (Zmax+Zmin)/2);
      G4PVPlacement* physActiveTileX = new G4PVPlacement(
              0,
              placementActiveTile,
              logActiveTile->GetName()+"_physical",
              logActiveTile,
              physSTKSiRO,
              false,
              0);
  }
  if(!siliconTileFound){
      G4cerr<<"ERROR [DmpStkROGeometry::Build]: unable to find any single silicon tile"<<G4endl;
      throw;
  }


  /*
   *  Readout silicon strips
   */
  G4double TKRActiveTileXY =  dmpDetector->GetStkDetectorDescription()->GetTKRActiveTileXY();
  G4double TKRActiveTileZ  =  dmpDetector->GetStkDetectorDescription()->GetTKRActiveTileZ();

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

  G4VSolid* solidTKRStripX = new G4Box("StripX", TKRXStripX/2,TKRYStripX/2, TKRZStrip/2);
  G4LogicalVolume* logicTKRStripX = new G4LogicalVolume(solidTKRStripX,dummyMat,"StripX",0,0,0);

  G4VSolid* solidTKRStripY = new G4Box("StripY", TKRXStripY/2,TKRYStripY/2, TKRZStrip/2);
  G4LogicalVolume* logicTKRStripY = new G4LogicalVolume(solidTKRStripY,dummyMat,"StripY",0,0,0);

  G4double TKRSiliconPitch = dmpDetector->GetStkDetectorDescription()->GetTKRSiliconPitch();

  //logicTKRStripX->SetVisAttributes(G4VisAttributes::Invisible);
  //logicTKRStripY->SetVisAttributes(G4VisAttributes::Invisible);


  // Place silicon strips
  for(G4int silicon_i=0; silicon_i<physSTKSiRO->GetLogicalVolume()->GetNoDaughters();silicon_i++){
      G4VPhysicalVolume* tile = physSTKSiRO->GetLogicalVolume()->GetDaughter(silicon_i);
      if (dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTileX(tile->GetName()))
      {
          for (G4int i=0;i< NbOfTKRStrips; i++) new G4PVPlacement(
                  0,
                  G4ThreeVector(-TKRActiveTileXY/2 +TKRSiliconPitch/2 +(i)*TKRSiliconPitch, 0., 0.),
                  //tile->GetLogicalVolume()->GetName() + "_StripX", //  + G4UIcommand::ConvertToString(i)+"_physical",
                  "StripX",
                  logicTKRStripX,
                  tile,
                  false,
                  i);
          //G4cout<<i<<G4endl;
          //}
          //G4cout<<"tile->GetName() : "<<tile->GetName()<<G4endl;
          //break;
      }
      else if (dmpDetector->GetStkDetectorDescription()->isVolumeSTKActiveTileY(tile->GetName()))
      {
          for (G4int i=0;i< NbOfTKRStrips; i++) new G4PVPlacement(
                  0,
                  //G4ThreeVector(0.,TKRActiveTileXY/2 -TKRSiliconPitch/2 - (i)*TKRSiliconPitch, 0.),  //<-- use it for new coordinate system?
                  G4ThreeVector(0.,-TKRActiveTileXY/2 +TKRSiliconPitch/2 + (i)*TKRSiliconPitch, 0.),  //<-- as in the old-style geometry
                  //tile->GetLogicalVolume()->GetName() + "_StripY", //+ G4UIcommand::ConvertToString(i)+"_physical",
                  "StripY",
                  logicTKRStripY,
                  tile,
                  false,
                  i);
          //G4cout<<i<<G4endl;
          //}
          //G4cout<<"tile->GetName() : "<<tile->GetName()<<G4endl;
          //break;

      }

      else
      {
          G4cerr<<"ERROR [DmpStkROGeometry::Build]: internal cross-check failed!"<<G4endl;
          throw;
      }
  }

  //Flags the strip as sensitive .The pointer here serves
  // as a flag only to check for sensitivity.
  // (Could we make it by a simple cast of a non-NULL value ?)

  DmpStkDummySD * dummySensi = new DmpStkDummySD("Orpo");
  logicTKRStripX->SetSensitiveDetector(dummySensi);
  logicTKRStripY->SetSensitiveDetector(dummySensi);


  /*
   *   Return STK readout  geometry
   */
  return ROWorldPhys;
}










