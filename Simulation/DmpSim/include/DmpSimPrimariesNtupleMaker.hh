#ifndef DmpSimPrimariesNtupleMaker_h
#define DmpSimPrimariesNtupleMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

class TTree;

class DmpSimPrimariesNtupleMaker
{
public:
  
  DmpSimPrimariesNtupleMaker();
  ~DmpSimPrimariesNtupleMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

 private:
  
  TTree*   tree;    
  G4int  debugEvent;
  G4int  eventNumber;

  int tt_npv;

  G4double tt_pv_x, tt_pv_y, tt_pv_z;
  int tt_npvpart;
  G4double tt_pvpart_px, tt_pvpart_py, tt_pvpart_pz, tt_pvpart_ekin, tt_pvpart_q;
  int tt_pvpart_pdg;


};


#endif

