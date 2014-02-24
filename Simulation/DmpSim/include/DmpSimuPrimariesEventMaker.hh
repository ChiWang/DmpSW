#ifndef DmpSimuPrimariesEventMaker_h
#define DmpSimuPrimariesEventMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

#include "DmpEvtSimuPrimaries.h"

class TTree;

class DmpSimuPrimariesEventMaker
{
public:
  
  DmpSimuPrimariesEventMaker();
  ~DmpSimuPrimariesEventMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

 private:
  
  TTree* tree;
  G4int  debugEvent;
  G4int  eventNumber;

  DmpEvtSimuPrimaries* dmpSimuPrimariesEvent;

};


#endif

