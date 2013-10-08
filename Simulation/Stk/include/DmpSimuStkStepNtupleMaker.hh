#ifndef DmpSimuStkStepNtupleMaker_h
#define DmpSimuStkStepNtupleMaker_h 1

#include <vector>
#include "globals.hh"
#include "G4Event.hh"
#include "G4Run.hh"

class TTree;

class DmpSimuStkStepNtupleMaker
{
public:
  
  DmpSimuStkStepNtupleMaker();
  ~DmpSimuStkStepNtupleMaker();
   
  void book(const G4Run* aRun, TTree* aTree);
  void save();

  void beginEvent(const G4Event* evt);
  void FillStep(const G4Step* aStep);
  void FillEvent(const G4Event* evt);        

 private:
  
  TTree*   tree;    

  G4int  debugEvent;

  G4int  eventNumber;

  G4bool is_pvtrack;
  G4bool is_eletrack;
  G4bool is_postrack;
  G4bool is_backtrack;
  G4int  pvtrackID;
  G4int  eletrackID;
  G4int  postrackID;
  G4int  currentTrackID;

  G4double eDepositAcc_pvtrack;
  G4double eDepositAcc_ele;
  G4double eDepositAcc_pos;
  G4double eDepositAcc_back;
  int tt_stepping_ntracks;
  std::vector<int>*       tt_stepping_trackID;
  std::vector<int>*       tt_stepping_trackPDG;
  std::vector<int>*       tt_stepping_parentID;
 
  int tt_pvtrack_nsteps;
  std::vector<double>*    tt_step_pvtrack_px;
  std::vector<double>*    tt_step_pvtrack_py;
  std::vector<double>*    tt_step_pvtrack_pz;
  std::vector<double>*    tt_step_pvtrack_ekin;
  std::vector<double>*    tt_step_pvtrack_x;
  std::vector<double>*    tt_step_pvtrack_y;
  std::vector<double>*    tt_step_pvtrack_z;
  std::vector<double>*    tt_step_pvtrack_stepLength;
  std::vector<double>*    tt_step_pvtrack_trackLength;
  std::vector<double>*    tt_step_pvtrack_energyDeposit;
  std::vector<int>*       tt_step_pvtrack_stepNumber;
  std::vector<G4bool>*    tt_step_pvtrack_isEntering;
  std::vector<int>*       tt_step_pvtrack_thisIndex;
  std::vector<int>*       tt_step_pvtrack_nextIndex;
  std::vector<std::string>*  tt_step_pvtrack_thisVolume;
  std::vector<std::string>*  tt_step_pvtrack_nextVolume;

  int tt_back_nsteps;
  std::vector<int>*       tt_step_back_pdg;
  std::vector<int>*       tt_step_back_trackID;
  std::vector<double>*    tt_step_back_px;
  std::vector<double>*    tt_step_back_py;
  std::vector<double>*    tt_step_back_pz;
  std::vector<double>*    tt_step_back_ekin;
  std::vector<double>*    tt_step_back_x;
  std::vector<double>*    tt_step_back_y;
  std::vector<double>*    tt_step_back_z;
  std::vector<int>*       tt_step_back_stepNumber;
  std::vector<G4bool>*    tt_step_back_isEntering;
  std::vector<int>*       tt_step_back_thisIndex;
  std::vector<int>*       tt_step_back_nextIndex;
  std::vector<std::string>*  tt_step_back_thisVolume;
  std::vector<std::string>*  tt_step_back_nextVolume;
  std::vector<double>*    tt_step_back_stepLength;
  std::vector<double>*    tt_step_back_trackLength;
  std::vector<double>*    tt_step_back_energyDeposit;

  int tt_ele_nsteps;
  std::vector<double>*    tt_step_ele_px;
  std::vector<double>*    tt_step_ele_py;
  std::vector<double>*    tt_step_ele_pz;
  std::vector<double>*    tt_step_ele_ekin;
  std::vector<double>*    tt_step_ele_x;
  std::vector<double>*    tt_step_ele_y;
  std::vector<double>*    tt_step_ele_z;
  std::vector<int>*       tt_step_ele_stepNumber;
  std::vector<G4bool>*    tt_step_ele_isEntering;
  std::vector<int>*       tt_step_ele_thisIndex;
  std::vector<int>*       tt_step_ele_nextIndex;
  std::vector<std::string>*  tt_step_ele_thisVolume;
  std::vector<std::string>*  tt_step_ele_nextVolume;
  std::vector<double>*    tt_step_ele_stepLength;
  std::vector<double>*    tt_step_ele_trackLength;
  std::vector<double>*    tt_step_ele_energyDeposit;

  int tt_pos_nsteps;
  std::vector<double>*    tt_step_pos_px;
  std::vector<double>*    tt_step_pos_py;
  std::vector<double>*    tt_step_pos_pz;
  std::vector<double>*    tt_step_pos_ekin;
  std::vector<double>*    tt_step_pos_x;
  std::vector<double>*    tt_step_pos_y;
  std::vector<double>*    tt_step_pos_z;
  std::vector<int>*       tt_step_pos_stepNumber;
  std::vector<G4bool>*    tt_step_pos_isEntering;
  std::vector<int>*       tt_step_pos_thisIndex;
  std::vector<int>*       tt_step_pos_nextIndex;
  std::vector<std::string>*  tt_step_pos_thisVolume;
  std::vector<std::string>*  tt_step_pos_nextVolume;
  std::vector<double>*    tt_step_pos_stepLength;
  std::vector<double>*    tt_step_pos_trackLength;
  std::vector<double>*    tt_step_pos_energyDeposit;

};


#endif

