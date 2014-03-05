/*
 *  $Id: DmpSimTrackingAction.cc, 2014-03-05 16:34:46 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/03/2014
*/

#include "G4TrackingManager.hh"
#include "G4Track.hh"

#include "DmpSimTrackingAction.h"

void DmpSimTrackingAction::PreUserTrackingAction(const G4Track* aTrack){
  if(aTrack->GetParentID()==0) {        // Create trajectory only for primaries
    fpTrackingManager->SetStoreTrajectory(true);        // then will affect what??
  }else if(aTrack->GetParentID()==1 && aTrack->GetDefinition()->GetPDGCharge() != 0.) { // also e+ and e- from primary photon conversion
    fpTrackingManager->SetStoreTrajectory(true); 
  }else {
    fpTrackingManager->SetStoreTrajectory(false); 
  }
}

