/*=============================================================================
#       FileName :          DmpEvtAbsHeader.hh
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
#                                          Update:  2013-11-12   23:18:24
=============================================================================*/

#ifndef DmpEvtAbsHeader_H
#define DmpEvtAbsHeader_H

#include "TObject.h"

class TTree;
class TString;

enum EParticleID {
  kUnknown  = -99,
  kElectron = -1,
  kMuon     = 0,
  kProton   = 9,
  kCarbon   = 12,
};

class DmpEvtAbsHeader : public TObject{
 protected:
  Long64_t      fEvtID;             // valid event count. continnue
  Long64_t      fSec;               // Time, sec + msec
  Short_t       fmSec;              //
  Long64_t      fTimeGap;           // unit:   msec
  EParticleID   fPID;               // Particle ID
//Int_t         fCharge;            // Particle charge

 protected:
  void  BookBranchAbsHeader(TTree *tree, Bool_t read, TString Header);         // all types Header has this branch

 public:
  DmpEvtAbsHeader();
  virtual ~DmpEvtAbsHeader();
  Long64_t   GetEventID() const;
  Long64_t   GetTimeGap() const;
  void  ShowTime() const;
  virtual void Reset() = 0;
  virtual Bool_t BookBranch(TTree *tree, Bool_t read, TString detectorName) = 0;

  ClassDef(DmpEvtAbsHeader,1)
};

//______________________________________________________________________________
inline Long64_t DmpEvtAbsHeader::GetEventID() const {
  return fEvtID;
}

//______________________________________________________________________________
inline Long64_t DmpEvtAbsHeader::GetTimeGap() const {
  return fTimeGap;
}

#endif


