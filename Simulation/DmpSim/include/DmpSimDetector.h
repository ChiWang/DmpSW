/* 
 *  $Id: DmpSimDetector.h, 2014-04-14 14:04:27 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#ifndef DmpSimDetector_H
#define DmpSimDetector_H

#include "G4VUserDetectorConstruction.hh"
#include "DmpDetectorID.h"

class G4GDMLParser;

class DmpSimDetector : public G4VUserDetectorConstruction{
/*
 *
 *
 */
public:
  DmpSimDetector();
  ~DmpSimDetector();
  G4VPhysicalVolume* Construct();
  void SetSatGdml(const std::string &argv) {fSatGdmlPath = argv;}
  void SetGdml(DmpDetector::DmpEDetectorID id,const std::string &argv) {fGdmlPath[id] = argv;}
  void SetOffset(DmpDetector::DmpEDetectorID id,const float &v) {fOffset[id] = v;}

private:
  std::string            fSatGdmlPath;       // must set it in JobOpt file
  G4GDMLParser          *fSatParser;
  G4VPhysicalVolume     *fSatPhyVolume;

private:
  std::string           fGdmlPath[DmpDetector::gSubDetNo];
  G4GDMLParser          *fParser[DmpDetector::gSubDetNo];
  G4VPhysicalVolume     *fPhyVolume[DmpDetector::gSubDetNo];
  float         fOffset[DmpDetector::gSubDetNo];        // sudDet center --> Sat center
};

#endif


