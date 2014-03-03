/*
 *  $Id: DmpSimEventAction.h, 2014-03-03 23:30:30 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifndef DmpSimEventAction_H
#define DmpSimEventAction_H

#include "G4UserEventAction.hh"
//#include "globals.hh"

class DmpSimEventAction : public G4UserEventAction{
public:
  DmpSimEventAction();
  ~DmpSimEventAction();
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  
  void SetDrawFlag   (G4String val)  {drawFlag = val;};
  
private:
  G4int       stkHitCollID;                
  G4int       bgoHitCollID;                
  G4int       psdHitCollID;                
  G4String    drawFlag;
};

#endif

    

