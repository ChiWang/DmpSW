#ifndef DmpSimuNudHitEventMaker_h
#define DmpSimuNudHitEventMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

#include "DmpEvtNudHit.hh"

class TTree;

class DmpSimuNudHitEventMaker
{
public:
  
  DmpSimuNudHitEventMaker();
  ~DmpSimuNudHitEventMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);

  G4bool passTotalEnergyCut(G4double cut);

 private:

  TTree*   tree;    
  G4int  debugEvent;
  G4int  eventNumber;

  DmpEvtNudHit* dmpEvtNudHit;


};


#endif

