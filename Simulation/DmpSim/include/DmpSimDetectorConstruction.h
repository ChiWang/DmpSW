/* 
 *  $Id: DmpSimDetectorConstruction.h, 2014-03-03 23:02:22 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#ifndef DmpSimDetectorConstruction_H
#define DmpSimDetectorConstruction_H

#include "G4VUserDetectorConstruction.hh"

#include "DmpCore.h"

// *
// *  TODO: binding set functions into python and control in python script, instead of using meseengers
// *
class G4GDMLParser;

class DmpSimDetectorConstruction : public G4VUserDetectorConstruction{
public:
  DmpSimDetectorConstruction();
  ~DmpSimDetectorConstruction();
  G4VPhysicalVolume* Construct();

private:
  G4GDMLParser      *fParser;

public:
  static void SetGdmlPath(DmpCore::DmpEDetectorID,std::string);
  static std::string GetGdmlPath(const DmpCore::DmpEDetectorID&);

private:
  static std::string    sGdmlPath[DmpCore::gSubDetNo];
};

#endif

