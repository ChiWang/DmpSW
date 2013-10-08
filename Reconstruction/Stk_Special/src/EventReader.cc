#define EventReader_cxx
// Description: This class is used to read input data from a ROOT L2 data ntuple
//
// Author(s):
//  - creation by X.Wu, 07/09/2013
//
// The class definition in EventReader.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//


#include "EventReader.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>

void EventReader::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void EventReader::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t EventReader::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either EventReader::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.


   return kTRUE;
}

void EventReader::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void EventReader::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}

void EventReader::readEventInfo()
{
  m_eventInfoSet = true;
  b_tt_run  ->GetEntry(m_entry);
  b_tt_event->GetEntry(m_entry);

  m_run       = tt_run;
  m_event     = tt_event;

  return;
}

void EventReader::readPrimaries()
{
  b_tt_npv ->GetEntry(m_entry);
  b_tt_pv_x->GetEntry(m_entry);
  b_tt_pv_y->GetEntry(m_entry);
  b_tt_pv_z->GetEntry(m_entry);

  b_tt_pvpart_px  ->GetEntry(m_entry);
  b_tt_pvpart_py  ->GetEntry(m_entry);
  b_tt_pvpart_pz  ->GetEntry(m_entry);
  b_tt_pvpart_ekin->GetEntry(m_entry);
  b_tt_pvpart_q   ->GetEntry(m_entry);
  b_tt_pvpart_pdg ->GetEntry(m_entry);

  m_npv           = tt_npv ;
  m_pv_x          = tt_pv_x;
  m_pv_y          = tt_pv_y;
  m_pv_z          = tt_pv_z;
  m_pvpart_px     = tt_pvpart_px  ;
  m_pvpart_py     = tt_pvpart_py  ;
  m_pvpart_pz     = tt_pvpart_pz  ;
  m_pvpart_ekin   = tt_pvpart_ekin;
  m_pvpart_q      = tt_pvpart_q   ;
  m_pvpart_pdg    = tt_pvpart_pdg ;

  return;
}

void EventReader::readStepPvtrack()
{
  b_tt_pvtrack_nsteps            ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_px           ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_py           ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_pz           ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_ekin         ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_x            ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_y            ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_z            ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_stepLength   ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_trackLength  ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_energyDeposit->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_stepNumber   ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_isEntering   ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_thisVolume   ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_nextVolume   ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_thisIndex    ->GetEntry(m_entry);   //!
  b_tt_step_pvtrack_nextIndex    ->GetEntry(m_entry);   //!

  m_pvtrack_nsteps = tt_pvtrack_nsteps;

  return;
}

void EventReader::readStepBack()
{

  b_tt_back_nsteps            ->GetEntry(m_entry);   //!
  b_tt_step_back_trackID      ->GetEntry(m_entry);   //!
  b_tt_step_back_pdg          ->GetEntry(m_entry);   //!
  b_tt_step_back_px           ->GetEntry(m_entry);   //!
  b_tt_step_back_py           ->GetEntry(m_entry);   //!
  b_tt_step_back_pz           ->GetEntry(m_entry);   //!
  b_tt_step_back_ekin         ->GetEntry(m_entry);   //!
  b_tt_step_back_x            ->GetEntry(m_entry);   //!
  b_tt_step_back_y            ->GetEntry(m_entry);   //!
  b_tt_step_back_z            ->GetEntry(m_entry);   //!
  b_tt_step_back_stepLength   ->GetEntry(m_entry);   //!
  b_tt_step_back_trackLength  ->GetEntry(m_entry);   //!
  b_tt_step_back_energyDeposit->GetEntry(m_entry);   //!
  b_tt_step_back_stepNumber   ->GetEntry(m_entry);   //!
  b_tt_step_back_isEntering   ->GetEntry(m_entry);   //!
  b_tt_step_back_thisVolume   ->GetEntry(m_entry);   //!
  b_tt_step_back_nextVolume   ->GetEntry(m_entry);   //!
  b_tt_step_back_thisIndex    ->GetEntry(m_entry);   //!
  b_tt_step_back_nextIndex    ->GetEntry(m_entry);   //!

  m_back_nsteps = tt_back_nsteps;

  return;
}

