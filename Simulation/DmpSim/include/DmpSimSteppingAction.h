#ifndef DmpSimuSteppingAction_h
#define DmpSimuSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DmpRootEventDataManager;

class DmpSimuSteppingAction : public G4UserSteppingAction
{
public:
  DmpSimuSteppingAction(DmpRootEventDataManager*);
  virtual ~DmpSimuSteppingAction();

  void UserSteppingAction(const G4Step*);
    
private:
  DmpRootEventDataManager* rootEventDataManager;

};

#endif
