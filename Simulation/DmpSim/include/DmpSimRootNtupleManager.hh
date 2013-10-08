#ifndef DmpSimRootNtupleManager_h
#define DmpSimRootNtupleManager_h 1

#include <vector>
#include "globals.hh"
#include "G4Run.hh"
#include "G4Event.hh"

class DmpSimRunEventNtupleMaker;
class DmpSimPrimariesNtupleMaker;
class DmpSimStkStepNtupleMaker;
class DmpSimTrajectoryNtupleMaker;
class DmpSimBgoHitNtupleMaker;
class DmpSimStkHitNtupleMaker;
class DmpSimStkDigiNtupleMaker;

class TFile;
class TTree;
class TH1D;

class DmpSimRootNtupleManager
{
  public:
  
    DmpSimRootNtupleManager();
   ~DmpSimRootNtupleManager();
   
    void book(const G4Run* aRun);
    void save();

    void beginEvent(const G4Event* evt);
    void FillStep(const G4Step* aStep);
    void FillEvent(const G4Event* evt);        

 private:
  
  DmpSimRunEventNtupleMaker*     dmpSimRunEventNtupleMaker;
  DmpSimPrimariesNtupleMaker*    dmpSimPrimariesNtupleMaker;
  DmpSimStkStepNtupleMaker*      dmpSimStkStepNtupleMaker;
  DmpSimTrajectoryNtupleMaker*   dmpSimTrajectoryNtupleMaker;
  DmpSimBgoHitNtupleMaker*       dmpSimBgoHitNtupleMaker;
  DmpSimStkHitNtupleMaker*       dmpSimStkHitNtupleMaker;
  DmpSimStkDigiNtupleMaker*      dmpSimStkDigiNtupleMaker;

  TFile*   rootFile;
  TTree*   tree;    

};


#endif

