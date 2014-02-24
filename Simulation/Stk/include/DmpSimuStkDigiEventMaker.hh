#ifndef DmpSimuStkDigiEventMaker_h
#define DmpSimuStkDigiEventMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "TTree.h"
#include "DmpEvtStkDigit.hh"



class DmpSimuStkDigiEventMaker
{
public:
  
    DmpSimuStkDigiEventMaker();
  ~DmpSimuStkDigiEventMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillEvent(const G4Event* evt);
  //void FillStep(const G4Step* aStep);


  bool passTotalDigiCut(G4int cut);

 private:
  int debugEvent;
  int NbOfROChannels;

  TTree*   tree;
  const G4Run*   run;
  DmpEvtStkDigit* StkDigitEvt;

};


#endif

