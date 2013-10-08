//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep  6 16:11:06 2013 by ROOT version 5.34/09
// from TTree dampe/dampe tracker
// found on file: DmpSimu_Photon_1GeV_iso.root
//////////////////////////////////////////////////////////

#ifndef EventReader_h
#define EventReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <string>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.
using namespace std;

class EventReader : public TSelector {

////// begin user defined functions and variables
public :
  //varaibles filled by readEventInfo()
  int run()  { if (!m_eventInfoSet) readEventInfo(); return m_run; }
  int event(){ if (!m_eventInfoSet) readEventInfo(); return m_event; }

  //varaibles filled by readPrimaries()
  int     npv()             { return m_npv         ; }
  double  pv_x()            { return m_pv_x        ; }
  double  pv_y()            { return m_pv_y        ; }
  double  pv_z()            { return m_pv_z        ; }
  double  pvpart_px()       { return m_pvpart_px   ; }
  double  pvpart_py()       { return m_pvpart_py   ; }
  double  pvpart_pz()       { return m_pvpart_pz   ; }
  double  pvpart_ekin()     { return m_pvpart_ekin ; }
  double  pvpart_q()        { return m_pvpart_q    ; }
  int     pvpart_pdg()      { return m_pvpart_pdg  ; }

  //varaibles filled by readStepPvtrack
  int     pvtrack_nsteps()  { return m_pvtrack_nsteps; }
  vector<double>  *step_pvtrack_px()	     { return tt_step_pvtrack_px; }
  vector<double>  *step_pvtrack_py()	     { return tt_step_pvtrack_py; }
  vector<double>  *step_pvtrack_pz()	     { return tt_step_pvtrack_pz; }
  vector<double>  *step_pvtrack_ekin()       { return tt_step_pvtrack_ekin; }
  vector<double>  *step_pvtrack_x()	     { return tt_step_pvtrack_x; }
  vector<double>  *step_pvtrack_y()	     { return tt_step_pvtrack_y; }
  vector<double>  *step_pvtrack_z()	     { return tt_step_pvtrack_z; }
  vector<double>  *step_pvtrack_stepLength() { return tt_step_pvtrack_stepLength; }
  vector<double>  *step_pvtrack_trackLengt() { return tt_step_pvtrack_trackLength; }
  vector<double>  *step_pvtrack_energyDepo() { return tt_step_pvtrack_energyDeposit; }
  vector<int>     *step_pvtrack_stepNumber() { return tt_step_pvtrack_stepNumber; }
  vector<bool>    *step_pvtrack_isEntering() { return tt_step_pvtrack_isEntering; }
  vector<string>  *step_pvtrack_thisVolume() { return tt_step_pvtrack_thisVolume; }
  vector<string>  *step_pvtrack_nextVolume() { return tt_step_pvtrack_nextVolume; }
  vector<int>     *step_pvtrack_thisIndex()  { return tt_step_pvtrack_thisIndex; }
  vector<int>     *step_pvtrack_nextIndex()  { return tt_step_pvtrack_nextIndex; }

  //varaibles filled by readStepBack()
  int     back_nsteps()     { return m_back_nsteps; }
  vector<int>     *step_back_trackID()       { return tt_step_back_trackID; }
  vector<int>     *step_back_pdg()           { return tt_step_back_pdg; }
  vector<double>  *step_back_px()	     { return tt_step_back_px; }
  vector<double>  *step_back_py()	     { return tt_step_back_py; }
  vector<double>  *step_back_pz()	     { return tt_step_back_pz; }
  vector<double>  *step_back_ekin()          { return tt_step_back_ekin; }
  vector<double>  *step_back_x()	     { return tt_step_back_x; }
  vector<double>  *step_back_y()	     { return tt_step_back_y; }
  vector<double>  *step_back_z()	     { return tt_step_back_z; }
  vector<double>  *step_back_stepLength()    { return tt_step_back_stepLength; }
  vector<double>  *step_back_trackLengt()    { return tt_step_back_trackLength; }
  vector<double>  *step_back_energyDepo()    { return tt_step_back_energyDeposit; }
  vector<int>     *step_back_stepNumber()    { return tt_step_back_stepNumber; }
  vector<bool>    *step_back_isEntering()    { return tt_step_back_isEntering; }
  vector<string>  *step_back_thisVolume()    { return tt_step_back_thisVolume; }
  vector<string>  *step_back_nextVolume()    { return tt_step_back_nextVolume; }
  vector<int>     *step_back_thisIndex()     { return tt_step_back_thisIndex; }
  vector<int>     *step_back_nextIndex()     { return tt_step_pvtrack_nextIndex; }

  //varaibles filled by readStepEle
  int     ele_nsteps()  { return m_ele_nsteps; }
  vector<double>  *step_ele_px()         { return tt_step_ele_px;   }
  vector<double>  *step_ele_py()         { return tt_step_ele_py;   }
  vector<double>  *step_ele_pz()         { return tt_step_ele_pz;   }
  vector<double>  *step_ele_ekin()       { return tt_step_ele_ekin; }
  vector<double>  *step_ele_x()	         { return tt_step_ele_x;    }
  vector<double>  *step_ele_y()	         { return tt_step_ele_y;    }
  vector<double>  *step_ele_z()	         { return tt_step_ele_z;    }
  vector<double>  *step_ele_energyDepo() { return tt_step_ele_energyDeposit; }
  vector<int>     *step_ele_stepNumber() { return tt_step_ele_stepNumber;    }
  vector<bool>    *step_ele_isEntering() { return tt_step_ele_isEntering;    }
  vector<string>  *step_ele_thisVolume() { return tt_step_ele_thisVolume;    }
  vector<string>  *step_ele_nextVolume() { return tt_step_ele_nextVolume;    }
  vector<int>     *step_ele_thisIndex()  { return tt_step_ele_thisIndex;     }
  vector<int>     *step_ele_nextIndex()  { return tt_step_ele_nextIndex;     }

