#ifndef DmpSimRunAction_H
#define DmpSimRunAction_H

#include "G4UserRunAction.hh"
//#include "globals.hh"

class DmpSimRunAction : public G4UserRunAction{
public:
  DmpSimRunAction();
  ~DmpSimRunAction();
  
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
  
private:
};

#endif


