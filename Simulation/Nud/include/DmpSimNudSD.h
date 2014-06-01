/*
 *  $Id: DmpSimNudSD.h, 2014-05-22 17:15:53 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifndef DmpSimNudSD_H
#define DmpSimNudSD_H

#include "G4VSensitiveDetector.hh"

class TClonesArray;

class DmpSimNudSD : public G4VSensitiveDetector{
/*
 *  DmpSimNudSD
 *
 *  update fDataMan->UpdateThisHit(SubDet_ID) in ProcessHits()
 *
 */
public:
  DmpSimNudSD();
  ~DmpSimNudSD();
  G4bool ProcessHits(G4Step*,G4TouchableHistory*);
  
  void Initialize(G4HCofThisEvent*);
  void EndOfEvent(G4HCofThisEvent*);

private:
  TClonesArray      *fBlockSet;
};

#endif

