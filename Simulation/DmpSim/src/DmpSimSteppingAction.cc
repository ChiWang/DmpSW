// Description: This class hinerits from G4UserSteppingAction. It is used to
// access information during G4 stepping and store them into the ntuple
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpSimuSteppingAction.hh"

#include "DmpRootEventDataManager.hh"

#include "G4Step.hh"

DmpSimuSteppingAction::DmpSimuSteppingAction(DmpRootEventDataManager* rootEvtMgr)
  : rootEventDataManager(rootEvtMgr)
{ }

DmpSimuSteppingAction::~DmpSimuSteppingAction()
{ }

void DmpSimuSteppingAction::UserSteppingAction(const G4Step* aStep)
{

    rootEventDataManager->FillStep(aStep);

}


