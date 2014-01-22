// Description: This class describes the detector geometry of the DAMPE STK detector
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpStkDetectorDescription.hh"
#include "DmpStkDetectorMessenger.hh"
#include "DmpStkSensitiveDetector.hh"
#include "DmpStkROGeometry.hh"

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

DmpStkDetectorDescription::DmpStkDetectorDescription(G4GDMLParser* gdmlParser)
:fParser(gdmlParser)
{
	/*
	 *  Set default STK parameters
	 */
	//SensitiveDetectorCenterZ = -99999.9*m;

	TKRSizeZ    = -99999.9*m;
	TKRSizeXY   = -99999.9*m;
	TKRBlockXY  = -99999.9*m;

	TKRSiliconThickness    = -99999.9*m;
	TKRSiliconTileXY       = -99999.9*m;
	TKRSiliconPitch        = -99999.9*m;

	NbOfTKRLayers  = -9999;
	NbOfTKRTiles   = -9999;
	NbOfTKRBlocks  = -9999;
	NbOfTKRStrips  = -9999;

	TKRLayerDistance      = -99999.9*m;
	TKRViewsDistance      = -99999.9*m;
	//TKRTungstenDistance   = -99999.9*m;
	TKRActiveTileXY       = -99999.9*m;
	TKRActiveTileZ        = -99999.9*m;
	SiliconGuardRing      = -99999.9*m;
	TilesSeparation       = -99999.9*m;

	ConverterThickness      = -99999.9*m;
	ThickConverterThickness = -99999.9*m;

	TKRCenterGap  = -99999.9*m;

	/* Get STK model parameters from GDML description */
	ParseStkParametersFromGDML();
	ComputeOtherParameters();

	/* Create commands for interactive definition of the payload */
	stkDetectorMessenger = new DmpStkDetectorMessenger(this);

}


DmpStkDetectorDescription::~DmpStkDetectorDescription()
{ 
  //delete stkDetectorMessenger;
}


void DmpStkDetectorDescription::ParseStkParametersFromGDML(){
	G4cout<< "[DmpStkDetectorDescription::ParseStkParametersFromGDML] parsing STK parameters from GDML... \n";
	G4LogicalVolume* stk_detector_vol = fParser->GetVolume("STK_detector_vol");
	G4GDMLAuxListType auxinfo = fParser->GetVolumeAuxiliaryInformation (stk_detector_vol);
	for(G4int i=0; i<auxinfo.size(); i++){
		G4String type = auxinfo.at(i).type;
		// default parameter values of the payload
		//tungsten converter hickness
		if      (type == "ConverterThickness")       ConverterThickness      = __StringToDouble(auxinfo.at(i).value)*micrometer;
		else if (type == "ThickConverterThickness")  ThickConverterThickness = __StringToDouble(auxinfo.at(i).value)*micrometer;
		else if (type == "TKRSiliconThickness")      TKRSiliconThickness     = __StringToDouble(auxinfo.at(i).value)*micrometer;
		else if (type == "TKRSiliconTileXY")         TKRSiliconTileXY        = __StringToDouble(auxinfo.at(i).value)*cm;//size
		else if (type == "TKRSiliconPitch")		  	 TKRSiliconPitch         = __StringToDouble(auxinfo.at(i).value)*micrometer;  //physical pitch
		else if (type == "SiliconGuardRing") 	  	 SiliconGuardRing        = __StringToDouble(auxinfo.at(i).value)*mm; //guard ring thickness
		else if (type == "NbOfTKRStrips") 		  	 NbOfTKRStrips           = __StringToInt(auxinfo.at(i).value);
		//ladder geometry
		else if (type == "NbOfTKRTiles")  	  	     NbOfTKRTiles            = __StringToInt(auxinfo.at(i).value);
		else if (type == "NbOfWTKRTiles")            NbOfWTKRTiles           = __StringToInt(auxinfo.at(i).value);
		else if (type == "TilesSeparation")          TilesSeparation         = __StringToDouble(auxinfo.at(i).value)*micrometer;
		else if (type == "TKRWRecess")               TKRWRecess              = __StringToDouble(auxinfo.at(i).value)*mm;
		//tracker geometry
		else if (type == "TKRLayerDistance")  		 TKRLayerDistance        = __StringToDouble(auxinfo.at(i).value)*cm;
		else if (type == "TKRViewsDistance")         TKRViewsDistance        = __StringToDouble(auxinfo.at(i).value)*mm;
		else if (type == "TKRCenterGap")             TKRCenterGap            = __StringToDouble(auxinfo.at(i).value)*micrometer;
		//else if (type == "TKRTungstenDistance")      TKRTungstenDistance     = __StringToDouble(auxinfo.at(i).value)*mm; //distance from converter to SSD
		else if (type == "NbOfTKRLayers")            NbOfTKRLayers           = __StringToInt(auxinfo.at(i).value);
		else if (type == "NbOfTKRBlocks")  		     NbOfTKRBlocks           = __StringToInt(auxinfo.at(i).value);
		//sensitive detector
		//else if (type == "SensitiveDetectorCenterZ") SensitiveDetectorCenterZ= __StringToDouble(auxinfo.at(i).value)*mm;

	}
	G4cout<< "[DmpStkDetectorDescription::ParseStkParametersFromGDML] ... finished parsing parameters" << "\n";

	// Get materials
	G4cout<< "[DmpStkDetectorDescription::ParseStkParametersFromGDML] parsing STK parameters from GDML... \n";
	ConverterMaterial = fParser->GetVolume("stk_tungsten")->GetDaughter(0)->GetLogicalVolume()->GetMaterial();
	G4cout<< "[DmpStkDetectorDescription::ParseStkParametersFromGDML] ... finished parsing materials" << "\n";


}





