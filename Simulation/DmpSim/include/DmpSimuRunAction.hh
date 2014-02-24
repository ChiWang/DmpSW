#ifndef DmpSimuRunAction_h
#define DmpSimuRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class DmpRootEventDataManager;
class DmpGenEvtRootNtupleManager;


class DmpSimuPrimaryGeneratorAction;

class DmpSimuRunAction : public G4UserRunAction
{
public:
  DmpSimuRunAction(DmpRootEventDataManager*, DmpSimuPrimaryGeneratorAction*);

  ~DmpSimuRunAction();
  
public:
  void BeginOfRunAction(const G4Run*);
 
  void EndOfRunAction(const G4Run*);
  
private:
  DmpRootEventDataManager* rootEventDataManager;
  DmpSimuPrimaryGeneratorAction* dmpSimuPrimaryGeneratorAction;
};

#endif



