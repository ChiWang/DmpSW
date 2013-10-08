#ifndef DmpSimuStkDigiNtupleMaker_h
#define DmpSimuStkDigiNtupleMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

class TTree;

class DmpSimuStkDigiNtupleMaker
{
public:
  
  DmpSimuStkDigiNtupleMaker();
  ~DmpSimuStkDigiNtupleMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

 private:
  
  TTree*   tree;    
  G4int    debugEvent;
  G4int    eventNumber;

  int tt_SiDigit_n;
  std::vector<int>*    tt_SiDigit_strip;
  std::vector<unsigned int>*    tt_SiDigit_trackID;
  std::vector<double>* tt_SiDigit_e;
  std::vector<double>* tt_SiDigit_e_prim;
  std::vector<int>*    tt_SiDigit_ntracks;
  std::vector<int>*    tt_SiDigit_ntracksBack;
  std::vector<int>*    tt_SiDigit_ntracksPrim;
  std::vector<int>*    tt_SiDigit_nhits;
  std::vector<int>*    tt_SiDigit_nhitsBack;
  std::vector<int>*    tt_SiDigit_hitID;
  std::vector<int>*    tt_SiDigit_hitID1;
  std::vector<int>*    tt_SiDigit_hitID2;

};


#endif

