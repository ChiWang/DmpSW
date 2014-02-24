#ifndef DMPSIMUBgoHITEVENTMAKER_HH
#define DMPSIMUBgoHITEVENTMAKER_HH

#include "globals.hh"

class TTree;
class G4Run;
class G4Event;
class DmpEvtBgoHit;

class DmpSimuBgoHitEventMaker
{
public:
  DmpSimuBgoHitEventMaker();
  ~DmpSimuBgoHitEventMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillEvent(const G4Event* evt);        

  G4bool passTotalEnergyCut(G4double cut);

 private:
  TTree*   tree;    
  G4int  debugEvent;
  G4int  eventNumber;
  DmpEvtBgoHit *BgoHitEvt;

};

#endif

