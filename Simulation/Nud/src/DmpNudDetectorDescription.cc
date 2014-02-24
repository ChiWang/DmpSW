// Description: This class describes the detector geometry of the DAMPE PSD detector
//
// Author(s):
//  - added by Tiekuang Dong 2012/12/23

#include "DmpNudDetectorDescription.hh"
//#include "DmpPsdDetectorMessenger.hh"
#include "DmpNudSensitiveDetector.hh"
//#include "DmpPsdROGeometry.hh"

#include "G4Material.hh"
#include "G4ProductionCuts.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
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

DmpNudDetectorDescription::DmpNudDetectorDescription(G4GDMLParser *gdmlParser)
    :logicNUD(0),logicNUDDet0(0),logicNUDDet1(0),logicNUDDet2(0),logicNUDDet3(0),
     logicNUDShell0(0),logicNUDShell1(0),
      nudSensitiveDetector(0),aNudRegion(0),fParser(gdmlParser)
{
  // default parameter values of the payload
  NUDThickness        = 6.*cm;
  NbOfNUDStrips       = 4;

logicNUD=fParser->GetVolume("NUD_log");
logicNUDDet0=fParser->GetVolume("NUD0"); 
logicNUDDet1=fParser->GetVolume("NUD1"); 
logicNUDDet2=fParser->GetVolume("NUD2"); 
logicNUDDet3=fParser->GetVolume("NUD3"); 
logicNUDShell0=fParser->GetVolume("SHELL0");
logicNUDShell1=fParser->GetVolume("SHELL1");
}

DmpNudDetectorDescription::~DmpNudDetectorDescription()
{ 
  //delete psdDetectorMessenger;
}


void DmpNudDetectorDescription::ComputeParameters()
{
 ParseNudParametersFromGDML();
 G4Box* Nud_box=(G4Box*)logicNUD->GetSolid();
 NUDSizeXY = 2*Nud_box->GetXHalfLength();
 NUDSizeZ =  2*Nud_box->GetZHalfLength();
 NUDCenter=30*cm;
 
}


void DmpNudDetectorDescription::defineSensitiveDetector()
{  
  //Sensitive Detector Manager
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if(!nudSensitiveDetector) {
    nudSensitiveDetector = new DmpNudSensitiveDetector("NudSD");
    SDman->AddNewDetector(nudSensitiveDetector );		
   }
 if (logicNUDDet0)
    logicNUDDet0->SetSensitiveDetector(nudSensitiveDetector); // PSD
 if (logicNUDDet1)
    logicNUDDet1->SetSensitiveDetector(nudSensitiveDetector); // PSD
 if (logicNUDDet2)
    logicNUDDet2->SetSensitiveDetector(nudSensitiveDetector); // PSD
 if (logicNUDDet3)
    logicNUDDet3->SetSensitiveDetector(nudSensitiveDetector); // PSD

}


void DmpNudDetectorDescription::ParseNudParametersFromGDML()
{

 G4cout<< "[DmpNudDetectorDescription::ParseNudParametersFromGDML] parsing NUD parameters from GDML... " << G4endl;

  G4GDMLAuxListType auxinfo = fParser->GetVolumeAuxiliaryInformation(logicNUD);

}










