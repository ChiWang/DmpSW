#ifndef DmpSimuPrimariesNtupleMaker_h
#define DmpSimuPrimariesNtupleMaker_h 1

#include "globals.hh"


class G4Event;
class G4Run;
class TTree;

class DmpSimuPrimariesNtupleMaker
{
public:
  DmpSimuPrimariesNtupleMaker();
  ~DmpSimuPrimariesNtupleMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void beginEvent(const G4Event* evt);
  void FillEvent(const G4Event* evt);        

 private:
  TTree* tree;    
  //G4int  debugEvent;
  G4int  eventNumber;

  int tt_npv;       // n primary vertex
  G4double tt_pv_x, tt_pv_y, tt_pv_z, tt_pv_r, tt_pv_theta, tt_pv_phi ;
  int tt_npvpart;
  G4double tt_pvpart_px, tt_pvpart_py, tt_pvpart_pz, tt_pvpart_cosx, tt_pvpart_cosy, tt_pvpart_cosz;
  G4double tt_pvpart_ekin, tt_pvpart_q, tt_pvpart_zenith, tt_pvpart_azimuth;
  int tt_pvpart_pdg;
};

#endif

