/*
 *  $Id: DmpSimDetector.cc, 2014-05-08 11:44:50 DAMPE $
 *  Author(s):
 *    Xin WU (Xin.Wu@cern.cn)   11/07/2013
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GDMLParser.hh"
#include "G4SDManager.hh"

#include "DmpSimDetector.h"
#include "DmpSimPsdSD.h"
#include "DmpSimStkSD.h"
#include "DmpSimBgoSD.h"
#include "DmpSimNudSD.h"

//-------------------------------------------------------------------
std::string DmpSimDetector::fGdmlPath = "NO";

//-------------------------------------------------------------------
DmpSimDetector::DmpSimDetector()
 :fParser(0),
  fPhyVolume(0),
  fPsdSD(0),
  fStkSD(0),
  fBgoSD(0),
  fNudSD(0)
{
  fParser = new G4GDMLParser();
  fPsdSD = new DmpSimPsdSD();
  fStkSD = new DmpSimStkSD();
  fBgoSD = new DmpSimBgoSD();
  fNudSD = new DmpSimNudSD();
}

//-------------------------------------------------------------------
DmpSimDetector::~DmpSimDetector(){
  delete fParser;
  delete fPsdSD;
  delete fStkSD;
  delete fBgoSD;
  delete fNudSD;
}

//-------------------------------------------------------------------
G4VPhysicalVolume* DmpSimDetector::Construct(){
  char *dirTmp = getcwd(NULL,NULL);
  if(fGdmlPath == "NO"){
     G4cout<<"Error: must setup detector in job option file. SetGdml(GdmlFilePath)"<<G4endl;
     return 0;
  }else{
    chdir(fGdmlPath.c_str());
    fParser->Read("DAMPE.gdml");
    fPhyVolume = fParser->GetWorldVolume();
  }
  chdir(dirTmp);
// *
// *  TODO:  set structure invisable
// *

  // *
  // *  TODO: set SD of SubDet at here
  // *
  G4SDManager *mgrSD = G4SDManager::GetSDMpointer();
  if(fParser->GetVolume("Psd_DetLV")){
    std::cout<<" Setting Sensitive Detector of Psd"<<std::endl;
    mgrSD->AddNewDetector(fPsdSD);
    fParser->GetVolume("Psd_Strip0LV")->SetSensitiveDetector(fPsdSD);
    fParser->GetVolume("Psd_Strip1LV")->SetSensitiveDetector(fPsdSD);
  }
  if(fParser->GetVolume("Stk_DetLV")){
          /*
    std::cout<<" Setting Sensitive Detector of Stk"<<std::endl;
    mgrSD->AddNewDetector(fStkSD);
    fParser->GetVolume("Stk_StripLV")->SetSensitiveDetector(fStkSD);
    */
  }
  if(fParser->GetVolume("Bgo_DetLV")){
    std::cout<<" Setting Sensitive Detector of Bgo"<<std::endl;
    mgrSD->AddNewDetector(fBgoSD);
    fParser->GetVolume("Bgo_BarLV")->SetSensitiveDetector(fBgoSD);
  }
  if(fParser->GetVolume("Nud_DetLV")){
    std::cout<<" Setting Sensitive Detector of Nud"<<std::endl;
    mgrSD->AddNewDetector(fNudSD);
    fParser->GetVolume("Nud_Block0LV")->SetSensitiveDetector(fNudSD);
    fParser->GetVolume("Nud_Block1LV")->SetSensitiveDetector(fNudSD);
    fParser->GetVolume("Nud_Block2LV")->SetSensitiveDetector(fNudSD);
    fParser->GetVolume("Nud_Block3LV")->SetSensitiveDetector(fNudSD);
  }

  return fPhyVolume;
}


