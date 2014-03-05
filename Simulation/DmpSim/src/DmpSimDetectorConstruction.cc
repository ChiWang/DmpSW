/*
 *  $Id: DmpSimDetectorConstruction.cc, 2014-03-03 23:05:51 chi $
 *  Author(s):
 *    Xin WU (Xin.Wu@cern.cn)   11/07/2013
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#include <stdlib.h>     // getenv()

#include "G4GDMLParser.hh"
#include "G4SDManager.hh"

// *
// *  TODO: add SD of Psd, Stk and Nud
// *
#include "DmpSimDetectorConstruction.h"
//#include "DmpSimPsdSD.h"
//#include "DmpSimStkSD.h"
#include "DmpSimBgoSD.h"
//#include "DmpSimNudSD.h"

DmpSimDetectorConstruction::DmpSimDetectorConstruction()
  :fPhysiWorld(0)
{
	// create commands for interactive definition of the payload
  fParser = new G4GDMLParser();
}

DmpSimDetectorConstruction::~DmpSimDetectorConstruction(){
  delete fParser;
}

G4VPhysicalVolume* DmpSimDetectorConstruction::Construct(){
#ifdef DmpDebug
  fParser->Read("../Geometry/DAMPE.gdml");
#else
  G4String file = (G4String)getenv("DMPSWSYS")+"/share/Geometry/DAMPE.gdml";
  fParser->Read(file);
#endif
  fPhysiWorld = fParser->GetWorldVolume();

// *
// *  TODO: set SD of SubDet at here
// *
  G4SDManager *SDMan = G4SDManager::GetSDMpointer();
//  SDMan->AddNewDetector(new DmpSimPsdSD("/DmpDet/Psd"));
//  SDMan->AddNewDetector(new DmpSimStkSD("/DmpDet/Stk"));
  SDMan->AddNewDetector(new DmpSimBgoSD("/DmpDet/Bgo"));
//  SDMan->AddNewDetector(new DmpSimNudSD("/DmpDet/Nud"));

  return fPhysiWorld;
}

/*
#include "G4RunManager.hh"
#include "G4RegionStore.hh"
void DmpSimDetectorConstruction::UpdateGeometry(){
  //  delete payloadSD??
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
  G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  G4RegionStore::GetInstance()->UpdateMaterialList(fPhysiWorld);
}
*/

