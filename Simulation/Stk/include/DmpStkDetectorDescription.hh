#ifndef DmpStkDetectorDescription_h
#define DmpStkDetectorDescription_h 1

#include "globals.hh"
#include "G4GDMLParser.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class G4Region;

class DmpStkDetectorMessenger;
class DmpStkSensitiveDetector;

class DmpStkDetectorDescription
{
public:
  
  DmpStkDetectorDescription(G4GDMLParser* gdmlParser);
  ~DmpStkDetectorDescription();
  
public:

  void defineSensitiveDetector();

  /*
  void ComputeParameters();
  void Construct(G4double, G4VPhysicalVolume*, G4LogicalVolume*);
  */

  /*
  void SetNbOfTKRLayers (G4int); // TKR number of layers, material, detector
  void SetTKRTileSizeXY (G4double);
  void SetNbOfTKRTiles (G4int);
  void SetTKRSiliconThickness(G4double);
  void SetTKRSiliconPitch(G4double);
  
  void SetTKRLayerDistance (G4double);
  void SetTKRViewsDistance (G4double);
  void SetTKRTungstenDistance (G4double);

  void SetConverterThickness(G4double);     
  
  void SetThickConverterThickness(G4double);     
  void SetTKRCenterGap(G4double);
  */


  /*
   *  Get methods
   */
  //G4double GetSensitiveDetectorCenterZ() {return SensitiveDetectorCenterZ;};

  G4double GetSizeZ()               {return TKRSizeZ;}; 
  G4double GetSizeXY()              {return TKRSizeXY;};

  G4double GetTKRSizeZ()               {return TKRSizeZ;}; 
  G4double GetTKRSizeXY()              {return TKRSizeXY;};
  G4double GetTKRBlockXY()             {return TKRBlockXY;};
     
  G4double GetTKRSiliconThickness()    {return TKRSiliconThickness;}; 
  G4double GetTKRSiliconTileXY()       {return TKRSiliconTileXY;}; 
  G4double GetTKRSiliconPitch()        {return TKRSiliconPitch;}; 
  G4int    GetNbOfTKRLayers()          {return NbOfTKRLayers;}; 
  G4int    GetNbOfTKRTiles()           {return NbOfTKRTiles;}; 
  G4int    GetNbOfTKRBlocks()          {return NbOfTKRBlocks;}; 
  G4int    GetNbOfTKRStrips()          {return NbOfTKRStrips;}; 
  G4double GetTKRLayerDistance()       {return TKRLayerDistance;};
  G4double GetTKRViewsDistance()       {return TKRViewsDistance;};
  //G4double GetTKRTungstenDistance()    {return TKRTungstenDistance;};

  G4double GetTKRActiveTileXY()        {return TKRActiveTileXY;};
  G4double GetTKRActiveTileZ()         {return TKRActiveTileZ;};
  G4double GetSiliconGuardRing()       {return SiliconGuardRing;}
  G4double GetTilesSeparation()        {return TilesSeparation;};
  
  G4Material* GetConverterMaterial()   {return ConverterMaterial;};
  G4double    GetConverterThickness()  {return ConverterThickness;};      
  
  G4double    GetThickConverterThickness()  {return ThickConverterThickness;};      
  G4double    GetTKRCenterGap()        {return TKRCenterGap;};


  // GDML STK name definitions
  G4String GetLogSTKVolumeNameGDML()          {return "STK_detector_vol";};
  G4String GetPhysSTKVolumeNameGDML()         {return "STK_detector_vol_PV";};
  G4String GetLogSTKSiMotherVolumeNameGDML()  {return "stk_si";};
  G4String GetPhysSTKSiMotherVolumeNameGDML() {return "stk_si_PV";};
  //G4String GetLogSTKSiTileVolumeNameGDML()    {return "ActiveTileX-%d_STKDetectorX-%d";};
  //G4String GetPhysSTKSiTileVolumeNameGDML()   {return "ActiveTileX-%d_STKDetectorX-%d_PV";};

