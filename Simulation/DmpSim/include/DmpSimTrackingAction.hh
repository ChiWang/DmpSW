#ifndef  GammaRayTelTrackingAction_h
#define  GammaRayTelTrackingAction_h 1

#include "G4UserTrackingAction.hh"


class  DmpSimTrackingAction : public G4UserTrackingAction {

  public:
     DmpSimTrackingAction(){};
    virtual ~ DmpSimTrackingAction(){};
   
    virtual void PreUserTrackingAction(const G4Track*);

};

#endif
