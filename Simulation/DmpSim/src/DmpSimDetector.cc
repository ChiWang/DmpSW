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

// *
// *  TODO: add SD of Psd, Stk and Nud
// *
#include "DmpSimDetector.h"
//#include "DmpSimPsdSD.h"
//#include "DmpSimStkSD.h"
#include "DmpSimBgoSD.h"
#include "DmpSimNudSD.h"

//-------------------------------------------------------------------
DmpSimDetector::DmpSimDetector()
 :fGdmlPath("default"),
  fParser(0),
  fPhyVolume(0)
{
  fParser = new G4GDMLParser();
}

//-------------------------------------------------------------------
DmpSimDetector::~DmpSimDetector(){
  delete fParser;
}

//-------------------------------------------------------------------
G4VPhysicalVolume* DmpSimDetector::Construct(){
  char *dirTmp = getcwd(NULL,NULL);
  if(fGdmlPath == "default"){
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
    /*DmpSimPsdSD *psdSD = new DmpSimPsdSD("PsdSD");
    mgrSD->AddNewDetector(psdSD);
    fParser->GetVolume("Psd_StripLV")->SetSensitiveDetector(psdSD);*/
  }
  /*
  if(fParser->GetVolume("Stk_DetLV")){
    std::cout<<" Setting Sensitive Detector of Stk"<<std::endl;
    DmpSimStkSD *stkSD = new DmpSimStkSD("StkSD");
    mgrSD->AddNewDetector(stkSD);
    fParser->GetVolume("Stk_StripLV")->SetSensitiveDetector(stkSD);
  }
  */
  if(fParser->GetVolume("Bgo_DetLV")){
    std::cout<<" Setting Sensitive Detector of Bgo"<<std::endl;
    DmpSimBgoSD *bgoSD = new DmpSimBgoSD("BgoSD");
    mgrSD->AddNewDetector(bgoSD);
    fParser->GetVolume("Bgo_BarLV")->SetSensitiveDetector(bgoSD);
  }
  if(fParser->GetVolume("Nud_DetLV")){
    std::cout<<" Setting Sensitive Detector of Nud"<<std::endl;
    DmpSimNudSD *nudSD = new DmpSimNudSD("NudSD");
    mgrSD->AddNewDetector(nudSD);
    fParser->GetVolume("Nud_Block0LV")->SetSensitiveDetector(nudSD);
    fParser->GetVolume("Nud_Block1LV")->SetSensitiveDetector(nudSD);
    fParser->GetVolume("Nud_Block2LV")->SetSensitiveDetector(nudSD);
    fParser->GetVolume("Nud_Block3LV")->SetSensitiveDetector(nudSD);
  }

  return fPhyVolume;
}


