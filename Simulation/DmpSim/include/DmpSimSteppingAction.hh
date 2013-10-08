#ifndef DmpSimSteppingAction_h
#define DmpSimSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DmpRootNtupleManager;

class DmpSimSteppingAction : public G4UserSteppingAction
{
public:
  DmpSimSteppingAction(DmpRootNtupleManager*);
  virtual ~DmpSimSteppingAction();

  void UserSteppingAction(const G4Step*);
    
private:
  DmpRootNtupleManager* ntupleManager; 

};

#endif
