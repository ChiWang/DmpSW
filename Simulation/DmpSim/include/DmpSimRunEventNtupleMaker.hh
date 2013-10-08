#ifndef DmpSimRunEventNtupleMaker_h
#define DmpSimRunEventNtupleMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

class TTree;

class DmpSimRunEventNtupleMaker
{
public:
  
  DmpSimRunEventNtupleMaker();
  ~DmpSimRunEventNtupleMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

 private:
  
  TTree*   tree;    

  G4int  m_runNumber;

  int tt_run;
  int tt_event;

};


#endif

