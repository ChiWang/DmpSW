/*
 *  $Id: DmpSimDetectorConstruction.cc, 2014-03-05 16:37:19 chi $
 *  Author(s):
 *    Xin WU (Xin.Wu@cern.cn)   11/07/2013
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#ifdef DmpDebug
#include <iostream>
#endif

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

std::string DmpSimDetectorConstruction::sGdmlPath[DmpCore::gSubDetNo+1]={"default","default","default","default","default"};
float DmpSimDetectorConstruction::sOffset[DmpCore::gSubDetNo+1] = {-33.4, 0, 200, 0, 0};

DmpSimDetectorConstruction::DmpSimDetectorConstruction(){
  for (short i=0;i<DmpCore::gSubDetNo+1;++i){
    fParser[i] = 0;
    new G4GDMLParser();
  }
}

DmpSimDetectorConstruction::~DmpSimDetectorConstruction(){
  for (short i=0;i<DmpCore::gSubDetNo+1;++i){
    if(fParser[i] != 0){
      delete fParser[i];
    }
  }
}

G4VPhysicalVolume* DmpSimDetectorConstruction::Construct(){
  //G4PhysicalVolumeStore::GetInstance()->Clean();
  //G4LogicalVolumeStore::GetInstance()->Clean();
  char *dirTmp = getcwd(NULL,NULL);
  if(sGdmlPath[DmpCore::kWhole] == "default"){
    G4cout<<"Error: must setup detector in job option file. DmpSim.SetGdmlPath(DmpCore.DmpEDetectorID.WhichID,GdmlFilePath)"<<G4endl;
  }else{
    chdir(sGdmlPath[DmpCore::kWhole].c_str());
    fParser[DmpCore::kWhole] = new G4GDMLParser();
    fParser[DmpCore::kWhole]->Read("Sat.gdml");
  }
  fPhysiVol[DmpCore::kWhole] = fParser[DmpCore::kWhole]->GetWorldVolume();
  if(sGdmlPath[DmpCore::kPsd] != "default"){
    chdir(sGdmlPath[DmpCore::kPsd].c_str());
    fParser[DmpCore::kPsd] = new G4GDMLParser();
    fParser[DmpCore::kPsd]->Read("Psd.gdml");
    fPhysiVol[DmpCore::kPsd] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,sOffset[DmpCore::kPsd]),
                    "Psd",
                    fParser[DmpCore::kPsd]->GetVolume("Psd_detector_vol"),
                    fPhysiVol[DmpCore::kWhole],
                    false,
                    0);
  }
  if(sGdmlPath[DmpCore::kStk] != "default"){
    chdir(sGdmlPath[DmpCore::kStk].c_str());
    fParser[DmpCore::kStk] = new G4GDMLParser();
    fParser[DmpCore::kStk]->Read("Stk.gdml");
    fPhysiVol[DmpCore::kStk] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,sOffset[DmpCore::kStk]),
                    "Stk",
                    fParser[DmpCore::kStk]->GetVolume("Stk_detector_vol"),
                    fPhysiVol[DmpCore::kWhole],
                    false,
                    0);
  }
  if(sGdmlPath[DmpCore::kBgo] != "default"){
    chdir(sGdmlPath[DmpCore::kBgo].c_str());
    fParser[DmpCore::kBgo] = new G4GDMLParser();
    fParser[DmpCore::kBgo]->Read("Bgo.gdml");
    fPhysiVol[DmpCore::kBgo] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,sOffset[DmpCore::kBgo]),
                    "Bgo",
                    fParser[DmpCore::kBgo]->GetVolume("Bgo_detector_vol"),
                    fPhysiVol[DmpCore::kWhole],
                    false,
                    0);
  }
  if(sGdmlPath[DmpCore::kNud] != "default"){
    chdir(sGdmlPath[DmpCore::kNud].c_str());
    fParser[DmpCore::kNud] = new G4GDMLParser();
    fParser[DmpCore::kNud]->Read("Nud.gdml");
    fPhysiVol[DmpCore::kNud] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,sOffset[DmpCore::kNud]),
                    "Nud",
                    fParser[DmpCore::kNud]->GetVolume("Nud_detector_vol"),
                    fPhysiVol[DmpCore::kWhole],
                    false,
                    0);
  }
  chdir(dirTmp);

// *
// *  TODO: set SD of SubDet at here
// *
  G4SDManager *mgrSD = G4SDManager::GetSDMpointer();
  if(fParser[DmpCore::kBgo]){
    DmpSimBgoSD *bgoSD = new DmpSimBgoSD("BgoSD");
    mgrSD->AddNewDetector(bgoSD);
    fParser[DmpCore::kBgo]->GetVolume("BGO_bar_vol")->SetSensitiveDetector(bgoSD);
  }

  return fPhysiVol[DmpCore::kWhole];
}

//-------------------------------------------------------------------
void DmpSimDetectorConstruction::SetGdmlPath(DmpCore::DmpEDetectorID id, const std::string &p, float off){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"\t ID = "<<id<<std::endl;
#endif
  sGdmlPath[id] = p;
  sOffset[id] = off;
}