  //varaibles filled by readStepPos
  int     pos_nsteps()  { return m_pos_nsteps; }
  vector<double>  *step_pos_px()         { return tt_step_pos_px;   }
  vector<double>  *step_pos_py()         { return tt_step_pos_py;   }
  vector<double>  *step_pos_pz()         { return tt_step_pos_pz;   }
  vector<double>  *step_pos_ekin()       { return tt_step_pos_ekin; }
  vector<double>  *step_pos_x()	         { return tt_step_pos_x;    }
  vector<double>  *step_pos_y()	         { return tt_step_pos_y;    }
  vector<double>  *step_pos_z()	         { return tt_step_pos_z;    }
  vector<double>  *step_pos_energyDepo() { return tt_step_pos_energyDeposit; }
  vector<int>     *step_pos_stepNumber() { return tt_step_pos_stepNumber;    }
  vector<bool>    *step_pos_isEntering() { return tt_step_pos_isEntering;    }
  vector<string>  *step_pos_thisVolume() { return tt_step_pos_thisVolume;    }
  vector<string>  *step_pos_nextVolume() { return tt_step_pos_nextVolume;    }
  vector<int>     *step_pos_thisIndex()  { return tt_step_pos_thisIndex;     }
  vector<int>     *step_pos_nextIndex()  { return tt_step_pos_nextIndex;     }

  //varaibles filled by readPvtrj
  int           pvtrj_trackID()          { return m_pvtrj_trackID;    }
  string*       pvtrj_stop_vo()          { return m_pvtrj_stop_vo;    }
  int           pvtrj_stop_index()       { return m_pvtrj_stop_index; }
  double        pvtrj_stop_x()           { return m_pvtrj_stop_x;     }
  double        pvtrj_stop_y()           { return m_pvtrj_stop_y;     }
  double        pvtrj_stop_z()           { return m_pvtrj_stop_z;     }

  //varaibles filled by readEle
  double        ele_px()	         { return m_ele_px;           }
  double        ele_py()	         { return m_ele_py;	      }
  double        ele_pz()	         { return m_ele_pz;	      }
  double        ele_ekin()	         { return m_ele_ekin;	      }
  int           ele_trackID()	         { return m_ele_trackID;      }
  int           ele_parentID()	         { return m_ele_parentID;     }
  string*       ele_stop_vo()	         { return m_ele_stop_vo;      }
  int           ele_stop_index()         { return m_ele_stop_index;   }
  double        ele_stop_x()	         { return m_ele_stop_x;	      }
  double        ele_stop_y()	         { return m_ele_stop_y;	      }
  double        ele_stop_z()             { return m_ele_stop_z;       }
								      
  //varaibles filled by readPos
  double        pos_px()	         { return m_pos_px;           }
  double        pos_py()	         { return m_pos_py;	      }
  double        pos_pz()	         { return m_pos_pz;	      }
  double        pos_ekin()	         { return m_pos_ekin;	      }
  int           pos_trackID()	         { return m_pos_trackID;      }
  int           pos_parentID()	         { return m_pos_parentID;     }
  string*       pos_stop_vo()	         { return m_pos_stop_vo;      }
  int           pos_stop_index()         { return m_pos_stop_index;   }
  double        pos_stop_x()	         { return m_pos_stop_x;	      }
  double        pos_stop_y()	         { return m_pos_stop_y;	      }
  double        pos_stop_z()             { return m_pos_stop_z;       }

  //varaibles filled by readCal
  double       cal_totE()	         { return m_cal_totE;	          }
  double       cal_totE_1MeV()           { return m_cal_totE_1MeV;        } 
  double       cal_totE_10MeV()          { return m_cal_totE_10MeV;       } 
  int          CalLayer_nlayer()         { return m_CalLayer_nlayer;      } 
  int          CalLayer_nlayer_1MeV()    { return m_CalLayer_nlayer_1MeV; }
  int          CalHit_n()                { return m_CalHit_n;             }
  vector<double>  *CalLayer_centroid()       { return tt_CalLayer_centroid;      }
  vector<double>  *CalLayer_e()	             { return tt_CalLayer_e;		 }
  vector<double>  *CalLayer_sumw2()	     { return tt_CalLayer_sumw2;	 }
  vector<int>     *CalLayer_index()          { return tt_CalLayer_index;	 }
  vector<double>  *CalLayer_centroid_1MeV()  { return tt_CalLayer_centroid_1MeV; }
  vector<double>  *CalLayer_e_1MeV()	     { return tt_CalLayer_e_1MeV;        }
  vector<double>  *CalLayer_sumw2_1MeV()     { return tt_CalLayer_sumw2_1MeV;	 }
  vector<int>     *CalLayer_index_1MeV()     { return tt_CalLayer_index_1MeV;	 }
  vector<int>     *CalHit_bar()	             { return tt_CalHit_bar;		 }
  vector<double>  *CalHit_e()                { return tt_CalHit_e;               }       

  //varaibles filled by readSiHit
  int           SiHit_n()                { return m_SiHit_n;   }         
  vector<int>          *SiHit_strip()	      { return tt_SiHit_strip;          } 
  vector<int>          *SiHit_id()	      { return tt_SiHit_id;		}
  vector<unsigned int> *SiHit_trackID()       { return tt_SiHit_trackID;	}
  vector<unsigned int> *SiHit_trackID1()      { return tt_SiHit_trackID1;	}
  vector<unsigned int> *SiHit_trackID2()      { return tt_SiHit_trackID2;	}
  vector<int>          *SiHit_ntracks()       { return tt_SiHit_ntracks;	}
  vector<int>          *SiHit_ntracksBack()   { return tt_SiHit_ntracksBack;	}
  vector<int>          *SiHit_ntracksPrim()   { return tt_SiHit_ntracksPrim;    }
  vector<double>       *SiHit_e()	      { return tt_SiHit_e;		}
  vector<double>       *SiHit_e_prim()        { return tt_SiHit_e_prim;		}
  vector<double>       *SiHit_x()	      { return tt_SiHit_x;		}
  vector<double>       *SiHit_y()	      { return tt_SiHit_y;		}
  vector<double>       *SiHit_z()             { return tt_SiHit_z;           	}
										
