#ifndef DmpBgoDetectorDescription_h
#define DmpBgoDetectorDescription_h 1

#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4Region;
class G4VSolid;
class G4GDMLParser; 

//class DmpBgoDetectorMessenger;
class DmpBgoSensitiveDetector;

class DmpBgoDetectorDescription
{
public:
  
  DmpBgoDetectorDescription(G4GDMLParser* );
  ~DmpBgoDetectorDescription();
  
public:
  
  void ComputeParameters();
  //void Construct(G4VPhysicalVolume*, G4LogicalVolume*);

  void PrintDimensions();
  void SetCopyNumber();                            
  void defineSensitiveDetector();

  G4double GetSizeZ()               {return CALSizeZ;}; 
  G4double GetSizeXY()              {return CALSizeXY;};

  G4double GetCALBarThickness()     {return CALBarZ;};
  G4int GetNbOfCALLayers()          {return NbOfCALLayers;}; 
  G4int GetNbOfCALBars()            {return NbOfCALBars;}; 
  G4int GetNbOfCALLayerBars()       {return NbOfCALLayerBars;};

  // Helper functions
  G4bool isVolumeBgoBar(G4String& volumename);
  G4bool isVolumeInsideCalorimeter(G4String& volumename);

private:
  void ParseBgoParametersFromGDML(); 


private:

 /* 
  G4Material*        defaultMaterial;
  G4Material*        CALMaterial;

  G4Box*             solidCAL;          // Calorimeter 
  G4LogicalVolume*   logicCAL;    
  G4VPhysicalVolume* physiCAL;    
 */

  G4GDMLParser*      fParser;
  G4LogicalVolume*   logicalBGO;
  G4LogicalVolume*   logicalBGOBar;


  G4double CALLayerSeparation;
  G4double CALBarsSeparation;
  //G4double CALBarThickness;
  //G4double CALBarLength;
  G4int NbOfCALLayers; 
  G4int NbOfCALLayerBars; 
  G4int NbOfCALBars;
  G4double CALSizeXY; 
  G4double CALSizeZ;

  G4double CALBarX;
  G4double CALBarY;
  G4double CALBarZ;

/*
  G4Box*             solidCALLayerX;  // Calorimeter PLANE X 
  G4LogicalVolume*   logicCALLayerX;
  G4VPhysicalVolume* physiCALLayerX;    

  G4Box*             solidCALLayerY;  // Calorimeter PLANE Y
  G4LogicalVolume*   logicCALLayerY;
  G4VPhysicalVolume* physiCALLayerY;    

  G4Box*             solidCALDetectorX;  // Calorimeter DETECTOR X
  G4LogicalVolume*   logicCALDetectorX;
  G4VPhysicalVolume* physiCALDetectorX;    

  G4Box*             solidCALDetectorY;  // Calorimeter DETECTOR Y
  G4LogicalVolume*   logicCALDetectorY;
  G4VPhysicalVolume* physiCALDetectorY;    
*/

  //DmpBgoDetectorMessenger* bgoDetectorMessenger;  //pointer to the Messenger
  DmpBgoSensitiveDetector*   bgoSensitiveDetector;  //pointer to the sensitive detector

  G4Region* aBgoRegion; // BGO cut region

//private:
    
//  void DefineMaterials();

};

#endif









