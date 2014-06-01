/*
 *  $Id: DmpSimBgoSD.h, 2014-05-22 17:04:23 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifndef DmpSimBgoSD_H
#define DmpSimBgoSD_H

#include "G4VSensitiveDetector.hh"

class TClonesArray;

class DmpSimBgoSD : public G4VSensitiveDetector{
/*
 *  DmpSimBgoSD
 *
 */
public:
  DmpSimBgoSD();
  ~DmpSimBgoSD();
  G4bool ProcessHits(G4Step*,G4TouchableHistory*);
  
  void Initialize(G4HCofThisEvent*);
  void EndOfEvent(G4HCofThisEvent*);

private:
  TClonesArray      *fBarSet;

};

#endif

