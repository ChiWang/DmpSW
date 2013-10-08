// Description: This class hinerits from G4UserSteppingAction. It is used to
// access information during G4 stepping and store them into the ntuple
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpSimSteppingAction.hh"

#include "DmpSimRootNtupleManager.hh"

#include "G4Step.hh"

DmpSimSteppingAction::DmpSimSteppingAction(DmpSimRootNtupleManager* ntupleMgr)
  : ntupleManager(ntupleMgr)					 
{ }

DmpSimSteppingAction::~DmpSimSteppingAction()
{ }

void DmpSimSteppingAction::UserSteppingAction(const G4Step* aStep)
{

  ntupleManager->FillStep(aStep); 

}