void EventReader::readStepEle()
{
  b_tt_ele_nsteps            ->GetEntry(m_entry);   //!
  b_tt_step_ele_px           ->GetEntry(m_entry);   //!
  b_tt_step_ele_py           ->GetEntry(m_entry);   //!
  b_tt_step_ele_pz           ->GetEntry(m_entry);   //!
  b_tt_step_ele_ekin         ->GetEntry(m_entry);   //!
  b_tt_step_ele_x            ->GetEntry(m_entry);   //!
  b_tt_step_ele_y            ->GetEntry(m_entry);   //!
  b_tt_step_ele_z            ->GetEntry(m_entry);   //!
  b_tt_step_ele_energyDeposit->GetEntry(m_entry);   //!
  b_tt_step_ele_stepNumber   ->GetEntry(m_entry);   //!
  b_tt_step_ele_isEntering   ->GetEntry(m_entry);   //!
  b_tt_step_ele_thisVolume   ->GetEntry(m_entry);   //!
  b_tt_step_ele_nextVolume   ->GetEntry(m_entry);   //!
  b_tt_step_ele_thisIndex    ->GetEntry(m_entry);   //!
  b_tt_step_ele_nextIndex    ->GetEntry(m_entry);   //!

  m_ele_nsteps = tt_ele_nsteps;

  return;
}

void EventReader::readStepPos()
{
  b_tt_pos_nsteps            ->GetEntry(m_entry);   //!
  b_tt_step_pos_px           ->GetEntry(m_entry);   //!
  b_tt_step_pos_py           ->GetEntry(m_entry);   //!
  b_tt_step_pos_pz           ->GetEntry(m_entry);   //!
  b_tt_step_pos_ekin         ->GetEntry(m_entry);   //!
  b_tt_step_pos_x            ->GetEntry(m_entry);   //!
  b_tt_step_pos_y            ->GetEntry(m_entry);   //!
  b_tt_step_pos_z            ->GetEntry(m_entry);   //!
  b_tt_step_pos_energyDeposit->GetEntry(m_entry);   //!
  b_tt_step_pos_stepNumber   ->GetEntry(m_entry);   //!
  b_tt_step_pos_isEntering   ->GetEntry(m_entry);   //!
  b_tt_step_pos_thisVolume   ->GetEntry(m_entry);   //!
  b_tt_step_pos_nextVolume   ->GetEntry(m_entry);   //!
  b_tt_step_pos_thisIndex    ->GetEntry(m_entry);   //!
  b_tt_step_pos_nextIndex    ->GetEntry(m_entry);   //!

  m_pos_nsteps = tt_pos_nsteps;

  return;
}

void EventReader::readPvtrj()
{
  b_tt_pvtrj_trackID         ->GetEntry(m_entry);   //!
  b_tt_pvtrj_stop_vo         ->GetEntry(m_entry);   //!
  b_tt_pvtrj_stop_index      ->GetEntry(m_entry);   //!
  b_tt_pvtrj_stop_x          ->GetEntry(m_entry);   //!
  b_tt_pvtrj_stop_y          ->GetEntry(m_entry);   //!
  b_tt_pvtrj_stop_z          ->GetEntry(m_entry);   //!

  m_pvtrj_trackID           = tt_pvtrj_trackID;         
  m_pvtrj_stop_vo           = tt_pvtrj_stop_vo;        
  m_pvtrj_stop_index        = tt_pvtrj_stop_index;      
  m_pvtrj_stop_x            = tt_pvtrj_stop_x;          
  m_pvtrj_stop_y            = tt_pvtrj_stop_y;          
  m_pvtrj_stop_z            = tt_pvtrj_stop_z;          

  return;
}

