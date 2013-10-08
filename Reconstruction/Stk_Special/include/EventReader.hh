#ifndef EventReader_h
#define EventReader_h

#include <vector>
#include <string>

#include <TLorentzVector.h>
#include <TTree.h>
#include <TChain.h>
#include <TBranch.h>

class EventReader {

 public:
  enum BlockType { BlockCAL = 0,
		   BlockPVPART, 
		   BlockPVTRJ, 
		   BlockELE, 
		   BlockPOS,
		   STEP_PVTRACK,
		   STEP_BACK,
		   STEP_ELE,
		   STEP_POS,
		   SIHIT,
		   SIDIGIT}; 

  EventReader(TChain * chain);
  virtual ~EventReader() {};

  void setBranchAddresses(BlockType type); //sets branch addresses

 protected:
  TChain * fChain;

   // Declaration of leaf types
   UInt_t          tt_run;
   UInt_t          tt_event;
   UInt_t          tt_npv;
   Double_t        tt_cal_totE;
   Double_t        tt_cal_totE_1MeV;
   Double_t        tt_cal_totE_10MeV;
   Double_t        tt_pv_x;
   Double_t        tt_pv_y;
   Double_t        tt_pv_z;
   Double_t        tt_pvpart_px;
   Double_t        tt_pvpart_py;
   Double_t        tt_pvpart_pz;
   Double_t        tt_pvpart_ekin;
   Double_t        tt_pvpart_q;
   Int_t           tt_pvpart_pdg;
   Int_t           tt_pvtrj_trackID;
   std::string          *tt_pvtrj_stop_vo;
   Int_t           tt_pvtrj_stop_index;
   Double_t        tt_pvtrj_stop_x;
   Double_t        tt_pvtrj_stop_y;
   Double_t        tt_pvtrj_stop_z;
   Double_t        tt_ele_px;
   Double_t        tt_ele_py;
   Double_t        tt_ele_pz;
   Double_t        tt_ele_ekin;
   Int_t           tt_ele_trackID;
   Int_t           tt_ele_parentID;
   std::string          *tt_ele_stop_vo;
   Int_t           tt_ele_stop_index;
   Double_t        tt_ele_stop_x;
   Double_t        tt_ele_stop_y;
   Double_t        tt_ele_stop_z;
   Double_t        tt_pos_px;
   Double_t        tt_pos_py;
   Double_t        tt_pos_pz;
   Double_t        tt_pos_ekin;
   Int_t           tt_pos_trackID;
   Int_t           tt_pos_parentID;
   std::string          *tt_pos_stop_vo;
   Int_t           tt_pos_stop_index;
   Double_t        tt_pos_stop_x;
   Double_t        tt_pos_stop_y;
   Double_t        tt_pos_stop_z;
   UInt_t          tt_pvtrack_nsteps;
   std::vector<double>  *tt_step_pvtrack_px;
   std::vector<double>  *tt_step_pvtrack_py;
   std::vector<double>  *tt_step_pvtrack_pz;
   std::vector<double>  *tt_step_pvtrack_ekin;
   std::vector<double>  *tt_step_pvtrack_x;
   std::vector<double>  *tt_step_pvtrack_y;
   std::vector<double>  *tt_step_pvtrack_z;
   std::vector<double>  *tt_step_pvtrack_stepLength;
   std::vector<double>  *tt_step_pvtrack_trackLength;
   std::vector<double>  *tt_step_pvtrack_energyDeposit;
   std::vector<int>     *tt_step_pvtrack_stepNumber;
   std::vector<bool>    *tt_step_pvtrack_isEntering;
   std::vector<std::string>  *tt_step_pvtrack_thisVolume;
   std::vector<std::string>  *tt_step_pvtrack_nextVolume;
   std::vector<int>     *tt_step_pvtrack_thisIndex;
   std::vector<int>     *tt_step_pvtrack_nextIndex;
   UInt_t          tt_back_nsteps;
   std::vector<int>     *tt_step_back_trackID;
   std::vector<int>     *tt_step_back_pdg;
   std::vector<double>  *tt_step_back_px;
   std::vector<double>  *tt_step_back_py;
   std::vector<double>  *tt_step_back_pz;
   std::vector<double>  *tt_step_back_ekin;
   std::vector<double>  *tt_step_back_x;
   std::vector<double>  *tt_step_back_y;
   std::vector<double>  *tt_step_back_z;
   std::vector<double>  *tt_step_back_stepLength;
   std::vector<double>  *tt_step_back_trackLength;
   std::vector<double>  *tt_step_back_energyDeposit;
   std::vector<int>     *tt_step_back_stepNumber;
   std::vector<bool>    *tt_step_back_isEntering;
   std::vector<std::string>  *tt_step_back_thisVolume;
   std::vector<std::string>  *tt_step_back_nextVolume;
   std::vector<int>     *tt_step_back_thisIndex;
   std::vector<int>     *tt_step_back_nextIndex;
   UInt_t          tt_ele_nsteps;
   std::vector<double>  *tt_step_ele_px;
   std::vector<double>  *tt_step_ele_py;
   std::vector<double>  *tt_step_ele_pz;
   std::vector<double>  *tt_step_ele_ekin;
   std::vector<double>  *tt_step_ele_x;
   std::vector<double>  *tt_step_ele_y;
   std::vector<double>  *tt_step_ele_z;
   std::vector<double>  *tt_step_ele_energyDeposit;
   std::vector<int>     *tt_step_ele_stepNumber;
   std::vector<bool>    *tt_step_ele_isEntering;
   std::vector<std::string>  *tt_step_ele_thisVolume;
   std::vector<std::string>  *tt_step_ele_nextVolume;
   std::vector<int>     *tt_step_ele_thisIndex;
   std::vector<int>     *tt_step_ele_nextIndex;
   UInt_t          tt_pos_nsteps;
   std::vector<double>  *tt_step_pos_px;
   std::vector<double>  *tt_step_pos_py;
   std::vector<double>  *tt_step_pos_pz;
   std::vector<double>  *tt_step_pos_ekin;
   std::vector<double>  *tt_step_pos_x;
   std::vector<double>  *tt_step_pos_y;
   std::vector<double>  *tt_step_pos_z;
   std::vector<double>  *tt_step_pos_stepLength;
   std::vector<double>  *tt_step_pos_trackLength;
   std::vector<double>  *tt_step_pos_energyDeposit;
   std::vector<int>     *tt_step_pos_stepNumber;
   std::vector<bool>    *tt_step_pos_isEntering;
   std::vector<std::string>  *tt_step_pos_thisVolume;
   std::vector<std::string>  *tt_step_pos_nextVolume;
   std::vector<int>     *tt_step_pos_thisIndex;
   std::vector<int>     *tt_step_pos_nextIndex;
   UInt_t          tt_CalLayer_nlayer;
   std::vector<double>  *tt_CalLayer_centroid;
   std::vector<double>  *tt_CalLayer_e;
   std::vector<double>  *tt_CalLayer_sumw2;
   std::vector<int>     *tt_CalLayer_index;
   UInt_t          tt_CalLayer_nlayer_1MeV;
   std::vector<double>  *tt_CalLayer_centroid_1MeV;
   std::vector<double>  *tt_CalLayer_e_1MeV;
   std::vector<double>  *tt_CalLayer_sumw2_1MeV;
   std::vector<int>     *tt_CalLayer_index_1MeV;
   UInt_t          tt_CalHit_n;
   std::vector<int>     *tt_CalHit_bar;
   std::vector<double>  *tt_CalHit_e;
   UInt_t          tt_SiHit_n;
   std::vector<int>     *tt_SiHit_strip;
   std::vector<int>     *tt_SiHit_id;
   std::vector<unsigned int> *tt_SiHit_trackID;
   std::vector<unsigned int> *tt_SiHit_trackID1;
   std::vector<unsigned int> *tt_SiHit_trackID2;
   std::vector<int>     *tt_SiHit_ntracks;
   std::vector<int>     *tt_SiHit_ntracksBack;
   std::vector<int>     *tt_SiHit_ntracksPrim;
   std::vector<double>  *tt_SiHit_e;
   std::vector<double>  *tt_SiHit_e_prim;
   std::vector<double>  *tt_SiHit_x;
   std::vector<double>  *tt_SiHit_y;
   std::vector<double>  *tt_SiHit_z;
   UInt_t          tt_SiDigit_n;
   std::vector<int>     *tt_SiDigit_strip;
   std::vector<unsigned int> *tt_SiDigit_trackID;
   std::vector<double>  *tt_SiDigit_e;
   std::vector<double>  *tt_SiDigit_e_prim;
   std::vector<int>     *tt_SiDigit_ntracks;
   std::vector<int>     *tt_SiDigit_ntracksBack;
   std::vector<int>     *tt_SiDigit_ntracksPrim;
   std::vector<int>     *tt_SiDigit_nhits;
   std::vector<int>     *tt_SiDigit_nhitsBack;
   std::vector<int>     *tt_SiDigit_hitID;
   std::vector<int>     *tt_SiDigit_hitID1;
   std::vector<int>     *tt_SiDigit_hitID2;

