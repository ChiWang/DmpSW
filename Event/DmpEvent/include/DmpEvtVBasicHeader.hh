/*=============================================================================
#       FileName :          DmpEvtVBasicHeader.hh
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-03   21:58:16
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-04   09:11:07
=============================================================================*/

#ifndef DmpEvtVBasicHeader_H
#define DmpEvtVBasicHeader_H

#include "TROOT.h"

#include "DmpDcdParticle.hh"

class TTree;
class TString;

class DmpEvtVBasicHeader {
 public:
  DmpEvtVBasicHeader();
  virtual ~DmpEvtVBasicHeader();
  inline Long64_t   GetEventID() const      {return fEvtID;}
  inline Long64_t   GetTimeGap() const      {return fTimeGap;}
  void  SetTime(Short_t* time);     // converte hex time to dec time and cal. time gap
  void  ShowTime() const;           // print normal time
  virtual void Reset() = 0;
  virtual Bool_t BookBranch(TTree* tree, Bool_t read, TString detectorName) = 0;

 protected:
  void  BookBranchHeaderBasic(TTree* tree, Bool_t read, TString Header);         // all types Header has this branch

 protected:
  Long64_t       fEvtID;            // valid event count. continnue
  Long64_t       fSec;              // Time, sec + msec
  Short_t        fmSec;             //
  Long64_t       fTimeGap;          // unit:   msec
  DmpDcdParticle fPID;              // Particle ID

};

#endif


