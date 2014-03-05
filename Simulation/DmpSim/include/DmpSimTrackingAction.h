/*
 *  $Id: DmpSimTrackingAction.h, 2014-03-05 16:29:31 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/03/2014
*/

#ifndef  DmpSimTrackingAction_H
#define  DmpSimTrackingAction_H

#include "G4UserTrackingAction.hh"

class  DmpSimTrackingAction : public G4UserTrackingAction {
public:
  DmpSimTrackingAction(){};
  ~DmpSimTrackingAction(){};

  void PreUserTrackingAction(const G4Track*);

};

#endif

