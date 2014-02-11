#ifndef DmpRootNtupleManager_h
#define DmpRootNtupleManager_h 1

#include <vector>
#include "globals.hh"
#include "G4Run.hh"
#include "G4Event.hh"

class DmpSimuRunEventNtupleMaker;
class DmpSimuPrimariesNtupleMaker;
class DmpSimuStkStepNtupleMaker;
class DmpSimuTrajectoryNtupleMaker;
class DmpSimuBgoHitNtupleMaker;
class DmpSimuStkHitNtupleMaker;
class DmpSimuStkDigiNtupleMaker;
class DmpSimuPsdHitNtupleMaker;

class TFile;
class TTree;
class TH1D;

class DmpRootNtupleMessenger;

class DmpRootNtupleManager{
public:
  DmpRootNtupleManager();
  ~DmpRootNtupleManager();
  
  void book(const G4Run* aRun);
  void save();
  
  void endEvent(const G4Event* evt);
  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        
  
  void SetRootGenDebug(G4bool val)     { nRootGenDebug    = val;}
  void SetRootFile(G4String val)       { nRootFile        = val;}
  void SetCalEcut(G4double val)        { calEcut          = val;}
  void SetSiDigicut(G4int val)         { siDigicut        = val;}
  void SetGenerationOnly(G4bool val)   { generationOnly = val;}
  void SetKeepOnlyDownward(G4bool val) { keepOnlyDownward = val;}
  TTree* GetGenTree()                  { return treeGen; }
  DmpSimuPrimariesNtupleMaker* GetDmpSimuPrimariesNtupleMaker() 
  G4bool GenerationOnly()              { return generationOnly; }
private:
  DmpSimuRunEventNtupleMaker*     dmpSimuRunEventNtupleMaker;
  DmpSimuPrimariesNtupleMaker*    dmpSimuPrimariesNtupleMaker;
  DmpSimuStkStepNtupleMaker*      dmpSimuStkStepNtupleMaker;
  DmpSimuTrajectoryNtupleMaker*   dmpSimuTrajectoryNtupleMaker;
  DmpSimuBgoHitNtupleMaker*       dmpSimuBgoHitNtupleMaker;
  DmpSimuStkHitNtupleMaker*       dmpSimuStkHitNtupleMaker;
  DmpSimuStkDigiNtupleMaker*      dmpSimuStkDigiNtupleMaker;
  DmpSimuPsdHitNtupleMaker*       dmpSimuPsdHitNtupleMaker;

  TFile*   rootFile;
  TTree*   tree;    
  TTree*   treeGen; // tree only for the genereted events
  DmpRootNtupleMessenger* rootMessenger; 
  G4bool   nRootGenDebug ; // true for Particle Generation Debug
  G4String nRootFile;
  G4double calEcut;
  G4int    siDigicut;
  G4bool generationOnly;
  G4bool keepOnlyDownward;
  G4int nInput;
  G4int nSaved;
};

#endif