  // Helper functions
  G4bool isVolumeSTKActiveTileX(const G4String& volumename);
  G4bool isVolumeSTKActiveTileY(const G4String& volumename);
  G4bool isVolumeSTKActiveTile(const G4String& volumename);
  G4bool isVolumeConverter(const G4String& volumename);
  G4bool isVolumeThickConverter(const G4String& volumename);


  G4int    GetPlaneNumber(G4LogicalVolume* tilen);
  G4int    GetTileNumber(G4LogicalVolume* tile);



              
private:
  G4GDMLParser*      fParser;

  G4Material*        ConverterMaterial;

  G4double           ConverterThickness;
  G4double           ThickConverterThickness;
  
  G4double TKRSiliconThickness; 
  G4double TKRSiliconTileXY; 
  G4double TKRSiliconPitch; 

  //G4double SensitiveDetectorCenterZ;
  G4double TKRSizeXY;
  G4double TKRSizeZ;
  G4double TKRBlockXY;
  G4double TKRWBlockXY;

  G4double TKRLayerDistance;
  G4double TKRViewsDistance;
  //G4double TKRTungstenDistance;
  G4double TKRSupportThickness;
  G4double TKRCenterGap;

  G4int    NbOfTKRLayers; 
  G4int    NbOfTKRTiles; 
  G4int    NbOfWTKRTiles; 
  G4int    NbOfTKRBlocks; 

  G4double TKRActiveTileXY;
  G4double TKRActiveTileZ;
  G4double TilesSeparation;
  G4double TKRWRecess;
  G4double SiliconGuardRing;
  G4int    NbOfTKRStrips;

  G4double TKRXStripX;
  G4double TKRYStripX;
  G4double TKRXStripY;
  G4double TKRYStripY;
  G4double TKRZStrip;
  

  /*
  G4Material*        defaultMaterial;
  G4Material*        TKRMaterial;
     
  G4Box*             solidTKR;          // Tracker 
  G4LogicalVolume*   logicTKR;    
  G4VPhysicalVolume* physiTKR;    

  G4Box*             solidTKRDetectorX;  // Tracker PLANE X
  G4LogicalVolume*   logicTKRDetectorX;
  G4VPhysicalVolume* physiTKRDetectorX;    

  G4Box*             solidTKRDetectorY;  // Tracker PLANE Y
  G4LogicalVolume*   logicTKRDetectorY;
  G4VPhysicalVolume* physiTKRDetectorY;    

  G4Box*             solidPlane;  // Support Plane no W
  G4LogicalVolume*   logicPlane;
  G4VPhysicalVolume* physiPlane;

  G4Box*             solidPlaneThinW;  // Support Plane with 1mm W
  G4LogicalVolume*   logicPlaneThinW;
  G4VPhysicalVolume* physiPlaneThinW;
    
  G4Box*             solidPlaneThickW;  // Support Plane 2mm W
  G4LogicalVolume*   logicPlaneThickW;
  G4VPhysicalVolume* physiPlaneThickW;

  G4Box*             solidConverter;  // Converter 
  G4LogicalVolume*   logicConverter;
  G4VPhysicalVolume* physiConverter;         

  G4Box*             solidThickConverter;  // Thick Converter 
  G4LogicalVolume*   logicThickConverter;
  G4VPhysicalVolume* physiThickConverter;
  */

  DmpStkDetectorMessenger*   stkDetectorMessenger;  //pointer to the Messenger
  DmpStkSensitiveDetector*   stkSensitiveDetector;  //pointer to the sensitive detector

  //G4Region* aTKRRegion; // STK cut region

private:

  void ParseStkParametersFromGDML();
  void ComputeOtherParameters();
  //void DefineMaterials();
  G4double __StringToDouble(G4String value);
  G4int    __StringToInt(G4String value);
  G4String __getAuxGDMLParamter(G4GDMLAuxListType auxinfo, std::string parameterName);

};

#endif









