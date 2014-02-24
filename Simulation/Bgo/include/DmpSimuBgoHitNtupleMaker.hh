#ifndef DmpSimuBgoHitNtupleMaker_h
#define DmpSimuBgoHitNtupleMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

class TTree;

class DmpSimuBgoHitNtupleMaker
{
public:
  
  DmpSimuBgoHitNtupleMaker();
  ~DmpSimuBgoHitNtupleMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

  G4bool passTotalEnergyCut(G4double cut);

 private:

  TTree*   tree;    
  G4int  debugEvent;
  G4int  eventNumber;

  G4double tt_cal_totE;
  G4double tt_cal_totE_1MeV;
  G4double tt_cal_totE_10MeV;

  int tt_CalLayer_nlayer;
  std::vector<double>*    tt_CalLayer_centroid;
  std::vector<double>*    tt_CalLayer_e;
  std::vector<double>*    tt_CalLayer_sumw2;
  std::vector<int>*       tt_CalLayer_index;

  int tt_CalLayer_nlayer_1MeV;
  std::vector<double>*    tt_CalLayer_centroid_1MeV;
  std::vector<double>*    tt_CalLayer_e_1MeV;
  std::vector<double>*    tt_CalLayer_sumw2_1MeV;
  std::vector<int>*       tt_CalLayer_index_1MeV;

  int tt_CalHit_n;
  std::vector<int>*    tt_CalHit_bar;
  std::vector<double>* tt_CalHit_e;
  std::vector<double>* tt_CalHit_epos;
  std::vector<double>* tt_CalHit_eneg;
  std::vector<double>* tt_CalHit_sumposition;

  std::vector<int>*    tt_CalMaxBar_layer;
  std::vector<int>*    tt_CalMaxBarPos_layer;
  std::vector<int>*    tt_CalMaxBarNeg_layer;
  std::vector<int>*    tt_CalMaxBar_ind;
  std::vector<int>*    tt_CalMaxBarPos_ind;
  std::vector<int>*    tt_CalMaxBarNeg_ind;
  std::vector<double>* tt_CalMaxBar_e;
  std::vector<double>* tt_CalMaxBarPos_e;
  std::vector<double>* tt_CalMaxBarNeg_e;

};


#endif

