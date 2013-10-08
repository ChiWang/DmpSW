#ifndef DmpSimDetectorDescriptionBgo_h
#define DmpSimDetectorDescriptionBgo_h 1

#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4Region;

//class DmpBgoDetectorMessenger;
class DmpSimSensitiveDetectorBgo;

class DmpSimDetectorDescriptionBgo
{
public:
  
  DmpSimDetectorDescriptionBgo();
  ~DmpSimDetectorDescriptionBgo();
  
public:
  
  void ComputeParameters();
  void Construct(G4VPhysicalVolume*, G4LogicalVolume*);

  G4double GetSizeZ()               {return CALSizeZ;}; 
  G4double GetSizeXY()              {return CALSizeXY;};

  G4double GetCALBarThickness()     {return CALBarThickness;};
  G4int GetNbOfCALLayers()          {return NbOfCALLayers;}; 
  G4int GetNbOfCALBars()            {return NbOfCALBars;}; 

private:
  
  G4Material*        defaultMaterial;
  G4Material*        CALMaterial;

  G4Box*             solidCAL;          // Calorimeter 
  G4LogicalVolume*   logicCAL;    
  G4VPhysicalVolume* physiCAL;    

  G4double CALLayerSeparation;
  G4double CALBarsSeparation;
  G4double CALBarThickness;
  G4double CALBarLength;
  G4int NbOfCALLayers; 
  G4int NbOfCALBars; 
  G4double CALSizeXY; 
  G4double CALSizeZ;

  G4double CALBarX;
  G4double CALBarY;
  G4double CALBarZ;

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

  //DmpBgoDetectorMessenger* bgoDetectorMessenger;  //pointer to the Messenger
  DmpSimSensitiveDetectorBgo*   bgoSensitiveDetector;  //pointer to the sensitive detector

  G4Region* aBgoRegion; // BGO cut region

private:
    
  void DefineMaterials();

};

#endif









