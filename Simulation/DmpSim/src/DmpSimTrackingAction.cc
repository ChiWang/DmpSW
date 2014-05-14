/*
 *  $Id: DmpSimTrackingAction.cc, 2014-05-14 15:35:24 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/03/2014
*/

#include "G4TrackingManager.hh"
#include "G4Track.hh"

#include "DmpSimTrackingAction.h"

void DmpSimTrackingAction::PreUserTrackingAction(const G4Track* aTrack){
  if(aTrack->GetDefinition()->GetPDGCharge() == 0){
    fpTrackingManager->SetStoreTrajectory(false);
  }else{
    fpTrackingManager->SetStoreTrajectory(true);
  }
        /*
  if(aTrack->GetParentID()==0) {        // Create trajectory only for primaries
    fpTrackingManager->SetStoreTrajectory(true);        // then will affect what??
  }else if(aTrack->GetParentID()==1 && aTrack->GetDefinition()->GetPDGCharge() != 0.) { // also e+ and e- from primary photon conversion
    fpTrackingManager->SetStoreTrajectory(true); 
  }else {
    //fpTrackingManager->SetStoreTrajectory(false);
  }
  */
}

