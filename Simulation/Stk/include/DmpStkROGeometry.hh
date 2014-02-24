#ifndef DmpStkROGeometry_h
#define DmpStkROGeometry_h 1

#include "G4VReadOutGeometry.hh"
#include "G4GDMLParser.hh"

class DmpDetectorConstruction;

class DmpStkROGeometry : public G4VReadOutGeometry
{
public:
  DmpStkROGeometry();
  DmpStkROGeometry(G4String aString, G4GDMLParser* aParser);
  ~DmpStkROGeometry();

protected:

  G4VPhysicalVolume* Build();

private:
  G4GDMLParser* fParser;
  DmpDetectorConstruction* dmpDetector;  //pointer to the geometry
};

#endif


