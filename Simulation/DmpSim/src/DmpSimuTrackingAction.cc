// Description: This class hinerits from G4UserTrackingAction and implements
// its PreUserTrackingAction method to select track trajectories to be stored 
// in event store for later analysis
//
// Author(s):
//  - creation by X.Wu, 09/07/2013

#include "DmpSimuTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"

void DmpSimuTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  // Create trajectory only for primaries
  if(aTrack->GetParentID()==0) { 
    fpTrackingManager->SetStoreTrajectory(true);
  }
  // also e+ and e- from primary photon conversion
  else if(aTrack->GetParentID()==1 && aTrack->GetDefinition()->GetPDGCharge() != 0.) { 
    fpTrackingManager->SetStoreTrajectory(true); 
  }
  else { 
    fpTrackingManager->SetStoreTrajectory(false); 
  }
}


