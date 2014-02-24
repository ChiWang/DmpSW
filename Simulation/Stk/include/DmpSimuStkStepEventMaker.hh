#ifndef DmpSimuStkStepEventMaker_h
#define DmpSimuStkStepEventMaker_h 1

#include "DmpDetectorConstruction.hh"

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

#include "DmpEvtStkStep.hh"

class TTree;

class DmpSimuStkStepEventMaker
{
public:
  
  DmpSimuStkStepEventMaker();
  ~DmpSimuStkStepEventMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

 private:
  
  DmpDetectorConstruction* dmpDetector;

  TTree*   tree;    

  G4int  debugEvent;

  G4int  eventNumber;

  G4bool is_pvtrack;
  G4bool is_eletrack;
  G4bool is_postrack;
  G4bool is_backtrack;
  G4int  pvtrackID;
  G4int  eletrackID;
  G4int  postrackID;
  G4int  currentTrackID;

  G4double eDepositAcc_pvtrack;
  G4double eDepositAcc_ele;
  G4double eDepositAcc_pos;
  G4double eDepositAcc_back;

  DmpEvtStkStep* dmpStkStepEvent;
};


#endif

