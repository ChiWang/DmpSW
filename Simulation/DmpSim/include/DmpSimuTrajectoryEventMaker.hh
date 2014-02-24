#ifndef DmpSimuTrajectoryEventMaker_h
#define DmpSimuTrajectoryEventMaker_h 1

#include "DmpEvtSimuTrajectory.h"
#include "DmpDetectorConstruction.hh"

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

class TTree;

class DmpSimuTrajectoryEventMaker
{
public:
  
  DmpSimuTrajectoryEventMaker();
  ~DmpSimuTrajectoryEventMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

 private:
  
  TTree*   tree;    
  G4int  debugEvent;
  G4int  eventNumber;
  DmpDetectorConstruction* dmpDetector;


  DmpEvtSimuTrajectory* dmpSimuTrajectoryEvent;
};


#endif

