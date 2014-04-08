/* 
 *  $Id: DmpSimDetectorConstruction.h, 2014-04-08 13:55:40 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#ifndef DmpSimDetectorConstruction_H
#define DmpSimDetectorConstruction_H

#include "G4VUserDetectorConstruction.hh"

#include "DmpDetectorID.h"

class G4GDMLParser;

class DmpSimDetectorConstruction : public G4VUserDetectorConstruction{
public:
  DmpSimDetectorConstruction();
  ~DmpSimDetectorConstruction();
  G4VPhysicalVolume* Construct();

private:
  G4GDMLParser              *fParser[DmpDetector::gSubDetNo + 1];
  G4VPhysicalVolume         *fPhysiVol[DmpDetector::gSubDetNo + 1];

};

#endif

