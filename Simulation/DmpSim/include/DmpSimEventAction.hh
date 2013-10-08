#ifndef DmpSimEventAction_h
#define DmpSimEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class DmpRootNtupleManager;

class DmpSimEventAction : public G4UserEventAction
{
public:

  DmpSimEventAction(DmpRootNtupleManager*);
  virtual ~DmpSimEventAction();
  
public:
  virtual void   BeginOfEventAction(const G4Event*);
  virtual void   EndOfEventAction(const G4Event*);
  
  void SetDrawFlag   (G4String val)  {drawFlag = val;};
  
private:

  G4int       stkHitCollID;                
  G4int       bgoHitCollID;                
  G4int       psdHitCollID;                
  G4String    drawFlag;

  DmpRootNtupleManager* ntupleManager; 
};

#endif

    





