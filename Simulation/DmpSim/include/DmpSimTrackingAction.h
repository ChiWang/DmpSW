#ifndef  GammaRayTelTrackingAction_h
#define  GammaRayTelTrackingAction_h 1

#include "G4UserTrackingAction.hh"


class  DmpSimuTrackingAction : public G4UserTrackingAction {

  public:
     DmpSimuTrackingAction(){};
    virtual ~ DmpSimuTrackingAction(){};
   
    virtual void PreUserTrackingAction(const G4Track*);

};

#endif
