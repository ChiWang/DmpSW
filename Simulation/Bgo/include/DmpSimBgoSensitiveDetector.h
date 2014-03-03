/*
 *  $Id: DmpSimBgoSensitiveDetector.h, 2014-03-03 22:46:29 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifndef DmpBgoSimSensitiveDetector_H
#define DmpBgoSimSensitiveDetector_H

#include "G4VSensitiveDetector.hh"
#include "DmpSimBgoHit.h"

class TClonesArray;
class DmpBgoSimSensitiveDetector : public G4VSensitiveDetector{
public:
  DmpBgoSimSensitiveDetector(G4String);
  ~DmpBgoSimSensitiveDetector();
  G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROHist);
  
  void Initialize(G4HCofThisEvent*);
  void EndOfEvent(G4HCofThisEvent*);

private:
  TClonesArray      *fBgoHits;
};

#endif