  //varaibles filled by readSiDigit
  int           SiDigit()                { return m_SiDigit_n; }   
  vector<int>          *SiDigit_strip()        { return tt_SiDigit_strip;       }     
  vector<unsigned int> *SiDigit_trackID()      { return tt_SiDigit_trackID;	}
  vector<double>       *SiDigit_e()	       { return tt_SiDigit_e;		}
  vector<double>       *SiDigit_e_prim()       { return tt_SiDigit_e_prim;	}
  vector<int>          *SiDigit_ntracks()      { return tt_SiDigit_ntracks;	}
  vector<int>          *SiDigit_ntracksBack()  { return tt_SiDigit_ntracksBack;	}
  vector<int>          *SiDigit_ntracksPrim()  { return tt_SiDigit_ntracksPrim;	}
  vector<int>          *SiDigit_nhits()        { return tt_SiDigit_nhits;	}
  vector<int>          *SiDigit_nhitsBack()    { return tt_SiDigit_nhitsBack;	}
  vector<int>          *SiDigit_hitID()        { return tt_SiDigit_hitID;	}
  vector<int>          *SiDigit_hitID1()       { return tt_SiDigit_hitID1;	}
  vector<int>          *SiDigit_hitID2()       { return tt_SiDigit_hitID2;     	}
										
  void clearEventData();

  void readEventInfo(); 
  void readPrimaries(); 
  void readStepPvtrack();
  void readStepBack();
  void readStepEle();
  void readStepPos();
  void readPvtrj();
  void readEle();
  void readPos();
  void readCal();
  void readSiHit();
  void readSiDigit();

protected:
  Long64_t m_entry;

  bool            m_eventInfoSet;

  UInt_t          m_run;
  UInt_t          m_event;

  UInt_t          m_npv;
  Double_t        m_pv_x;
  Double_t        m_pv_y;
  Double_t        m_pv_z;
  Double_t        m_pvpart_px;
  Double_t        m_pvpart_py;
  Double_t        m_pvpart_pz;
  Double_t        m_pvpart_ekin;
  Double_t        m_pvpart_q;
  Int_t           m_pvpart_pdg;

  Int_t           m_pvtrj_trackID;
  string          *m_pvtrj_stop_vo;
  Int_t           m_pvtrj_stop_index;
  Double_t        m_pvtrj_stop_x;
  Double_t        m_pvtrj_stop_y;
  Double_t        m_pvtrj_stop_z;

  Int_t           m_pvtrack_nsteps;
  Int_t           m_back_nsteps;
  Int_t           m_ele_nsteps;
  Int_t           m_pos_nsteps;

  Double_t        m_ele_px;
  Double_t        m_ele_py;
  Double_t        m_ele_pz;
  Double_t        m_ele_ekin;
  Int_t           m_ele_trackID;
  Int_t           m_ele_parentID;
  string          *m_ele_stop_vo;
  Int_t           m_ele_stop_index;
  Double_t        m_ele_stop_x;
  Double_t        m_ele_stop_y;
  Double_t        m_ele_stop_z;

  Double_t        m_pos_px;
  Double_t        m_pos_py;
  Double_t        m_pos_pz;
  Double_t        m_pos_ekin;
  Int_t           m_pos_trackID;
  Int_t           m_pos_parentID;
  string          *m_pos_stop_vo;
  Int_t           m_pos_stop_index;
  Double_t        m_pos_stop_x;
  Double_t        m_pos_stop_y;
  Double_t        m_pos_stop_z;

  Double_t        m_cal_totE;	     
  Double_t        m_cal_totE_1MeV;    
  Double_t        m_cal_totE_10MeV;   
  Int_t           m_CalLayer_nlayer;  
  Int_t           m_CalLayer_nlayer_1MeV;  
  Int_t           m_CalHit_n;

