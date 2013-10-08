#ifndef DmpSimDetectorConstruction_h
#define DmpSimDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class DmpPsdDetectorDescription;
class DmpStkDetectorDescription;
class DmpBgoDetectorDescription;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4Region;
class DmpSimDetectorMessenger;

class DmpSimDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  
  DmpSimDetectorConstruction();
  ~DmpSimDetectorConstruction();
  
public:

  G4VPhysicalVolume* Construct();
  void UpdateGeometry();
  
  G4double GetWorldSizeZ()             {return WorldSizeZ;}; 
  G4double GetWorldSizeXY()            {return WorldSizeXY;};
  
  G4double GetPayloadSizeZ()           {return PayloadSizeZ;}; 
  G4double GetPayloadSizeXY()          {return PayloadSizeXY;};

  G4double GetPSDSizeZ()               {return PSDSizeZ;}; 
  G4double GetPSDSizeXY()              {return PSDSizeXY;};
  G4double GetSTKSizeZ()               {return STKSizeZ;}; 
  G4double GetSTKSizeXY()              {return STKSizeXY;};
  G4double GetBGOSizeZ()               {return BGOSizeZ;}; 
  G4double GetBGOSizeXY()              {return BGOSizeXY;};

  G4double GetBGOSTKDistance()         {return BGOSTKDistance;}; 
  G4double GetPSDSTKDistance()         {return PSDSTKDistance;}; 

  G4double    GetPSDCenter()  {return PSDCenter;};      
  G4double    GetSTKCenter()  {return STKCenter;};      
  G4double    GetBGOCenter()  {return BGOCenter;};      

  DmpPsdDetectorDescription* GetPsdDetectorDescription() { return dmpPsdDetectorDescription; }
  DmpStkDetectorDescription* GetStkDetectorDescription() { return dmpStkDetectorDescription; }
  DmpBgoDetectorDescription* GetBgoDetectorDescription() { return dmpBgoDetectorDescription; }

private:
  
  DmpPsdDetectorDescription* dmpPsdDetectorDescription;
  DmpStkDetectorDescription* dmpStkDetectorDescription;
  DmpBgoDetectorDescription* dmpBgoDetectorDescription;

  G4Material*        defaultMaterial;
 
  G4double PSDSizeXY;
  G4double PSDSizeZ;
  G4double STKSizeXY;
  G4double STKSizeZ;
  G4double BGOSizeXY;
  G4double BGOSizeZ;

  G4double PSDCenter;
  G4double STKCenter;
  G4double BGOCenter;

  G4double PSDSTKDistance;
  G4double BGOSTKDistance;

  G4double PayloadSizeZ;
  G4double PayloadSizeXY;
  
  G4double           WorldSizeXY;
  G4double           WorldSizeZ;
            
  G4Box*             solidWorld;        // World 
  G4LogicalVolume*   logicWorld;    
  G4VPhysicalVolume* physiWorld;    

  G4Box*             solidPayload;      // Payload 
  G4LogicalVolume*   logicPayload;    
  G4VPhysicalVolume* physiPayload;    
     
  G4Box*             solidPSD;
  G4LogicalVolume*   logicPSD;    
  G4VPhysicalVolume* physiPSD;    

  G4Box*             solidSTK;          
  G4LogicalVolume*   logicSTK;    
  G4VPhysicalVolume* physiSTK;    

  G4Box*             solidBGO;          
  G4LogicalVolume*   logicBGO;    
  G4VPhysicalVolume* physiBGO;    

  DmpSimDetectorMessenger*     detectorMessenger;     //pointer to the Messenger

private:
    
  void DefineMaterials();
  void ComputePayloadParameters();
  G4VPhysicalVolume* ConstructPayload();     
};

#endif









