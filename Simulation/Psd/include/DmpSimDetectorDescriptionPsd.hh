#ifndef DmpSimDetectorDescriptionPsd_h
#define DmpSimDetectorDescriptionPsd_h 1

#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class G4Region;

//class DmpPsdDetectorMessenger;
class DmpSimSensitiveDetectorPsd;

class DmpSimDetectorDescriptionPsd
{
public:
  
  DmpSimDetectorDescriptionPsd();
  ~DmpSimDetectorDescriptionPsd();
  
public:
  
  void ComputeParameters();
  void Construct(G4VPhysicalVolume*, G4LogicalVolume*);

  G4double GetSizeZ()               {return PSDSizeZ;}; 
  G4double GetSizeXY()              {return PSDSizeXY;};

  G4int GetNbOfPSDStrips()        {return NbOfPSDStrips;}; 

private:
  
  G4Material*        defaultMaterial;
  G4Material*        PSDMaterial;

  G4Box*             solidPSD;           
  G4LogicalVolume*   logicPSD;    
  G4VPhysicalVolume* physiPSD;    

  G4Box*             solidPSDDetector;           
  G4LogicalVolume*   logicPSDDetector;    
  G4VPhysicalVolume* physiPSDDetector;    


  G4int NbOfPSDStrips;

  G4double PSDThickness;
  G4double PSDSizeXY; 
  G4double PSDSizeZ; 

  //DmpPsdDetectorMessenger* psdDetectorMessenger;  //pointer to the Messenger
  DmpSimSensitiveDetectorPsd*   psdSensitiveDetector;  //pointer to the sensitive detector

  G4Region* aPsdRegion; // PSD cut region

private:
    
  void DefineMaterials();

};

#endif









