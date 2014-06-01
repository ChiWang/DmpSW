/*
 *  $Id: DmpSimPsdSD.h, 2014-05-24 12:54:56 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/05/2014
*/

#ifndef DmpSimPsdSD_H
#define DmpSimPsdSD_H

#include "G4VSensitiveDetector.hh"

class TClonesArray;

class DmpSimPsdSD : public G4VSensitiveDetector{
/*
 *  DmpSimPsdSD
 *
 */
public:
  DmpSimPsdSD();
  ~DmpSimPsdSD();
  G4bool ProcessHits(G4Step*,G4TouchableHistory*);
  
  void Initialize(G4HCofThisEvent*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  TClonesArray  *fStripSet;
};

#endif

