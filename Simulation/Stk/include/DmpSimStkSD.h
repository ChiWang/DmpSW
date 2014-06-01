/*
 *  $Id: DmpSimStkSD.h, 2014-05-25 09:29:31 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/05/2014
*/

#ifndef DmpSimStkSD_H
#define DmpSimStkSD_H

#include "G4VSensitiveDetector.hh"

class TClonesArray;

class DmpSimStkSD : public G4VSensitiveDetector{
/*
 *  DmpSimStkSD
 *
 */
public:
  DmpSimStkSD();
  ~DmpSimStkSD();
  G4bool ProcessHits(G4Step*,G4TouchableHistory*);
  
  void Initialize(G4HCofThisEvent*);
  void EndOfEvent(G4HCofThisEvent*);

private:
  TClonesArray      *fLadderSet;
};

#endif

