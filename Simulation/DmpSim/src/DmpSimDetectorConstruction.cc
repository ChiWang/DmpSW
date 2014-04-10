/*
 *  $Id: DmpSimDetectorConstruction.cc, 2014-04-10 21:12:21 chi $
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
#include "DmpSimSvcOption.h"
//#include "DmpSimPsdSD.h"
//#include "DmpSimStkSD.h"
#include "DmpSimBgoSD.h"
//#include "DmpSimNudSD.h"


//-------------------------------------------------------------------
DmpSimDetectorConstruction::DmpSimDetectorConstruction(){
  for (short i=0;i<DmpDetector::gSubDetNo+1;++i){
    fParser[i] = 0;
  }
}

//-------------------------------------------------------------------
DmpSimDetectorConstruction::~DmpSimDetectorConstruction(){
  for (short i=0;i<DmpDetector::gSubDetNo+1;++i){
    if(fParser[i] != 0){
      delete fParser[i];
    }
  }
}

//-------------------------------------------------------------------
G4VPhysicalVolume* DmpSimDetectorConstruction::Construct(){
  char *dirTmp = getcwd(NULL,NULL);
  if(gSimOpt->GetGdmlPath(DmpDetector::kWhole) == "default"){
    G4cout<<"Error: must setup detector in job option file. DmpSim.SetGdmlPath(DmpDetector.DmpEDetectorID.WhichID,GdmlFilePath)"<<G4endl;
  }else{
    chdir(gSimOpt->GetGdmlPath(DmpDetector::kWhole).c_str());
    fParser[DmpDetector::kWhole] = new G4GDMLParser();
    fParser[DmpDetector::kWhole]->Read("Sat.gdml");
  }
  fPhysiVol[DmpDetector::kWhole] = fParser[DmpDetector::kWhole]->GetWorldVolume();
  if(gSimOpt->GetGdmlPath(DmpDetector::kPsd) != "default"){
    chdir(gSimOpt->GetGdmlPath(DmpDetector::kPsd).c_str());
    fParser[DmpDetector::kPsd] = new G4GDMLParser();
    fParser[DmpDetector::kPsd]->Read("Psd.gdml");
    fPhysiVol[DmpDetector::kPsd] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,gSimOpt->GetOffset(DmpDetector::kPsd)),
                    "Psd",
                    fParser[DmpDetector::kPsd]->GetVolume("Psd_detector_vol"),
                    fPhysiVol[DmpDetector::kWhole],
                    false,
                    0);
  }
  if(gSimOpt->GetGdmlPath(DmpDetector::kStk) != "default"){
    chdir(gSimOpt->GetGdmlPath(DmpDetector::kStk).c_str());
    fParser[DmpDetector::kStk] = new G4GDMLParser();
    fParser[DmpDetector::kStk]->Read("Stk.gdml");
    fPhysiVol[DmpDetector::kStk] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,gSimOpt->GetOffset(DmpDetector::kStk)),
                    "Stk",
                    fParser[DmpDetector::kStk]->GetVolume("Stk_detector_vol"),
                    fPhysiVol[DmpDetector::kWhole],
                    false,
                    0);
  }
  if(gSimOpt->GetGdmlPath(DmpDetector::kBgo) != "default"){
    chdir(gSimOpt->GetGdmlPath(DmpDetector::kBgo).c_str());
    fParser[DmpDetector::kBgo] = new G4GDMLParser();
    fParser[DmpDetector::kBgo]->Read("Bgo.gdml");
    fPhysiVol[DmpDetector::kBgo] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,gSimOpt->GetOffset(DmpDetector::kBgo)),
                    "Bgo",
                    fParser[DmpDetector::kBgo]->GetVolume("Bgo_detector_vol"),
                    fPhysiVol[DmpDetector::kWhole],
                    false,
                    0);
  }
  if(gSimOpt->GetGdmlPath(DmpDetector::kNud) != "default"){
    chdir(gSimOpt->GetGdmlPath(DmpDetector::kNud).c_str());
    fParser[DmpDetector::kNud] = new G4GDMLParser();
    fParser[DmpDetector::kNud]->Read("Nud.gdml");
    fPhysiVol[DmpDetector::kNud] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,gSimOpt->GetOffset(DmpDetector::kNud)),
                    "Nud",
                    fParser[DmpDetector::kNud]->GetVolume("Nud_detector_vol"),
                    fPhysiVol[DmpDetector::kWhole],
                    false,
                    0);
  }
  chdir(dirTmp);

// *
// *  TODO: set SD of SubDet at here
// *
  G4SDManager *mgrSD = G4SDManager::GetSDMpointer();
  if(fParser[DmpDetector::kBgo]){
#ifdef DmpDebug
std::cout<<"DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__FUNCTION__<<"\tadd SD"<<std::endl;
#endif
    DmpSimBgoSD *bgoSD = new DmpSimBgoSD("BgoSD");
    mgrSD->AddNewDetector(bgoSD);
    fParser[DmpDetector::kBgo]->GetVolume("BGO_bar_vol")->SetSensitiveDetector(bgoSD);
  }

  return fPhysiVol[DmpDetector::kWhole];
}


