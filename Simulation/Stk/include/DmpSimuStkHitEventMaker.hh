#ifndef DmpSimuStkHitEventMaker_h
#define DmpSimuStkHitEventMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "TTree.h"
#include "DmpEvtStkHit.hh"



class DmpSimuStkHitEventMaker
{
public:
  
  DmpSimuStkHitEventMaker();
  ~DmpSimuStkHitEventMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillEvent(const G4Event* evt);

  //void FillStep(const G4Step* aStep);

 private:
  int debugEvent;
  int eventNumber;
  TTree*             tree;
  const G4Run*        run;
  DmpEvtStkHit* StkHitEvt;

};


#endif

