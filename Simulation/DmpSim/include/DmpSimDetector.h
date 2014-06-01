/* 
 *  $Id: DmpSimDetector.h, 2014-05-08 11:44:48 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2014
*/

#ifndef DmpSimDetector_H
#define DmpSimDetector_H

#include "G4VUserDetectorConstruction.hh"
#include "DmpDetectorID.h"

class G4GDMLParser;
class DmpSimPsdSD;
class DmpSimStkSD;
class DmpSimBgoSD;
class DmpSimNudSD;

class DmpSimDetector : public G4VUserDetectorConstruction{
/*
 *
 *
 */
public:
  DmpSimDetector();
  ~DmpSimDetector();
  G4VPhysicalVolume* Construct();
  static void SetGdml(const std::string &argv) {fGdmlPath = argv;}

private:
  static std::string       fGdmlPath;          // must set it in JobOpt file
  G4GDMLParser      *fParser;
  G4VPhysicalVolume *fPhyVolume;

private:
  DmpSimPsdSD       *fPsdSD;
  DmpSimStkSD       *fStkSD;
  DmpSimBgoSD       *fBgoSD;
  DmpSimNudSD       *fNudSD;

};

#endif


