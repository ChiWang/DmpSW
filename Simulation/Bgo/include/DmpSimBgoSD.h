/*
 *  $Id: DmpSimBgoSD.h, 2014-03-04 21:25:49 chi $
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
 *  update fDataMan->UpdateThisHit(SubDet_ID) in ProcessHits()
 *
 */
public:
  DmpSimBgoSD(G4String);
  ~DmpSimBgoSD();
  G4bool ProcessHits(G4Step*,G4TouchableHistory*);
  
  void Initialize(G4HCofThisEvent*);
  void EndOfEvent(G4HCofThisEvent*);

private:
  TClonesArray      *fMSDSet;
};

#endif