  Int_t           m_SiHit_n;       
  Int_t           m_SiDigit_n;     
         
////// rnd user defined functions and variables

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   UInt_t          tt_run;
   UInt_t          tt_event;
   UInt_t          tt_npv;
   Double_t        tt_pv_x;
   Double_t        tt_pv_y;
   Double_t        tt_pv_z;
   Double_t        tt_pvpart_px;
   Double_t        tt_pvpart_py;
   Double_t        tt_pvpart_pz;
   Double_t        tt_pvpart_ekin;
   Double_t        tt_pvpart_q;
   Int_t           tt_pvpart_pdg;
   UInt_t          tt_pvtrack_nsteps;
   vector<double>  *tt_step_pvtrack_px;
   vector<double>  *tt_step_pvtrack_py;
   vector<double>  *tt_step_pvtrack_pz;
   vector<double>  *tt_step_pvtrack_ekin;
   vector<double>  *tt_step_pvtrack_x;
   vector<double>  *tt_step_pvtrack_y;
   vector<double>  *tt_step_pvtrack_z;
   vector<double>  *tt_step_pvtrack_stepLength;
   vector<double>  *tt_step_pvtrack_trackLength;
   vector<double>  *tt_step_pvtrack_energyDeposit;
   vector<int>     *tt_step_pvtrack_stepNumber;
   vector<bool>    *tt_step_pvtrack_isEntering;
   vector<string>  *tt_step_pvtrack_thisVolume;
   vector<string>  *tt_step_pvtrack_nextVolume;
   vector<int>     *tt_step_pvtrack_thisIndex;
   vector<int>     *tt_step_pvtrack_nextIndex;
   UInt_t          tt_back_nsteps;
   vector<int>     *tt_step_back_trackID;
   vector<int>     *tt_step_back_pdg;
   vector<double>  *tt_step_back_px;
   vector<double>  *tt_step_back_py;
   vector<double>  *tt_step_back_pz;
   vector<double>  *tt_step_back_ekin;
   vector<double>  *tt_step_back_x;
   vector<double>  *tt_step_back_y;
   vector<double>  *tt_step_back_z;
   vector<double>  *tt_step_back_stepLength;
   vector<double>  *tt_step_back_trackLength;
   vector<double>  *tt_step_back_energyDeposit;
   vector<int>     *tt_step_back_stepNumber;
   vector<bool>    *tt_step_back_isEntering;
   vector<string>  *tt_step_back_thisVolume;
   vector<string>  *tt_step_back_nextVolume;
   vector<int>     *tt_step_back_thisIndex;
   vector<int>     *tt_step_back_nextIndex;
   UInt_t          tt_ele_nsteps;
   vector<double>  *tt_step_ele_px;
   vector<double>  *tt_step_ele_py;
   vector<double>  *tt_step_ele_pz;
   vector<double>  *tt_step_ele_ekin;
   vector<double>  *tt_step_ele_x;
   vector<double>  *tt_step_ele_y;
   vector<double>  *tt_step_ele_z;
   vector<double>  *tt_step_ele_energyDeposit;
   vector<int>     *tt_step_ele_stepNumber;
   vector<bool>    *tt_step_ele_isEntering;
   vector<string>  *tt_step_ele_thisVolume;
   vector<string>  *tt_step_ele_nextVolume;
   vector<int>     *tt_step_ele_thisIndex;
   vector<int>     *tt_step_ele_nextIndex;
   UInt_t          tt_pos_nsteps;
   vector<double>  *tt_step_pos_px;
   vector<double>  *tt_step_pos_py;
   vector<double>  *tt_step_pos_pz;
   vector<double>  *tt_step_pos_ekin;
   vector<double>  *tt_step_pos_x;
   vector<double>  *tt_step_pos_y;
   vector<double>  *tt_step_pos_z;
   vector<double>  *tt_step_pos_stepLength;
   vector<double>  *tt_step_pos_trackLength;
   vector<double>  *tt_step_pos_energyDeposit;
   vector<int>     *tt_step_pos_stepNumber;
   vector<bool>    *tt_step_pos_isEntering;
   vector<string>  *tt_step_pos_thisVolume;
   vector<string>  *tt_step_pos_nextVolume;
   vector<int>     *tt_step_pos_thisIndex;
   vector<int>     *tt_step_pos_nextIndex;
   Int_t           tt_pvtrj_trackID;
   string          *tt_pvtrj_stop_vo;
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
   string          *tt_ele_stop_vo;
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
   string          *tt_pos_stop_vo;
   Int_t           tt_pos_stop_index;
   Double_t        tt_pos_stop_x;
   Double_t        tt_pos_stop_y;
   Double_t        tt_pos_stop_z;
   UInt_t          tt_sec_n;
   Double_t        tt_cal_totE;
   Double_t        tt_cal_totE_1MeV;
   Double_t        tt_cal_totE_10MeV;
   UInt_t          tt_CalLayer_nlayer;
   vector<double>  *tt_CalLayer_centroid;
   vector<double>  *tt_CalLayer_e;
   vector<double>  *tt_CalLayer_sumw2;
   vector<int>     *tt_CalLayer_index;
   UInt_t          tt_CalLayer_nlayer_1MeV;
   vector<double>  *tt_CalLayer_centroid_1MeV;
   vector<double>  *tt_CalLayer_e_1MeV;
   vector<double>  *tt_CalLayer_sumw2_1MeV;
   vector<int>     *tt_CalLayer_index_1MeV;
   UInt_t          tt_CalHit_n;
   vector<int>     *tt_CalHit_bar;
   vector<double>  *tt_CalHit_e;
   UInt_t          tt_SiHit_n;
   vector<int>     *tt_SiHit_strip;
   vector<int>     *tt_SiHit_id;
   vector<unsigned int> *tt_SiHit_trackID;
   vector<unsigned int> *tt_SiHit_trackID1;
   vector<unsigned int> *tt_SiHit_trackID2;
   vector<int>     *tt_SiHit_ntracks;
   vector<int>     *tt_SiHit_ntracksBack;
   vector<int>     *tt_SiHit_ntracksPrim;
   vector<double>  *tt_SiHit_e;
   vector<double>  *tt_SiHit_e_prim;
   vector<double>  *tt_SiHit_x;
   vector<double>  *tt_SiHit_y;
   vector<double>  *tt_SiHit_z;
   UInt_t          tt_SiDigit_n;
   vector<int>     *tt_SiDigit_strip;
   vector<unsigned int> *tt_SiDigit_trackID;
   vector<double>  *tt_SiDigit_e;
   vector<double>  *tt_SiDigit_e_prim;
   vector<int>     *tt_SiDigit_ntracks;
   vector<int>     *tt_SiDigit_ntracksBack;
   vector<int>     *tt_SiDigit_ntracksPrim;
   vector<int>     *tt_SiDigit_nhits;
   vector<int>     *tt_SiDigit_nhitsBack;
   vector<int>     *tt_SiDigit_hitID;
   vector<int>     *tt_SiDigit_hitID1;
   vector<int>     *tt_SiDigit_hitID2;

   // List of branches
   TBranch        *b_tt_run;   //!
   TBranch        *b_tt_event;   //!
   TBranch        *b_tt_npv;   //!
   TBranch        *b_tt_pv_x;   //!
   TBranch        *b_tt_pv_y;   //!
   TBranch        *b_tt_pv_z;   //!
   TBranch        *b_tt_pvpart_px;   //!
   TBranch        *b_tt_pvpart_py;   //!
   TBranch        *b_tt_pvpart_pz;   //!
   TBranch        *b_tt_pvpart_ekin;   //!
   TBranch        *b_tt_pvpart_q;   //!
   TBranch        *b_tt_pvpart_pdg;   //!
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
   TBranch        *b_tt_sec_n;   //!
   TBranch        *b_tt_cal_totE;   //!
   TBranch        *b_tt_cal_totE_1MeV;   //!
   TBranch        *b_tt_cal_totE_10MeV;   //!
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

