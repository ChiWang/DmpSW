#ifndef DmpNudDetectorDescription_h
#define DmpNudDetectorDescription_h 1

#include "globals.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4UniformMagField;
class G4Region;
class G4GDMLParser;

//class DmpPsdDetectorMessenger;
class DmpNudSensitiveDetector;

class DmpNudDetectorDescription
{
public:
  
   DmpNudDetectorDescription(G4GDMLParser* gdmlParser);
  ~DmpNudDetectorDescription();
  
public:
  
  void ComputeParameters();
  void defineSensitiveDetector();
  G4double GetSizeZ()               {return NUDSizeZ;}; 
  G4double GetSizeXY()              {return NUDSizeXY;};
  G4int GetNbOfNUDStrips()          {return NbOfNUDStrips;}; 

protected:
  void ParseNudParametersFromGDML();

private:
  G4GDMLParser*      fParser;           
  G4LogicalVolume*   logicNUD;             
  G4LogicalVolume*   logicNUDDet0; 
  G4LogicalVolume*   logicNUDDet1; 
  G4LogicalVolume*   logicNUDDet2; 
  G4LogicalVolume*   logicNUDDet3; 
  G4LogicalVolume*   logicNUDShell0;    
  G4LogicalVolume*   logicNUDShell1;    
  G4int NbOfNUDStrips;
  G4double NUDThickness;
  G4double NUDSizeXY; 
  G4double NUDSizeZ; 
  G4double NUDCenter;
  G4double NUD_shell_gap_up;
  G4double NUD_shell_gap_low;
  DmpNudSensitiveDetector*   nudSensitiveDetector;  //pointer to the sensitive detector

  G4Region* aNudRegion; // PSD cut region

};

#endif