void DmpStkDetectorDescription::ComputeOtherParameters()
{

  // Compute derived parameters of the payload

  //TKRSupportThickness =TKRLayerDistance -2.*TKRSiliconThickness 
  //  - TKRViewsDistance - ConverterThickness;
  TKRSupportThickness =TKRLayerDistance -2.*TKRSiliconThickness - TKRViewsDistance;
  //TKRSizeXY = NbOfTKRTiles*TKRSiliconTileXY + (NbOfTKRTiles+1)*TilesSeparation;
  //TKRBlockXY = NbOfTKRTiles*TKRSiliconTileXY + (NbOfTKRTiles+1)*TilesSeparation;
  TKRBlockXY = NbOfTKRTiles*TKRSiliconTileXY + (NbOfTKRTiles-1)*TilesSeparation;
  TKRWBlockXY = NbOfWTKRTiles*(TKRSiliconTileXY - TKRWRecess) + (NbOfWTKRTiles-1)*TilesSeparation;
  TKRSizeXY = (NbOfTKRBlocks/2)*TKRBlockXY + TKRCenterGap;
  TKRSizeZ = NbOfTKRLayers*TKRLayerDistance; 
  G4cout << "DmpStkDetectorDescription::ComputeParameters: calculated STK size " << G4endl;
  G4cout << "       Sensor size: " << TKRSiliconTileXY << G4endl;
  G4cout << "       Number of sensors: " << NbOfTKRTiles << G4endl;
  G4cout << "       Number of block: " << NbOfTKRBlocks << G4endl;
  G4cout << "       Tile separation: " << TilesSeparation << G4endl;
  G4cout << "       Center gap: " <<  TKRCenterGap << G4endl;
  //G4cout << "       TKR block size =nsen x size + (nsen+1) x sep  = " << TKRBlockXY << G4endl;
  G4cout << "       TKR block size =nsen x size + (nsen-1) x sep  = " << TKRBlockXY << G4endl;
  G4cout << "       TKR size = 2 x block + gap = " << TKRSizeXY << G4endl;
  G4cout << "       TKR W plate size =nsen x (size-recess) + (nsen-1) x sep  = " << TKRWBlockXY << G4endl;

    
  TKRActiveTileXY = TKRSiliconTileXY - 2*SiliconGuardRing;
  TKRActiveTileZ = TKRSiliconThickness;
  if(NbOfTKRStrips != TKRActiveTileXY/TKRSiliconPitch) {
    G4cout << "Warning!!! number of strips per ladder mismatch! " << NbOfTKRStrips << " vs " << TKRActiveTileXY/TKRSiliconPitch << G4endl;
  }

  NbOfTKRStrips = TKRActiveTileXY/TKRSiliconPitch;
  G4cout << "DmpStkDetectorDescription::ComputeParameters: calculated Si sensor parameters " << G4endl;
  G4cout << "       Input GuardRing width: " << SiliconGuardRing << G4endl;
  G4cout << "       Input Pitch width: " << TKRSiliconPitch << G4endl;
  G4cout << "       Active area = sensor_size - 2xGuradRing = " << TKRActiveTileXY << G4endl;
  G4cout << "       Nstrip = Active area/Pitch = " << NbOfTKRStrips << G4endl;

  //SiliconGuardRing = TKRActiveTileXY - NbOfTKRStrips*TKRSiliconPitch;
  SiliconGuardRing = 0.5*(TKRSiliconTileXY - NbOfTKRStrips*TKRSiliconPitch);
  TKRActiveTileXY = TKRSiliconTileXY - 2*SiliconGuardRing;
  G4cout << "       Recaculated GuradRing in case of integer roundup: " << SiliconGuardRing << G4endl;
  G4cout << "       Recaculated TKRActiveTileXY in case of integer roundup: " << TKRActiveTileXY << G4endl;

  TKRXStripX = TKRYStripY = TKRSiliconPitch;
  TKRYStripX = TKRXStripY = TKRActiveTileXY;
  TKRZStrip = TKRSiliconThickness;


  /* Some tests....
  G4cout<<"\n\n\n\n test \n";
  G4cout<<"GetPlaneNumber(fParser->GetVolume(STKDetectorX-23_ActiveTileX-15))"<<GetPlaneNumber(fParser->GetVolume("STKDetectorX-23_ActiveTileX-15"))<<G4endl;
  G4cout<<"GetTileNumber(fParser->GetVolume(STKDetectorX-23_ActiveTileX-15))"<<GetTileNumber(fParser->GetVolume("STKDetectorX-23_ActiveTileX-15"))<<G4endl;
  */


}


