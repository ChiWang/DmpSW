/* 
 *  $Id: DmpSimDetectorConstruction.h, 2014-02-26 20:57:16 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#ifndef DmpSimDetectorConstruction_H
#define DmpSimDetectorConstruction_H

#include "G4VUserDetectorConstruction.hh"

class G4GDMLParser;
class G4VPhysicalVolume;
class DmpSimDetectorMessenger;

class DmpSimDetectorConstruction : public G4VUserDetectorConstruction{
public:
  DmpSimDetectorConstruction();
  ~DmpSimDetectorConstruction();
  G4VPhysicalVolume* Construct();

  void UpdateGeometry();

private:
  G4GDMLParser              *fParser;
  G4VPhysicalVolume         *fPhysiWorld;    
  DmpSimDetectorMessenger   *fDetMessenger;

};

#endif

