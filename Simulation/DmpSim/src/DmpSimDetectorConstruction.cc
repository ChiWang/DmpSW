/*
 *  $Id: DmpSimDetectorConstruction.cc, 2014-03-05 16:37:19 chi $
 *  Author(s):
 *    Xin WU (Xin.Wu@cern.cn)   11/07/2013
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#include <stdlib.h>     // getenv() chdir()

#include "G4LogicalVolume.hh"
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

DmpSimDetectorConstruction::DmpSimDetectorConstruction(){
  fParser = new G4GDMLParser();
}

DmpSimDetectorConstruction::~DmpSimDetectorConstruction(){
  delete fParser;
}

G4VPhysicalVolume* DmpSimDetectorConstruction::Construct(){
  char *dirTmp = getcwd(NULL,NULL);
  chdir(getenv("DMPSWSYS"));    chdir("./share/Geometry");
 //*  TODO: add this for BT2012     chdir("BT2012");
  fParser->Read("DAMPE.gdml");
  chdir(dirTmp);

// *
// *  TODO: set SD of SubDet at here
// *
  G4SDManager *SDMan = G4SDManager::GetSDMpointer();
//  SDMan->AddNewDetector(new DmpSimPsdSD("/DmpDet/Psd"));
//  SDMan->AddNewDetector(new DmpSimStkSD("/DmpDet/Stk"));
  SDMan->AddNewDetector(new DmpSimBgoSD("/DmpDet/Bgo"));
 //*  TODO: add evry crystal as SD
  //G4LogicalVolume *bgoCrystal = fParser->GetXXX()->GetLogicalVolume();
  //bgoCrystal->SetSensitiveDetector(aTrackerSD);
//  SDMan->AddNewDetector(new DmpSimNudSD("/DmpDet/Nud"));

  return fParser->GetWorldVolume();
}

