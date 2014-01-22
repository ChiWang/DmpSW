#ifndef DmpSimuSteppingAction_h
#define DmpSimuSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DmpRootNtupleManager;

class DmpSimuSteppingAction : public G4UserSteppingAction
{
public:
  DmpSimuSteppingAction(DmpRootNtupleManager*);
  virtual ~DmpSimuSteppingAction();

  void UserSteppingAction(const G4Step*);
    
private:
  DmpRootNtupleManager* ntupleManager; 

};

#endif
