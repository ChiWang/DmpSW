#ifndef DmpSimuStkHitNtupleMaker_h
#define DmpSimuStkHitNtupleMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

class TTree;

class DmpSimuStkHitNtupleMaker
{
public:
  
  DmpSimuStkHitNtupleMaker();
  ~DmpSimuStkHitNtupleMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

 private:
  
  TTree*   tree;    
  G4int  debugEvent;
  G4int  eventNumber;

  int tt_SiHit_n;
  std::vector<int>*    tt_SiHit_strip;
  std::vector<int>*    tt_SiHit_id;
  std::vector<unsigned int>*    tt_SiHit_trackID;
  std::vector<unsigned int>*    tt_SiHit_trackID1;
  std::vector<unsigned int>*    tt_SiHit_trackID2;
  std::vector<int>*    tt_SiHit_ntracks;
  std::vector<int>*    tt_SiHit_ntracksBack;
  std::vector<int>*    tt_SiHit_ntracksPrim;
  std::vector<double>* tt_SiHit_e;
  std::vector<double>* tt_SiHit_e_prim;
  std::vector<double>* tt_SiHit_x;
  std::vector<double>* tt_SiHit_y;
  std::vector<double>* tt_SiHit_z;


};


#endif

