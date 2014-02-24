#ifndef DmpSimuRunEventHeaderMaker_h
#define DmpSimuRunEventHeaderMaker_h 1

#include "DmpEvtSimuHeader.h"
#include "DmpRunSimuHeader.h"
#include "DmpSimuPrimaryGeneratorAction.hh"
//#include "G4VUserPrimaryGeneratorAction.hh"


#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"
//#include "G4ParticleGun.hh"
//#include "G4GeneralParticleSource.hh"


class TTree;

//class DmpSimuPrimaryGeneratorAction;

class DmpSimuRunEventHeaderMaker
{
public:
  
  DmpSimuRunEventHeaderMaker();
  ~DmpSimuRunEventHeaderMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        
  
  void beginRun(const G4Run* aRun, TTree* aTree);
  void FillRun(const G4Run* aRun, DmpSimuPrimaryGeneratorAction* );



 private:
  
  TTree*   tree;
  TTree*   treeRun;
  
  G4int  m_runNumber;
  DmpEvtSimuHeader* dmpSimuEventHeader;
  DmpRunSimuHeader* dmpSimuRunHeader;
  
 
  //DmpSimuPrimaryGeneratorAction* dmpSimuPrimaryGeneratorAction;
  
};


#endif