void EventReader::readEle()
{
  b_tt_ele_px         ->GetEntry(m_entry);   //!
  b_tt_ele_py         ->GetEntry(m_entry);   //!
  b_tt_ele_pz         ->GetEntry(m_entry);   //!
  b_tt_ele_ekin       ->GetEntry(m_entry);   //!
  b_tt_ele_trackID    ->GetEntry(m_entry);   //!
  b_tt_ele_parentID   ->GetEntry(m_entry);   //!
  b_tt_ele_stop_vo    ->GetEntry(m_entry);   //!
  b_tt_ele_stop_index ->GetEntry(m_entry);   //!
  b_tt_ele_stop_x     ->GetEntry(m_entry);   //!
  b_tt_ele_stop_y     ->GetEntry(m_entry);   //!
  b_tt_ele_stop_z     ->GetEntry(m_entry);   //!

  m_ele_px         = tt_ele_px;         
  m_ele_py         = tt_ele_py;         
  m_ele_pz         = tt_ele_pz;         
  m_ele_ekin       = tt_ele_ekin;       
  m_ele_trackID    = tt_ele_trackID;    
  m_ele_parentID   = tt_ele_parentID;   
  m_ele_stop_vo    = tt_ele_stop_vo;    
  m_ele_stop_index = tt_ele_stop_index; 
  m_ele_stop_x     = tt_ele_stop_x;     
  m_ele_stop_y     = tt_ele_stop_y;     
  m_ele_stop_z     = tt_ele_stop_z;     

  return;
}

void EventReader::readPos()
{
  b_tt_pos_px         ->GetEntry(m_entry);   //!
  b_tt_pos_py         ->GetEntry(m_entry);   //!
  b_tt_pos_pz         ->GetEntry(m_entry);   //!
  b_tt_pos_ekin       ->GetEntry(m_entry);   //!
  b_tt_pos_trackID    ->GetEntry(m_entry);   //!
  b_tt_pos_parentID   ->GetEntry(m_entry);   //!
  b_tt_pos_stop_vo    ->GetEntry(m_entry);   //!
  b_tt_pos_stop_index ->GetEntry(m_entry);   //!
  b_tt_pos_stop_x     ->GetEntry(m_entry);   //!
  b_tt_pos_stop_y     ->GetEntry(m_entry);   //!
  b_tt_pos_stop_z     ->GetEntry(m_entry);   //!

  m_pos_px         = tt_pos_px;         
  m_pos_py         = tt_pos_py;         
  m_pos_pz         = tt_pos_pz;         
  m_pos_ekin       = tt_pos_ekin;       
  m_pos_trackID    = tt_pos_trackID;    
  m_pos_parentID   = tt_pos_parentID;   
  m_pos_stop_vo    = tt_pos_stop_vo;    
  m_pos_stop_index = tt_pos_stop_index; 
  m_pos_stop_x     = tt_pos_stop_x;     
  m_pos_stop_y     = tt_pos_stop_y;     
  m_pos_stop_z     = tt_pos_stop_z;     

  return;
}

