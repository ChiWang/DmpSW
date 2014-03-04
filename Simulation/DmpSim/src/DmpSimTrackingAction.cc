/*
 *  $Id: DmpSimTrackingAction.cc, 2014-03-04 17:46:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/03/2014
*/

#include "G4TrackingManager.hh"
#include "G4Track.hh"

#include "DmpSimTrackingAction.h"

void DmpSimTrackingAction::PreUserTrackingAction(const G4Track* aTrack){
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

