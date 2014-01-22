// Description: This class describes the detector geometry of the DAMPE BGO detector
//
// Author(s):
//  - creation by X.Wu, 13/07/2013
//  - implemented by Yf.Wei 10/1/2014

#include "DmpBgoDetectorDescription.hh"
//#include "DmpBgoDetectorMessenger.hh"
#include "DmpBgoSensitiveDetector.hh"
//#include "DmpBgoROGeometry.hh"

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

#include "G4GDMLParser.hh"
#include "G4PhysicalVolumeStore.hh"
#include <sstream>

DmpBgoDetectorDescription::DmpBgoDetectorDescription(G4GDMLParser *gdmlParser)
  :fParser(gdmlParser),logicalBGO(0),logicalBGOBar(0),
   bgoSensitiveDetector(0),
   aBgoRegion(0)
{
  // default parameter values of the payload
  
  // create commands for interactive definition of the payload
  //bgoDetectorMessenger = new DmpBgoDetectorMessenger(this);

  //DAMPE BGO calorimeter 
  /*
  CALBarLength       = 0.*cm; 
  CALBarThickness    = 0.*cm; 
  CALLayerSeparation = 0.*mm;
  CALBarsSeparation  = 0.*mm;
  NbOfCALLayerBars   = 0; 
  NbOfCALLayers      = 0;
  */

  logicalBGO = fParser->GetVolume("BGO_detector_vol");
  logicalBGOBar = fParser->GetVolume("BGO_bar_vol");

}

DmpBgoDetectorDescription::~DmpBgoDetectorDescription()
{ 
  //delete bgoDetectorMessenger;
}


void DmpBgoDetectorDescription::ComputeParameters()
{
  ParseBgoParametersFromGDML();

  G4Box* ECal_box=(G4Box*)logicalBGO->GetSolid();
  CALSizeXY = 2*ECal_box->GetXHalfLength();
  CALSizeZ = 2*ECal_box->GetZHalfLength();

  // Compute derived parameters of the payload
  //CALSizeXY = CALBarThickness*NbOfCALLayerBars + (NbOfCALLayerBars+1)*CALBarsSeparation;
  //CALSizeZ = 2.*NbOfCALLayers*CALBarThickness + (2.*NbOfCALLayers+1)*CALLayerSeparation;

  G4Box* CALBar_box=(G4Box*)logicalBGOBar->GetSolid();
  CALBarX = 2*CALBar_box->GetYHalfLength();
  CALBarY = 2*CALBar_box->GetXHalfLength();
  CALBarZ = 2*CALBar_box->GetZHalfLength();

  //CALBarX = CALBarLength;
  //CALBarY = CALBarThickness;
  //CALBarZ = CALBarThickness;

  G4cout << "DmpBgoDetectorDescription::ComputeParameters: calculated BGO parameters " << G4endl;
  G4cout << "       caloremeter size XY/Z: " << CALSizeXY << "/" << CALSizeZ << G4endl;
  G4cout << "       number of BGO bars: " << NbOfCALBars << G4endl;
  G4cout << "       number of layers: " << NbOfCALLayers << "  " << " number of bars per layer: " << NbOfCALLayerBars << G4endl;
  G4cout << "       bar length/width/thickness: "<< CALBarX << "/" << CALBarY << "/" << CALBarZ << G4endl;
  G4cout << "       separation between layerss: "<<  CALBarsSeparation/mm << "mm" << G4endl;
  G4cout << "       separation between bars:    "<<  CALLayerSeparation/mm << "mm" << G4endl;

}


void DmpBgoDetectorDescription::ParseBgoParametersFromGDML()
{
  G4cout<< "[DmpBgoDetectorDescription::ParseBgoParametersFromGDML] parsing BGO parameters from GDML... " << G4endl;

  G4GDMLAuxListType auxinfo = fParser->GetVolumeAuxiliaryInformation(logicalBGO);
  G4String auxtype;

  for(G4GDMLAuxListType::iterator iter=auxinfo.begin();iter != auxinfo.end();iter++){
      auxtype=iter->type;
      if     (auxtype == "BGOaux_NbOfCALLayers")           NbOfCALLayers = atoi((iter->value).c_str());
      else if(auxtype == "BGOaux_NbOfCALLayerBars")        NbOfCALLayerBars = atoi((iter->value).c_str());
      else if(auxtype == "BGOaux_NbOfCALBars")             NbOfCALBars = atoi((iter->value).c_str());
      else if(auxtype == "BGOaux_CALBarsSeparation")       CALBarsSeparation = atof((iter->value).c_str())*mm; 
      else if(auxtype == "BGOaux_CALLayerSeparation")      CALLayerSeparation = atof((iter->value).c_str())*mm; 
  }
}

void DmpBgoDetectorDescription::SetCopyNumber()
{
  G4cout<< "BGO: Assign copyNum to sensitive bars"<<G4endl;
  G4PhysicalVolumeStore* PV_Store=G4PhysicalVolumeStore::GetInstance();
  G4VPhysicalVolume* physvolPtr=0;
  std::ostringstream volname;
  G4int ID=0;

  for(G4int HeadNo=90000;HeadNo<91400;HeadNo=HeadNo+100){
     for(G4int copy_id=(HeadNo+101);copy_id<(HeadNo+123);copy_id++){
        volname.str("");
        volname.clear();
        volname << "BGO_bar_" << copy_id;
        physvolPtr = PV_Store->GetVolume(volname.str(),false);
        ID = copy_id-90000-101;  //set layer No 0~13, bar No 0~21
        physvolPtr->SetCopyNo(ID);
	G4int CopyNo = physvolPtr->GetCopyNo();
	G4int barno = CopyNo-((int)(CopyNo/100))*100;
	G4int layerno = (int)(CopyNo/100);
        //G4cout<< "\t"<<volname.str()<<" : "<<physvolPtr->GetCopyNo()<<G4endl;
	//G4cout<< "layer number: "<<layerno<<", bar number: "<<barno<<G4endl;
     }  
  }
  G4cout << "Set BGO bars' copy number: done!" <<G4endl;
}

void DmpBgoDetectorDescription::defineSensitiveDetector()
{
  SetCopyNumber();

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if(!bgoSensitiveDetector){
    bgoSensitiveDetector = new DmpBgoSensitiveDetector("BgoSD");
    SDman->AddNewDetector( bgoSensitiveDetector );
  }
  logicalBGOBar->SetSensitiveDetector(bgoSensitiveDetector);
}







