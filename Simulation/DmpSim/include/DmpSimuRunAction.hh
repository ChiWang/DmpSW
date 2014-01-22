#ifndef DmpSimuRunAction_h
#define DmpSimuRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class DmpRootNtupleManager;
class DmpGenEvtRootNtupleManager;

class DmpSimuRunAction : public G4UserRunAction
{
public:
  DmpSimuRunAction(DmpRootNtupleManager*);
  ~DmpSimuRunAction();
  
public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

private:
  DmpRootNtupleManager* ntupleManager;

};

#endif



