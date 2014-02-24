#ifndef DmpDetectorConstruction_h
#define DmpDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4GDMLParser.hh"
#include "globals.hh"

#include "DmpPsdDetectorDescription.hh"
#include "DmpStkDetectorDescription.hh"
#include "DmpBgoDetectorDescription.hh"
#include "DmpNudDetectorDescription.hh"

/*
class DmpPsdDetectorDescription;
class DmpStkDetectorDescription;
class DmpBgoDetectorDescription;
*/
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4Region;
class DmpDetectorMessenger;

class DmpDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  
  DmpDetectorConstruction();
  ~DmpDetectorConstruction();
  
public:

  G4VPhysicalVolume* Construct();
  G4VPhysicalVolume* ConstructGDML();
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
  G4double GetNUDSizeZ()               {return NUDSizeZ;};
  G4double GetNUDSizeXY()              {return NUDSizeXY;};



  //G4double GetBGOSTKDistance()         {return BGOSTKDistance;};
  //G4double GetPSDSTKDistance()         {return PSDSTKDistance;};

  G4double    GetPSDCenter()  {return PSDCenter;};      
  G4double    GetSTKCenter()  {return STKCenter;};      
  G4double    GetBGOCenter()  {return BGOCenter;};
  G4double    GetNUDCenter()  {return NUDCenter;};

  DmpPsdDetectorDescription* GetPsdDetectorDescription() { return dmpPsdDetectorDescription; }
  DmpStkDetectorDescription* GetStkDetectorDescription() { return dmpStkDetectorDescription; }
  DmpBgoDetectorDescription* GetBgoDetectorDescription() { return dmpBgoDetectorDescription; }
  DmpNudDetectorDescription* GetNudDetectorDescription() { return dmpNudDetectorDescription; }

  // Helper functions
  G4bool isWorldVolume(const G4String& volumename);
  G4int  getDetectorIndex(G4String& volumename);

private:
  
  G4GDMLParser* fParser;

  DmpPsdDetectorDescription* dmpPsdDetectorDescription;
  DmpStkDetectorDescription* dmpStkDetectorDescription;
  DmpBgoDetectorDescription* dmpBgoDetectorDescription;
  DmpNudDetectorDescription* dmpNudDetectorDescription;

  G4Material*        defaultMaterial;
 
  G4double PSDSizeXY;
  G4double PSDSizeZ;
  G4double STKSizeXY;
  G4double STKSizeZ;
  G4double BGOSizeXY;
  G4double BGOSizeZ;
  G4double NUDSizeXY;
  G4double NUDSizeZ;

  G4double PSDCenter;
  G4double STKCenter;
  G4double BGOCenter;
  G4double NUDCenter;

  //G4double PSDSTKDistance;
  //G4double BGOSTKDistance;

  G4double PayloadSizeZ;
  G4double PayloadSizeXY;
  
  G4double           WorldSizeXY;
  G4double           WorldSizeZ;
            
  G4Box*             solidWorld;        // World 
  G4LogicalVolume*   logicWorld;    
  G4VPhysicalVolume* physiWorld;    

  //G4Box*             solidHalfPosWorld;        // HalfPosWorld 
  //G4LogicalVolume*   logicHalfPosWorld;    
  //G4VPhysicalVolume* physiHalfPosWorld;  

  //G4Box*             solidHalfNegWorld;        // HalfNegWorld 
  //G4LogicalVolume*   logicHalfNegWorld;    
  //G4VPhysicalVolume* physiHalfNegWorld;  


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

  G4Box*             solidNUD;
  G4LogicalVolume*   logicNUD;
  G4VPhysicalVolume* physiNUD;

  DmpDetectorMessenger*     detectorMessenger;     //pointer to the Messenger

private:
    
  void ComputePayloadParameters();
  //G4VPhysicalVolume* ConstructPayload();
};

#endif









