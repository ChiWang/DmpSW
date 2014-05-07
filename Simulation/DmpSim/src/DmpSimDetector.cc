/*
 *  $Id: DmpSimDetector.cc, 2014-04-14 13:05:14 chi $
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
#include "DmpSimDetector.h"
//#include "DmpSimPsdSD.h"
//#include "DmpSimStkSD.h"
#include "DmpSimBgoSD.h"
//#include "DmpSimNudSD.h"

//-------------------------------------------------------------------
DmpSimDetector::DmpSimDetector()
 :fSatGdmlPath("default"),
  fSatParser(0),
  fSatPhyVolume(0)
{
  fSatParser = new G4GDMLParser();
  for (short i=0;i<DmpDetector::gSubDetNo;++i){
    fGdmlPath[i]="default";
    fParser[i] = 0;
    fPhyVolume[i] = 0;
  }
  fOffset[DmpDetector::kPsd] = -33.4;
  fOffset[DmpDetector::kStk] = 0;
  fOffset[DmpDetector::kBgo] = 200;
  fOffset[DmpDetector::kNud] = 0;
}

//-------------------------------------------------------------------
DmpSimDetector::~DmpSimDetector(){
  delete fSatParser;
  for (short i=0;i<DmpDetector::gSubDetNo;++i){
    if(fParser[i] != 0){
      delete fParser[i];
    }
  }
}

//-------------------------------------------------------------------
G4VPhysicalVolume* DmpSimDetector::Construct(){
  char *dirTmp = getcwd(NULL,NULL);
  if(fSatGdmlPath == "default"){
     G4cout<<"Error: must setup detector in job option file. SetSatGdml(type,GdmlFilePath)"<<G4endl;
     return 0;
  }else{
    chdir(fSatGdmlPath.c_str());
    fSatParser->Read("Sat.gdml");
    std::cout<<" Reading "<<fSatGdmlPath<<" Sat.gdml"<<std::endl;
    fSatPhyVolume = fSatParser->GetWorldVolume();
  }
  if(fGdmlPath[DmpDetector::kPsd] != "default"){
    chdir(fGdmlPath[DmpDetector::kPsd].c_str());
    fParser[DmpDetector::kPsd] = new G4GDMLParser();
    std::cout<<" Reading "<<fGdmlPath[DmpDetector::kPsd]<<" Psd.gdml"<<std::endl;
    fParser[DmpDetector::kPsd]->Read("Psd.gdml");
    fPhyVolume[DmpDetector::kPsd] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,fOffset[DmpDetector::kPsd]),
                    "Psd",
                    fParser[DmpDetector::kPsd]->GetVolume("Psd_DetLV"),
                    fSatPhyVolume,
                    false,
                    0);
  }
  if(fGdmlPath[DmpDetector::kStk] != "default"){
    chdir(fGdmlPath[DmpDetector::kStk].c_str());
    fParser[DmpDetector::kStk] = new G4GDMLParser();
    fParser[DmpDetector::kStk]->Read("Stk.gdml");
    std::cout<<" Reading "<<fGdmlPath[DmpDetector::kStk]<<" Stk.gdml"<<std::endl;
    fPhyVolume[DmpDetector::kStk] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,fOffset[DmpDetector::kStk]),
                    "Stk",
                    fParser[DmpDetector::kStk]->GetVolume("Stk_DetLV"),
                    fSatPhyVolume,
                    false,
                    0);
  }
  if(fGdmlPath[DmpDetector::kBgo] != "default"){
    chdir(fGdmlPath[DmpDetector::kBgo].c_str());
    fParser[DmpDetector::kBgo] = new G4GDMLParser();
    fParser[DmpDetector::kBgo]->Read("Bgo.gdml");
    std::cout<<" Reading "<<fGdmlPath[DmpDetector::kBgo]<<" Bgo.gdml"<<std::endl;
    fPhyVolume[DmpDetector::kBgo] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,fOffset[DmpDetector::kBgo]),
                    "Bgo",
                    fParser[DmpDetector::kBgo]->GetVolume("Bgo_DetLV"),
                    fSatPhyVolume,
                    false,
                    0);
  }
  if(fGdmlPath[DmpDetector::kNud] != "default"){
    chdir(fGdmlPath[DmpDetector::kNud].c_str());
    fParser[DmpDetector::kNud] = new G4GDMLParser();
    fParser[DmpDetector::kNud]->Read("Nud.gdml");
    std::cout<<" Reading "<<fGdmlPath[DmpDetector::kNud]<<" Nud.gdml"<<std::endl;
    fPhyVolume[DmpDetector::kNud] = new G4PVPlacement(0,
                    G4ThreeVector(0,0,fOffset[DmpDetector::kNud]),
                    "Nud",
                    fParser[DmpDetector::kNud]->GetVolume("Nud_DetLV"),
                    fSatPhyVolume,
                    false,
                    0);
  }
  chdir(dirTmp);
  // *
  // *  TODO: set SD of SubDet at here
  // *
  G4SDManager *mgrSD = G4SDManager::GetSDMpointer();
  if(fParser[DmpDetector::kBgo]){
    DmpSimBgoSD *bgoSD = new DmpSimBgoSD("BgoSD");
    mgrSD->AddNewDetector(bgoSD);
    fParser[DmpDetector::kBgo]->GetVolume("Bgo_BarLV")->SetSensitiveDetector(bgoSD);
  }

  return fSatPhyVolume;
}