   // List of branches
   TBranch        *b_tt_run;   //!
   TBranch        *b_tt_event;   //!
   TBranch        *b_tt_npv;   //!
   TBranch        *b_tt_cal_totE;   //!
   TBranch        *b_tt_cal_totE_1MeV;   //!
   TBranch        *b_tt_cal_totE_10MeV;   //!
   TBranch        *b_tt_pv_x;   //!
   TBranch        *b_tt_pv_y;   //!
   TBranch        *b_tt_pv_z;   //!
   TBranch        *b_tt_pvpart_px;   //!
   TBranch        *b_tt_pvpart_py;   //!
   TBranch        *b_tt_pvpart_pz;   //!
   TBranch        *b_tt_pvpart_ekin;   //!
   TBranch        *b_tt_pvpart_q;   //!
   TBranch        *b_tt_pvpart_pdg;   //!
   TBranch        *b_tt_pvtrj_trackID;   //!
   TBranch        *b_tt_pvtrj_stop_vo;   //!
   TBranch        *b_tt_pvtrj_stop_index;   //!
   TBranch        *b_tt_pvtrj_stop_x;   //!
   TBranch        *b_tt_pvtrj_stop_y;   //!
   TBranch        *b_tt_pvtrj_stop_z;   //!
   TBranch        *b_tt_ele_px;   //!
   TBranch        *b_tt_ele_py;   //!
   TBranch        *b_tt_ele_pz;   //!
   TBranch        *b_tt_ele_ekin;   //!
   TBranch        *b_tt_ele_trackID;   //!
   TBranch        *b_tt_ele_parentID;   //!
   TBranch        *b_tt_ele_stop_vo;   //!
   TBranch        *b_tt_ele_stop_index;   //!
   TBranch        *b_tt_ele_stop_x;   //!
   TBranch        *b_tt_ele_stop_y;   //!
   TBranch        *b_tt_ele_stop_z;   //!
   TBranch        *b_tt_pos_px;   //!
   TBranch        *b_tt_pos_py;   //!
   TBranch        *b_tt_pos_pz;   //!
   TBranch        *b_tt_pos_ekin;   //!
   TBranch        *b_tt_pos_trackID;   //!
   TBranch        *b_tt_pos_parentID;   //!
   TBranch        *b_tt_pos_stop_vo;   //!
   TBranch        *b_tt_pos_stop_index;   //!
   TBranch        *b_tt_pos_stop_x;   //!
   TBranch        *b_tt_pos_stop_y;   //!
   TBranch        *b_tt_pos_stop_z;   //!
   TBranch        *b_tt_pvtrack_nsteps;   //!
   TBranch        *b_tt_step_pvtrack_px;   //!
   TBranch        *b_tt_step_pvtrack_py;   //!
   TBranch        *b_tt_step_pvtrack_pz;   //!
   TBranch        *b_tt_step_pvtrack_ekin;   //!
   TBranch        *b_tt_step_pvtrack_x;   //!
   TBranch        *b_tt_step_pvtrack_y;   //!
   TBranch        *b_tt_step_pvtrack_z;   //!
   TBranch        *b_tt_step_pvtrack_stepLength;   //!
   TBranch        *b_tt_step_pvtrack_trackLength;   //!
   TBranch        *b_tt_step_pvtrack_energyDeposit;   //!
   TBranch        *b_tt_step_pvtrack_stepNumber;   //!
   TBranch        *b_tt_step_pvtrack_isEntering;   //!
   TBranch        *b_tt_step_pvtrack_thisVolume;   //!
   TBranch        *b_tt_step_pvtrack_nextVolume;   //!
   TBranch        *b_tt_step_pvtrack_thisIndex;   //!
   TBranch        *b_tt_step_pvtrack_nextIndex;   //!
   TBranch        *b_tt_back_nsteps;   //!
   TBranch        *b_tt_step_back_trackID;   //!
   TBranch        *b_tt_step_back_pdg;   //!
   TBranch        *b_tt_step_back_px;   //!
   TBranch        *b_tt_step_back_py;   //!
   TBranch        *b_tt_step_back_pz;   //!
   TBranch        *b_tt_step_back_ekin;   //!
   TBranch        *b_tt_step_back_x;   //!
   TBranch        *b_tt_step_back_y;   //!
   TBranch        *b_tt_step_back_z;   //!
   TBranch        *b_tt_step_back_stepLength;   //!
   TBranch        *b_tt_step_back_trackLength;   //!
   TBranch        *b_tt_step_back_energyDeposit;   //!
   TBranch        *b_tt_step_back_stepNumber;   //!
   TBranch        *b_tt_step_back_isEntering;   //!
   TBranch        *b_tt_step_back_thisVolume;   //!
   TBranch        *b_tt_step_back_nextVolume;   //!
   TBranch        *b_tt_step_back_thisIndex;   //!
   TBranch        *b_tt_step_back_nextIndex;   //!
   TBranch        *b_tt_ele_nsteps;   //!
   TBranch        *b_tt_step_ele_px;   //!
   TBranch        *b_tt_step_ele_py;   //!
   TBranch        *b_tt_step_ele_pz;   //!
   TBranch        *b_tt_step_ele_ekin;   //!
   TBranch        *b_tt_step_ele_x;   //!
   TBranch        *b_tt_step_ele_y;   //!
   TBranch        *b_tt_step_ele_z;   //!
   TBranch        *b_tt_step_ele_energyDeposit;   //!
   TBranch        *b_tt_step_ele_stepNumber;   //!
   TBranch        *b_tt_step_ele_isEntering;   //!
   TBranch        *b_tt_step_ele_thisVolume;   //!
   TBranch        *b_tt_step_ele_nextVolume;   //!
   TBranch        *b_tt_step_ele_thisIndex;   //!
   TBranch        *b_tt_step_ele_nextIndex;   //!
   TBranch        *b_tt_pos_nsteps;   //!
   TBranch        *b_tt_step_pos_px;   //!
   TBranch        *b_tt_step_pos_py;   //!
   TBranch        *b_tt_step_pos_pz;   //!
   TBranch        *b_tt_step_pos_ekin;   //!
   TBranch        *b_tt_step_pos_x;   //!
   TBranch        *b_tt_step_pos_y;   //!
   TBranch        *b_tt_step_pos_z;   //!
   TBranch        *b_tt_step_pos_stepLength;   //!
   TBranch        *b_tt_step_pos_trackLength;   //!
   TBranch        *b_tt_step_pos_energyDeposit;   //!
   TBranch        *b_tt_step_pos_stepNumber;   //!
   TBranch        *b_tt_step_pos_isEntering;   //!
   TBranch        *b_tt_step_pos_thisVolume;   //!
   TBranch        *b_tt_step_pos_nextVolume;   //!
   TBranch        *b_tt_step_pos_thisIndex;   //!
   TBranch        *b_tt_step_pos_nextIndex;   //!
   TBranch        *b_tt_CalLayer_nlayer;   //!
   TBranch        *b_tt_CalLayer_centroid;   //!
   TBranch        *b_tt_CalLayer_e;   //!
   TBranch        *b_tt_CalLayer_sumw2;   //!
   TBranch        *b_tt_CalLayer_index;   //!
   TBranch        *b_tt_CalLayer_nlayer_1MeV;   //!
   TBranch        *b_tt_CalLayer_centroid_1MeV;   //!
   TBranch        *b_tt_CalLayer_e_1MeV;   //!
   TBranch        *b_tt_CalLayer_sumw2_1MeV;   //!
   TBranch        *b_tt_CalLayer_index_1MeV;   //!
   TBranch        *b_tt_CalHit_n;   //!
   TBranch        *b_tt_CalHit_bar;   //!
   TBranch        *b_tt_CalHit_e;   //!
   TBranch        *b_tt_SiHit_n;   //!
   TBranch        *b_tt_SiHit_strip;   //!
   TBranch        *b_tt_SiHit_id;   //!
   TBranch        *b_tt_SiHit_trackID;   //!
   TBranch        *b_tt_SiHit_trackID1;   //!
   TBranch        *b_tt_SiHit_trackID2;   //!
   TBranch        *b_tt_SiHit_ntracks;   //!
   TBranch        *b_tt_SiHit_ntracksBack;   //!
   TBranch        *b_tt_SiHit_ntracksPrim;   //!
   TBranch        *b_tt_SiHit_e;   //!
   TBranch        *b_tt_SiHit_e_prim;   //!
   TBranch        *b_tt_SiHit_x;   //!
   TBranch        *b_tt_SiHit_y;   //!
   TBranch        *b_tt_SiHit_z;   //!
   TBranch        *b_tt_SiDigit_n;   //!
   TBranch        *b_tt_SiDigit_strip;   //!
   TBranch        *b_tt_SiDigit_trackID;   //!
   TBranch        *b_tt_SiDigit_e;   //!
   TBranch        *b_tt_SiDigit_e_prim;   //!
   TBranch        *b_tt_SiDigit_ntracks;   //!
   TBranch        *b_tt_SiDigit_ntracksBack;   //!
   TBranch        *b_tt_SiDigit_ntracksPrim;   //!
   TBranch        *b_tt_SiDigit_nhits;   //!
   TBranch        *b_tt_SiDigit_nhitsBack;   //!
   TBranch        *b_tt_SiDigit_hitID;   //!
   TBranch        *b_tt_SiDigit_hitID1;   //!
   TBranch        *b_tt_SiDigit_hitID2;   //!

};

#endif