void EventReader::readCal()
{
  b_tt_cal_totE                ->GetEntry(m_entry);   //!
  b_tt_cal_totE_1MeV           ->GetEntry(m_entry);   //!
  b_tt_cal_totE_10MeV          ->GetEntry(m_entry);   //!
  b_tt_CalLayer_nlayer         ->GetEntry(m_entry);   //!
  b_tt_CalLayer_centroid       ->GetEntry(m_entry);   //!
  b_tt_CalLayer_e              ->GetEntry(m_entry);   //!
  b_tt_CalLayer_sumw2          ->GetEntry(m_entry);   //!
  b_tt_CalLayer_index          ->GetEntry(m_entry);   //!
  b_tt_CalLayer_nlayer_1MeV    ->GetEntry(m_entry);   //!
  b_tt_CalLayer_centroid_1MeV  ->GetEntry(m_entry);   //!
  b_tt_CalLayer_e_1MeV         ->GetEntry(m_entry);   //!
  b_tt_CalLayer_sumw2_1MeV     ->GetEntry(m_entry);   //!
  b_tt_CalLayer_index_1MeV     ->GetEntry(m_entry);   //!
  b_tt_CalHit_n                ->GetEntry(m_entry);   //!
  b_tt_CalHit_bar              ->GetEntry(m_entry);   //!
  b_tt_CalHit_e                ->GetEntry(m_entry);   //!

  m_cal_totE	         = tt_cal_totE;	     
  m_cal_totE_1MeV        = tt_cal_totE_1MeV;  
  m_cal_totE_10MeV       = tt_cal_totE_10MeV; 
  m_CalLayer_nlayer      = tt_CalLayer_nlayer;
  m_CalLayer_nlayer_1MeV = tt_CalLayer_nlayer_1MeV;
  m_CalHit_n             = tt_CalHit_n;

  return;
}

void EventReader::readSiHit()
{
  b_tt_SiHit_n            ->GetEntry(m_entry);   //!
  b_tt_SiHit_strip        ->GetEntry(m_entry);   //!
  b_tt_SiHit_id           ->GetEntry(m_entry);   //!
  b_tt_SiHit_trackID      ->GetEntry(m_entry);   //!
  b_tt_SiHit_trackID1     ->GetEntry(m_entry);   //!
  b_tt_SiHit_trackID2     ->GetEntry(m_entry);   //!
  b_tt_SiHit_ntracks      ->GetEntry(m_entry);   //!
  b_tt_SiHit_ntracksBack  ->GetEntry(m_entry);   //!
  b_tt_SiHit_ntracksPrim  ->GetEntry(m_entry);   //!
  b_tt_SiHit_e            ->GetEntry(m_entry);   //!
  b_tt_SiHit_e_prim       ->GetEntry(m_entry);   //!
  b_tt_SiHit_x            ->GetEntry(m_entry);   //!
  b_tt_SiHit_y            ->GetEntry(m_entry);   //!
  b_tt_SiHit_z            ->GetEntry(m_entry);   //!

  m_SiHit_n = tt_SiHit_n;

  return;
}

void EventReader::readSiDigit()
{
  b_tt_SiDigit_n            ->GetEntry(m_entry);   //!
  b_tt_SiDigit_strip        ->GetEntry(m_entry);   //!
  b_tt_SiDigit_trackID      ->GetEntry(m_entry);   //!
  b_tt_SiDigit_e            ->GetEntry(m_entry);   //!
  b_tt_SiDigit_e_prim       ->GetEntry(m_entry);   //!
  b_tt_SiDigit_ntracks      ->GetEntry(m_entry);   //!
  b_tt_SiDigit_ntracksBack  ->GetEntry(m_entry);   //!
  b_tt_SiDigit_ntracksPrim  ->GetEntry(m_entry);   //!
  b_tt_SiDigit_nhits        ->GetEntry(m_entry);   //!
  b_tt_SiDigit_nhitsBack    ->GetEntry(m_entry);   //!
  b_tt_SiDigit_hitID        ->GetEntry(m_entry);   //!
  b_tt_SiDigit_hitID1       ->GetEntry(m_entry);   //!
  b_tt_SiDigit_hitID2       ->GetEntry(m_entry);   //!

  m_SiDigit_n  = tt_SiDigit_n ;

  return;
}


void EventReader::clearEventData()
{
  m_eventInfoSet = false;
  m_run       = -1;
  m_event     = -1;

  m_pvtrack_nsteps  = -1;
  m_back_nsteps     = -1;
  m_ele_nsteps      = -1;
  m_pos_nsteps      = -1;
  m_CalLayer_nlayer = -1;
  m_SiHit_n         = -1;
  m_SiDigit_n       = -1;

  return;
}
