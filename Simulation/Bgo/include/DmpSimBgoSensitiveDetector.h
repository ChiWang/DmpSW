/*
 *  $Id: DmpSimBgoSensitiveDetector.h, 2014-03-03 21:42:24 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifndef DmpBgoSimSensitiveDetector_H
#define DmpBgoSimSensitiveDetector_H

#include "G4VSensitiveDetector.hh"
#include "DmpSimBgoHit.h"

class DmpBgoSimSensitiveDetector : public G4VSensitiveDetector{
public:
  DmpBgoSimSensitiveDetector(G4String);
  ~DmpBgoSimSensitiveDetector();
  G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROHist);
  
  void Initialize(G4HCofThisEvent*);
  void EndOfEvent(G4HCofThisEvent*);

private:
  DmpSimBgoHitsCollection*  BGOHitCollection;      

  G4int (*ChitXID);
  G4int (*ChitYID);

  G4int NbOfCALLayers;
  G4int NbOfCALLayerBars; 
  G4int NbOfCALChannels; 

  G4double m_attenuation; //light attenuation constant
};

#endif