   EventReader(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~EventReader() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

  //ClassDef(EventReader,0);
};

#endif

#ifdef EventReader_cxx
void EventReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   tt_step_pvtrack_px = 0;
   tt_step_pvtrack_py = 0;
   tt_step_pvtrack_pz = 0;
   tt_step_pvtrack_ekin = 0;
   tt_step_pvtrack_x = 0;
   tt_step_pvtrack_y = 0;
   tt_step_pvtrack_z = 0;
   tt_step_pvtrack_stepLength = 0;
   tt_step_pvtrack_trackLength = 0;
   tt_step_pvtrack_energyDeposit = 0;
   tt_step_pvtrack_stepNumber = 0;
   tt_step_pvtrack_isEntering = 0;
   tt_step_pvtrack_thisVolume = 0;
   tt_step_pvtrack_nextVolume = 0;
   tt_step_pvtrack_thisIndex = 0;
   tt_step_pvtrack_nextIndex = 0;
   tt_step_back_trackID = 0;
   tt_step_back_pdg = 0;
   tt_step_back_px = 0;
   tt_step_back_py = 0;
   tt_step_back_pz = 0;
   tt_step_back_ekin = 0;
   tt_step_back_x = 0;
   tt_step_back_y = 0;
   tt_step_back_z = 0;
   tt_step_back_stepLength = 0;
   tt_step_back_trackLength = 0;
   tt_step_back_energyDeposit = 0;
   tt_step_back_stepNumber = 0;
   tt_step_back_isEntering = 0;
   tt_step_back_thisVolume = 0;
   tt_step_back_nextVolume = 0;
   tt_step_back_thisIndex = 0;
   tt_step_back_nextIndex = 0;
   tt_step_ele_px = 0;
   tt_step_ele_py = 0;
   tt_step_ele_pz = 0;
   tt_step_ele_ekin = 0;
   tt_step_ele_x = 0;
   tt_step_ele_y = 0;
   tt_step_ele_z = 0;
   tt_step_ele_energyDeposit = 0;
   tt_step_ele_stepNumber = 0;
   tt_step_ele_isEntering = 0;
   tt_step_ele_thisVolume = 0;
   tt_step_ele_nextVolume = 0;
   tt_step_ele_thisIndex = 0;
   tt_step_ele_nextIndex = 0;
   tt_step_pos_px = 0;
   tt_step_pos_py = 0;
   tt_step_pos_pz = 0;
   tt_step_pos_ekin = 0;
   tt_step_pos_x = 0;
   tt_step_pos_y = 0;
   tt_step_pos_z = 0;
   tt_step_pos_stepLength = 0;
   tt_step_pos_trackLength = 0;
   tt_step_pos_energyDeposit = 0;
   tt_step_pos_stepNumber = 0;
   tt_step_pos_isEntering = 0;
   tt_step_pos_thisVolume = 0;
   tt_step_pos_nextVolume = 0;
   tt_step_pos_thisIndex = 0;
   tt_step_pos_nextIndex = 0;
   tt_pvtrj_stop_vo = 0;
   tt_ele_stop_vo = 0;
   tt_pos_stop_vo = 0;
   tt_CalLayer_centroid = 0;
   tt_CalLayer_e = 0;
   tt_CalLayer_sumw2 = 0;
   tt_CalLayer_index = 0;
   tt_CalLayer_centroid_1MeV = 0;
   tt_CalLayer_e_1MeV = 0;
   tt_CalLayer_sumw2_1MeV = 0;
   tt_CalLayer_index_1MeV = 0;
   tt_CalHit_bar = 0;
   tt_CalHit_e = 0;
   tt_SiHit_strip = 0;
   tt_SiHit_id = 0;
   tt_SiHit_trackID = 0;
   tt_SiHit_trackID1 = 0;
   tt_SiHit_trackID2 = 0;
   tt_SiHit_ntracks = 0;
   tt_SiHit_ntracksBack = 0;
   tt_SiHit_ntracksPrim = 0;
   tt_SiHit_e = 0;
   tt_SiHit_e_prim = 0;
   tt_SiHit_x = 0;
   tt_SiHit_y = 0;
   tt_SiHit_z = 0;
   tt_SiDigit_strip = 0;
   tt_SiDigit_trackID = 0;
   tt_SiDigit_e = 0;
   tt_SiDigit_e_prim = 0;
   tt_SiDigit_ntracks = 0;
   tt_SiDigit_ntracksBack = 0;
   tt_SiDigit_ntracksPrim = 0;
   tt_SiDigit_nhits = 0;
   tt_SiDigit_nhitsBack = 0;
   tt_SiDigit_hitID = 0;
   tt_SiDigit_hitID1 = 0;
   tt_SiDigit_hitID2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("tt_run", &tt_run, &b_tt_run);
   fChain->SetBranchAddress("tt_event", &tt_event, &b_tt_event);
   fChain->SetBranchAddress("tt_npv", &tt_npv, &b_tt_npv);
   fChain->SetBranchAddress("tt_pv_x", &tt_pv_x, &b_tt_pv_x);
   fChain->SetBranchAddress("tt_pv_y", &tt_pv_y, &b_tt_pv_y);
   fChain->SetBranchAddress("tt_pv_z", &tt_pv_z, &b_tt_pv_z);
   fChain->SetBranchAddress("tt_pvpart_px", &tt_pvpart_px, &b_tt_pvpart_px);
   fChain->SetBranchAddress("tt_pvpart_py", &tt_pvpart_py, &b_tt_pvpart_py);
   fChain->SetBranchAddress("tt_pvpart_pz", &tt_pvpart_pz, &b_tt_pvpart_pz);
   fChain->SetBranchAddress("tt_pvpart_ekin", &tt_pvpart_ekin, &b_tt_pvpart_ekin);
   fChain->SetBranchAddress("tt_pvpart_q", &tt_pvpart_q, &b_tt_pvpart_q);
   fChain->SetBranchAddress("tt_pvpart_pdg", &tt_pvpart_pdg, &b_tt_pvpart_pdg);
   fChain->SetBranchAddress("tt_pvtrack_nsteps", &tt_pvtrack_nsteps, &b_tt_pvtrack_nsteps);
   fChain->SetBranchAddress("tt_step_pvtrack_px", &tt_step_pvtrack_px, &b_tt_step_pvtrack_px);
   fChain->SetBranchAddress("tt_step_pvtrack_py", &tt_step_pvtrack_py, &b_tt_step_pvtrack_py);
   fChain->SetBranchAddress("tt_step_pvtrack_pz", &tt_step_pvtrack_pz, &b_tt_step_pvtrack_pz);
   fChain->SetBranchAddress("tt_step_pvtrack_ekin", &tt_step_pvtrack_ekin, &b_tt_step_pvtrack_ekin);
   fChain->SetBranchAddress("tt_step_pvtrack_x", &tt_step_pvtrack_x, &b_tt_step_pvtrack_x);
   fChain->SetBranchAddress("tt_step_pvtrack_y", &tt_step_pvtrack_y, &b_tt_step_pvtrack_y);
   fChain->SetBranchAddress("tt_step_pvtrack_z", &tt_step_pvtrack_z, &b_tt_step_pvtrack_z);
   fChain->SetBranchAddress("tt_step_pvtrack_stepLength", &tt_step_pvtrack_stepLength, &b_tt_step_pvtrack_stepLength);
   fChain->SetBranchAddress("tt_step_pvtrack_trackLength", &tt_step_pvtrack_trackLength, &b_tt_step_pvtrack_trackLength);
   fChain->SetBranchAddress("tt_step_pvtrack_energyDeposit", &tt_step_pvtrack_energyDeposit, &b_tt_step_pvtrack_energyDeposit);
   fChain->SetBranchAddress("tt_step_pvtrack_stepNumber", &tt_step_pvtrack_stepNumber, &b_tt_step_pvtrack_stepNumber);
   fChain->SetBranchAddress("tt_step_pvtrack_isEntering", &tt_step_pvtrack_isEntering, &b_tt_step_pvtrack_isEntering);
   fChain->SetBranchAddress("tt_step_pvtrack_thisVolume", &tt_step_pvtrack_thisVolume, &b_tt_step_pvtrack_thisVolume);
   fChain->SetBranchAddress("tt_step_pvtrack_nextVolume", &tt_step_pvtrack_nextVolume, &b_tt_step_pvtrack_nextVolume);
   fChain->SetBranchAddress("tt_step_pvtrack_thisIndex", &tt_step_pvtrack_thisIndex, &b_tt_step_pvtrack_thisIndex);
   fChain->SetBranchAddress("tt_step_pvtrack_nextIndex", &tt_step_pvtrack_nextIndex, &b_tt_step_pvtrack_nextIndex);
   fChain->SetBranchAddress("tt_back_nsteps", &tt_back_nsteps, &b_tt_back_nsteps);
   fChain->SetBranchAddress("tt_step_back_trackID", &tt_step_back_trackID, &b_tt_step_back_trackID);
   fChain->SetBranchAddress("tt_step_back_pdg", &tt_step_back_pdg, &b_tt_step_back_pdg);
   fChain->SetBranchAddress("tt_step_back_px", &tt_step_back_px, &b_tt_step_back_px);
   fChain->SetBranchAddress("tt_step_back_py", &tt_step_back_py, &b_tt_step_back_py);
   fChain->SetBranchAddress("tt_step_back_pz", &tt_step_back_pz, &b_tt_step_back_pz);
   fChain->SetBranchAddress("tt_step_back_ekin", &tt_step_back_ekin, &b_tt_step_back_ekin);
   fChain->SetBranchAddress("tt_step_back_x", &tt_step_back_x, &b_tt_step_back_x);
   fChain->SetBranchAddress("tt_step_back_y", &tt_step_back_y, &b_tt_step_back_y);
   fChain->SetBranchAddress("tt_step_back_z", &tt_step_back_z, &b_tt_step_back_z);
   fChain->SetBranchAddress("tt_step_back_stepLength", &tt_step_back_stepLength, &b_tt_step_back_stepLength);
   fChain->SetBranchAddress("tt_step_back_trackLength", &tt_step_back_trackLength, &b_tt_step_back_trackLength);
   fChain->SetBranchAddress("tt_step_back_energyDeposit", &tt_step_back_energyDeposit, &b_tt_step_back_energyDeposit);
   fChain->SetBranchAddress("tt_step_back_stepNumber", &tt_step_back_stepNumber, &b_tt_step_back_stepNumber);
   fChain->SetBranchAddress("tt_step_back_isEntering", &tt_step_back_isEntering, &b_tt_step_back_isEntering);
   fChain->SetBranchAddress("tt_step_back_thisVolume", &tt_step_back_thisVolume, &b_tt_step_back_thisVolume);
   fChain->SetBranchAddress("tt_step_back_nextVolume", &tt_step_back_nextVolume, &b_tt_step_back_nextVolume);
   fChain->SetBranchAddress("tt_step_back_thisIndex", &tt_step_back_thisIndex, &b_tt_step_back_thisIndex);
   fChain->SetBranchAddress("tt_step_back_nextIndex", &tt_step_back_nextIndex, &b_tt_step_back_nextIndex);
   fChain->SetBranchAddress("tt_ele_nsteps", &tt_ele_nsteps, &b_tt_ele_nsteps);
   fChain->SetBranchAddress("tt_step_ele_px", &tt_step_ele_px, &b_tt_step_ele_px);
   fChain->SetBranchAddress("tt_step_ele_py", &tt_step_ele_py, &b_tt_step_ele_py);
   fChain->SetBranchAddress("tt_step_ele_pz", &tt_step_ele_pz, &b_tt_step_ele_pz);
   fChain->SetBranchAddress("tt_step_ele_ekin", &tt_step_ele_ekin, &b_tt_step_ele_ekin);
   fChain->SetBranchAddress("tt_step_ele_x", &tt_step_ele_x, &b_tt_step_ele_x);
   fChain->SetBranchAddress("tt_step_ele_y", &tt_step_ele_y, &b_tt_step_ele_y);
   fChain->SetBranchAddress("tt_step_ele_z", &tt_step_ele_z, &b_tt_step_ele_z);
   fChain->SetBranchAddress("tt_step_ele_energyDeposit", &tt_step_ele_energyDeposit, &b_tt_step_ele_energyDeposit);
   fChain->SetBranchAddress("tt_step_ele_stepNumber", &tt_step_ele_stepNumber, &b_tt_step_ele_stepNumber);
   fChain->SetBranchAddress("tt_step_ele_isEntering", &tt_step_ele_isEntering, &b_tt_step_ele_isEntering);
   fChain->SetBranchAddress("tt_step_ele_thisVolume", &tt_step_ele_thisVolume, &b_tt_step_ele_thisVolume);
   fChain->SetBranchAddress("tt_step_ele_nextVolume", &tt_step_ele_nextVolume, &b_tt_step_ele_nextVolume);
   fChain->SetBranchAddress("tt_step_ele_thisIndex", &tt_step_ele_thisIndex, &b_tt_step_ele_thisIndex);
   fChain->SetBranchAddress("tt_step_ele_nextIndex", &tt_step_ele_nextIndex, &b_tt_step_ele_nextIndex);
   fChain->SetBranchAddress("tt_pos_nsteps", &tt_pos_nsteps, &b_tt_pos_nsteps);
   fChain->SetBranchAddress("tt_step_pos_px", &tt_step_pos_px, &b_tt_step_pos_px);
   fChain->SetBranchAddress("tt_step_pos_py", &tt_step_pos_py, &b_tt_step_pos_py);
   fChain->SetBranchAddress("tt_step_pos_pz", &tt_step_pos_pz, &b_tt_step_pos_pz);
   fChain->SetBranchAddress("tt_step_pos_ekin", &tt_step_pos_ekin, &b_tt_step_pos_ekin);
   fChain->SetBranchAddress("tt_step_pos_x", &tt_step_pos_x, &b_tt_step_pos_x);
   fChain->SetBranchAddress("tt_step_pos_y", &tt_step_pos_y, &b_tt_step_pos_y);
   fChain->SetBranchAddress("tt_step_pos_z", &tt_step_pos_z, &b_tt_step_pos_z);
   fChain->SetBranchAddress("tt_step_pos_stepLength", &tt_step_pos_stepLength, &b_tt_step_pos_stepLength);
   fChain->SetBranchAddress("tt_step_pos_trackLength", &tt_step_pos_trackLength, &b_tt_step_pos_trackLength);
   fChain->SetBranchAddress("tt_step_pos_energyDeposit", &tt_step_pos_energyDeposit, &b_tt_step_pos_energyDeposit);
   fChain->SetBranchAddress("tt_step_pos_stepNumber", &tt_step_pos_stepNumber, &b_tt_step_pos_stepNumber);
   fChain->SetBranchAddress("tt_step_pos_isEntering", &tt_step_pos_isEntering, &b_tt_step_pos_isEntering);
   fChain->SetBranchAddress("tt_step_pos_thisVolume", &tt_step_pos_thisVolume, &b_tt_step_pos_thisVolume);
   fChain->SetBranchAddress("tt_step_pos_nextVolume", &tt_step_pos_nextVolume, &b_tt_step_pos_nextVolume);
   fChain->SetBranchAddress("tt_step_pos_thisIndex", &tt_step_pos_thisIndex, &b_tt_step_pos_thisIndex);
   fChain->SetBranchAddress("tt_step_pos_nextIndex", &tt_step_pos_nextIndex, &b_tt_step_pos_nextIndex);
   fChain->SetBranchAddress("tt_pvtrj_trackID", &tt_pvtrj_trackID, &b_tt_pvtrj_trackID);
   fChain->SetBranchAddress("tt_pvtrj_stop_vo", &tt_pvtrj_stop_vo, &b_tt_pvtrj_stop_vo);
   fChain->SetBranchAddress("tt_pvtrj_stop_index", &tt_pvtrj_stop_index, &b_tt_pvtrj_stop_index);
   fChain->SetBranchAddress("tt_pvtrj_stop_x", &tt_pvtrj_stop_x, &b_tt_pvtrj_stop_x);
   fChain->SetBranchAddress("tt_pvtrj_stop_y", &tt_pvtrj_stop_y, &b_tt_pvtrj_stop_y);
   fChain->SetBranchAddress("tt_pvtrj_stop_z", &tt_pvtrj_stop_z, &b_tt_pvtrj_stop_z);
   fChain->SetBranchAddress("tt_ele_px", &tt_ele_px, &b_tt_ele_px);
   fChain->SetBranchAddress("tt_ele_py", &tt_ele_py, &b_tt_ele_py);
   fChain->SetBranchAddress("tt_ele_pz", &tt_ele_pz, &b_tt_ele_pz);
   fChain->SetBranchAddress("tt_ele_ekin", &tt_ele_ekin, &b_tt_ele_ekin);
   fChain->SetBranchAddress("tt_ele_trackID", &tt_ele_trackID, &b_tt_ele_trackID);
   fChain->SetBranchAddress("tt_ele_parentID", &tt_ele_parentID, &b_tt_ele_parentID);
   fChain->SetBranchAddress("tt_ele_stop_vo", &tt_ele_stop_vo, &b_tt_ele_stop_vo);
   fChain->SetBranchAddress("tt_ele_stop_index", &tt_ele_stop_index, &b_tt_ele_stop_index);
   fChain->SetBranchAddress("tt_ele_stop_x", &tt_ele_stop_x, &b_tt_ele_stop_x);
   fChain->SetBranchAddress("tt_ele_stop_y", &tt_ele_stop_y, &b_tt_ele_stop_y);
   fChain->SetBranchAddress("tt_ele_stop_z", &tt_ele_stop_z, &b_tt_ele_stop_z);
   fChain->SetBranchAddress("tt_pos_px", &tt_pos_px, &b_tt_pos_px);
   fChain->SetBranchAddress("tt_pos_py", &tt_pos_py, &b_tt_pos_py);
   fChain->SetBranchAddress("tt_pos_pz", &tt_pos_pz, &b_tt_pos_pz);
   fChain->SetBranchAddress("tt_pos_ekin", &tt_pos_ekin, &b_tt_pos_ekin);
   fChain->SetBranchAddress("tt_pos_trackID", &tt_pos_trackID, &b_tt_pos_trackID);
   fChain->SetBranchAddress("tt_pos_parentID", &tt_pos_parentID, &b_tt_pos_parentID);
   fChain->SetBranchAddress("tt_pos_stop_vo", &tt_pos_stop_vo, &b_tt_pos_stop_vo);
   fChain->SetBranchAddress("tt_pos_stop_index", &tt_pos_stop_index, &b_tt_pos_stop_index);
   fChain->SetBranchAddress("tt_pos_stop_x", &tt_pos_stop_x, &b_tt_pos_stop_x);
   fChain->SetBranchAddress("tt_pos_stop_y", &tt_pos_stop_y, &b_tt_pos_stop_y);
   fChain->SetBranchAddress("tt_pos_stop_z", &tt_pos_stop_z, &b_tt_pos_stop_z);
   fChain->SetBranchAddress("tt_sec_n", &tt_sec_n, &b_tt_sec_n);
   fChain->SetBranchAddress("tt_cal_totE", &tt_cal_totE, &b_tt_cal_totE);
   fChain->SetBranchAddress("tt_cal_totE_1MeV", &tt_cal_totE_1MeV, &b_tt_cal_totE_1MeV);
   fChain->SetBranchAddress("tt_cal_totE_10MeV", &tt_cal_totE_10MeV, &b_tt_cal_totE_10MeV);
   fChain->SetBranchAddress("tt_CalLayer_nlayer", &tt_CalLayer_nlayer, &b_tt_CalLayer_nlayer);
   fChain->SetBranchAddress("tt_CalLayer_centroid", &tt_CalLayer_centroid, &b_tt_CalLayer_centroid);
   fChain->SetBranchAddress("tt_CalLayer_e", &tt_CalLayer_e, &b_tt_CalLayer_e);
   fChain->SetBranchAddress("tt_CalLayer_sumw2", &tt_CalLayer_sumw2, &b_tt_CalLayer_sumw2);
   fChain->SetBranchAddress("tt_CalLayer_index", &tt_CalLayer_index, &b_tt_CalLayer_index);
   fChain->SetBranchAddress("tt_CalLayer_nlayer_1MeV", &tt_CalLayer_nlayer_1MeV, &b_tt_CalLayer_nlayer_1MeV);
   fChain->SetBranchAddress("tt_CalLayer_centroid_1MeV", &tt_CalLayer_centroid_1MeV, &b_tt_CalLayer_centroid_1MeV);
   fChain->SetBranchAddress("tt_CalLayer_e_1MeV", &tt_CalLayer_e_1MeV, &b_tt_CalLayer_e_1MeV);
   fChain->SetBranchAddress("tt_CalLayer_sumw2_1MeV", &tt_CalLayer_sumw2_1MeV, &b_tt_CalLayer_sumw2_1MeV);
   fChain->SetBranchAddress("tt_CalLayer_index_1MeV", &tt_CalLayer_index_1MeV, &b_tt_CalLayer_index_1MeV);
   fChain->SetBranchAddress("tt_CalHit_n", &tt_CalHit_n, &b_tt_CalHit_n);
   fChain->SetBranchAddress("tt_CalHit_bar", &tt_CalHit_bar, &b_tt_CalHit_bar);
   fChain->SetBranchAddress("tt_CalHit_e", &tt_CalHit_e, &b_tt_CalHit_e);
   fChain->SetBranchAddress("tt_SiHit_n", &tt_SiHit_n, &b_tt_SiHit_n);
   fChain->SetBranchAddress("tt_SiHit_strip", &tt_SiHit_strip, &b_tt_SiHit_strip);
   fChain->SetBranchAddress("tt_SiHit_id", &tt_SiHit_id, &b_tt_SiHit_id);
   fChain->SetBranchAddress("tt_SiHit_trackID", &tt_SiHit_trackID, &b_tt_SiHit_trackID);
   fChain->SetBranchAddress("tt_SiHit_trackID1", &tt_SiHit_trackID1, &b_tt_SiHit_trackID1);
   fChain->SetBranchAddress("tt_SiHit_trackID2", &tt_SiHit_trackID2, &b_tt_SiHit_trackID2);
   fChain->SetBranchAddress("tt_SiHit_ntracks", &tt_SiHit_ntracks, &b_tt_SiHit_ntracks);
   fChain->SetBranchAddress("tt_SiHit_ntracksBack", &tt_SiHit_ntracksBack, &b_tt_SiHit_ntracksBack);
   fChain->SetBranchAddress("tt_SiHit_ntracksPrim", &tt_SiHit_ntracksPrim, &b_tt_SiHit_ntracksPrim);
   fChain->SetBranchAddress("tt_SiHit_e", &tt_SiHit_e, &b_tt_SiHit_e);
   fChain->SetBranchAddress("tt_SiHit_e_prim", &tt_SiHit_e_prim, &b_tt_SiHit_e_prim);
   fChain->SetBranchAddress("tt_SiHit_x", &tt_SiHit_x, &b_tt_SiHit_x);
   fChain->SetBranchAddress("tt_SiHit_y", &tt_SiHit_y, &b_tt_SiHit_y);
   fChain->SetBranchAddress("tt_SiHit_z", &tt_SiHit_z, &b_tt_SiHit_z);
   fChain->SetBranchAddress("tt_SiDigit_n", &tt_SiDigit_n, &b_tt_SiDigit_n);
   fChain->SetBranchAddress("tt_SiDigit_strip", &tt_SiDigit_strip, &b_tt_SiDigit_strip);
   fChain->SetBranchAddress("tt_SiDigit_trackID", &tt_SiDigit_trackID, &b_tt_SiDigit_trackID);
   fChain->SetBranchAddress("tt_SiDigit_e", &tt_SiDigit_e, &b_tt_SiDigit_e);
   fChain->SetBranchAddress("tt_SiDigit_e_prim", &tt_SiDigit_e_prim, &b_tt_SiDigit_e_prim);
   fChain->SetBranchAddress("tt_SiDigit_ntracks", &tt_SiDigit_ntracks, &b_tt_SiDigit_ntracks);
   fChain->SetBranchAddress("tt_SiDigit_ntracksBack", &tt_SiDigit_ntracksBack, &b_tt_SiDigit_ntracksBack);
   fChain->SetBranchAddress("tt_SiDigit_ntracksPrim", &tt_SiDigit_ntracksPrim, &b_tt_SiDigit_ntracksPrim);
   fChain->SetBranchAddress("tt_SiDigit_nhits", &tt_SiDigit_nhits, &b_tt_SiDigit_nhits);
   fChain->SetBranchAddress("tt_SiDigit_nhitsBack", &tt_SiDigit_nhitsBack, &b_tt_SiDigit_nhitsBack);
   fChain->SetBranchAddress("tt_SiDigit_hitID", &tt_SiDigit_hitID, &b_tt_SiDigit_hitID);
   fChain->SetBranchAddress("tt_SiDigit_hitID1", &tt_SiDigit_hitID1, &b_tt_SiDigit_hitID1);
   fChain->SetBranchAddress("tt_SiDigit_hitID2", &tt_SiDigit_hitID2, &b_tt_SiDigit_hitID2);
}

Bool_t EventReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef EventReader_cxx
