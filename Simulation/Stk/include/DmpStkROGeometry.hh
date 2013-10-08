#ifndef DmpStkROGeometry_h
#define DmpStkROGeometry_h 1

#include "G4VReadOutGeometry.hh"

class DmpDetectorConstruction;

class DmpStkROGeometry : public G4VReadOutGeometry
{
public:
  DmpStkROGeometry();
  DmpStkROGeometry(G4String);
  ~DmpStkROGeometry();

protected:

  G4VPhysicalVolume* Build();

private:
  DmpDetectorConstruction* dmpDetector;
  //pointer to the geometry
};

#endif


