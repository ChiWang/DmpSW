#ifndef DmpSimuRunEventNtupleMaker_h
#define DmpSimuRunEventNtupleMaker_h

#include "globals.hh"

class G4Run;
class G4Event;
class TTree;

class DmpSimuRunEventNtupleMaker
{
public:
  DmpSimuRunEventNtupleMaker();
  ~DmpSimuRunEventNtupleMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void FillEvent(const G4Event* evt);        

 private:
  TTree*   tree;    
  G4int  m_runNumber;

  int tt_run;
  int tt_event;
};
#endif

