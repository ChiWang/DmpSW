#ifndef DmpPsdDetectorDescription_h
#define DmpPsdDetectorDescription_h 1

#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class G4Region;
class G4VSolid;
class G4GDMLParser;

//class DmpPsdDetectorMessenger;
class DmpPsdSensitiveDetector;

class DmpPsdDetectorDescription
{
public:
  
  DmpPsdDetectorDescription(G4GDMLParser* gdmlParser);
  ~DmpPsdDetectorDescription();
  
public:  
  void ComputeParameters();
 // void Construct(G4VPhysicalVolume*, G4LogicalVolume*);
  void PrintDimensions();
  void SetCopyNumber();
  void defineSensitiveDetector();

  inline G4double GetSizeZ()    {return PSDSizeZ;};
  inline G4double GetSizeXY()  {return PSDSizeXY;};
  inline G4int GetNbOfPSDStrips()  {return NbOfPSDStrips;};

  // Helper functions
  G4bool isVolumeInPSD(G4String& volumename);

protected:
  void ParsePsdParametersFromGDML();

private:
  
  G4GDMLParser*      fParser;

  G4LogicalVolume*   logicPSD;
  G4LogicalVolume* logicStrip_A;
  G4LogicalVolume* logicStrip_B;

  G4int NbOfPSDStrips;
  G4int NbOfLayerStrips;
  G4int NbOfLayers;
  G4int NbOfBottomSublayerStrips;
  G4int NbOfUpSublayerStrips;
  G4double stripBodyLength;
  G4double stripHeadLength;
  G4double stripWidthA;
  G4double stripWidthB;
  G4double stripThickness;
  G4double stripGap;
  G4double layerGap;
  G4double sublayerGap;

  G4double PSDSizeXY; 
  G4double PSDSizeZ;
  G4double PSDMainBodyZ;
  G4double PSDCenter;

  //DmpPsdDetectorMessenger* psdDetectorMessenger;  //pointer to the Messenger
  DmpPsdSensitiveDetector*   psdSensitiveDetector;  //pointer to the sensitive detector

  G4Region* aPsdRegion; // PSD cut region
};

#endif









