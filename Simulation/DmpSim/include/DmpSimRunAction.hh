#ifndef DmpSimRunAction_h
#define DmpSimRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class DmpRootNtupleManager;

class DmpSimRunAction : public G4UserRunAction
{
public:
  DmpSimRunAction(DmpRootNtupleManager*);
  ~DmpSimRunAction();
  
public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

private:
  DmpRootNtupleManager* ntupleManager;

};

#endif