void DmpStkDetectorDescription::defineSensitiveDetector(){
    //Sensitive Detector Manager
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    //if(!stkSensitiveDetector) {
    stkSensitiveDetector = new DmpStkSensitiveDetector("StkSD");
    SDman->AddNewDetector( stkSensitiveDetector );
    //}


    //STK Readout geometry: in the STK 4-SSD are wire-bonded to form a ladder
    G4String ROgeometryName = "TrackerROGeom";
    G4VReadOutGeometry* stkRO = new DmpStkROGeometry(ROgeometryName,fParser);
    stkRO->BuildROGeometry();
    stkSensitiveDetector->SetROgeometry(stkRO);


    //Assign tracking geometry to sensitive detector
    G4LogicalVolume* logSTK = fParser->GetVolume(GetLogSTKSiMotherVolumeNameGDML());
    for(G4int i=0; i<logSTK->GetNoDaughters();i++){
        G4LogicalVolume* logSTKTile = logSTK->GetDaughter(i)->GetLogicalVolume();
        logSTKTile->SetSensitiveDetector(stkSensitiveDetector);
    }

}



/*
 *   Methods connected with GDML naming conventions for STK
 */

G4bool DmpStkDetectorDescription::isVolumeSTKActiveTileX(const G4String& volumename){
    if(!(volumename.contains("ActiveTileX"))) return false;
    if(!(volumename.contains("STKDetectorX"))) return false;
    return true;
}

G4bool DmpStkDetectorDescription::isVolumeSTKActiveTileY(const G4String& volumename){
    if(!(volumename.contains("ActiveTileY"))) return false;
    if(!(volumename.contains("STKDetectorY"))) return false;
    return true;
}


G4int DmpStkDetectorDescription::GetPlaneNumber(G4LogicalVolume* tile) {
    G4String name = tile->GetName();
    int start = name.index("STKDetector");
    start = name.index("-",start)+1;
    int stop = name.index("_",start+1);
    if(stop<0) stop = name.index("-",start+1);
    int len = -1;
    if(stop>=0) len=stop-start+1;
    return __StringToInt(G4String(name.substr(start, len)).strip());

};

G4int    DmpStkDetectorDescription::GetTileNumber(G4LogicalVolume* tile){
    G4String name = tile->GetName();
    int start = name.index("ActiveTile");
    start = name.index("-",start)+1;
    int stop = name.index("_",start+1);
    if(stop<0) stop = name.index("-",start+1);
    int len = -1;
    if(stop>=0) len=stop-start+1;
    return __StringToInt(G4String(name.substr(start, len)).strip());
};



G4double DmpStkDetectorDescription::__StringToDouble(G4String value){
	G4double result = atof(
			((std::string)(value)).c_str()
			);
	return result;
}

G4int DmpStkDetectorDescription::__StringToInt(G4String value){
	G4int result = atof(
			((std::string)(value)).c_str()
			);
	return result;
}













