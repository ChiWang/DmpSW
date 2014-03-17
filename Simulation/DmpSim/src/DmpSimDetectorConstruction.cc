/*
 *  $Id: DmpSimDetectorConstruction.cc, 2014-03-05 16:37:19 chi $
 *  Author(s):
 *    Xin WU (Xin.Wu@cern.cn)   11/07/2013
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
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

std::string DmpSimDetectorConstruction::sGdmlPath[DmpCore::gSubDetNo+1]={"default"};

DmpSimDetectorConstruction::DmpSimDetectorConstruction(){
  for (short i=0;i<DmpCore::gSubDetNo+1;++i){
    fParser[i] = new G4GDMLParser();
  }
}

DmpSimDetectorConstruction::~DmpSimDetectorConstruction(){
  for (short i=0;i<DmpCore::gSubDetNo+1;++i){
    delete fParser[i];
  }
}

//#include "DmpSimDataManager.h"
G4VPhysicalVolume* DmpSimDetectorConstruction::Construct(){
  char *dirTmp = getcwd(NULL,NULL);
// *
// *  TODO:  if could read gdml file of subDetector respectively. use me
// *
  chdir(sGdmlPath[DmpCore::kWhole].c_str());  fParser[DmpCore::kWhole]->Read("Sat.gdml");
  //chdir(sGdmlPath[DmpCore::kPsd]);  fParser[DmpCore::kPsd]->Read("Psd.gdml");
  //chdir(sGdmlPath[DmpCore::kStk]);  fParser[DmpCore::kStk]->Read("Stk.gdml");
  chdir(sGdmlPath[DmpCore::kBgo].c_str());  fParser[DmpCore::kBgo]->Read("Bgo.gdml");
  //chdir(sGdmlPath[DmpCore::kNud]);  fParser[DmpCore::kNud]->Read("Nud.gdml");
  chdir(dirTmp);

// *
// *  TODO: place subDet into satellite
// *
  fPhysiVol[DmpCore::kWhole] = fParser[DmpCore::kWhole]->GetWorldVolume();
  fPhysiVol[DmpCore::kBgo] = new G4PVPlacement(0,
                  G4ThreeVector(),
                  "Bgo",
                  fParser[DmpCore::kBgo]->GetVolume("BGO_detector_vol"),
                  fPhysiVol[DmpCore::kWhole],
                  false,
                  0);

// *
// *  TODO: set SD of SubDet at here
// *
  G4SDManager *MgrSD = G4SDManager::GetSDMpointer();
  DmpSimBgoSD *bgoSD = new DmpSimBgoSD("BgoSD");
  MgrSD->AddNewDetector(bgoSD);
  fParser[DmpCore::kBgo]->GetVolume("BGO_bar_vol")->SetSensitiveDetector(bgoSD);

  return fPhysiVol[DmpCore::kWhole];
}

//-------------------------------------------------------------------
void DmpSimDetectorConstruction::SetGdmlPath(DmpCore::DmpEDetectorID id, std::string p){
  sGdmlPath[id] = p;
}

