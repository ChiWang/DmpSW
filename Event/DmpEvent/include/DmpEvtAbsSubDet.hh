/*=============================================================================
#       FileName :          DmpEvtAbsSubDet.hh
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
#                                          Update:  2013-11-13   00:53:08
=============================================================================*/

#ifndef DmpEvtAbsSubDet_H
#define DmpEvtAbsSubDet_H

#include "TObject.h"

class TTree;
class TString;
class DmpEvtAbsHeader;

enum ERunMode {
  kMixed     = 0,       // only for Event Header, if sub-detectors setted different mode, run mode of Event Header is kMixed
  k0Compress = 1,       // zero compress
  kCompress  = 5,       // compress mode
  kCalPed    = 6,       // Calibrate pedestal
  kCalFEE    = 9,       // ADC Calibration
};

class DmpEvtAbsSubDet : public TObject{
 protected:
  DmpEvtAbsHeader      *fEvtHeader;     //! sub-detector could get event header by this
  ERunMode              fMode;          // run mode
  Int_t                 fNHit;          // max number of signal of sub-detector

 protected:
  void BookBranchAbsSubDet(TTree *tree, Bool_t read, TString detectorName);      // all Sub-detector has this branch

 public:
  DmpEvtAbsSubDet();
  DmpEvtAbsSubDet(DmpEvtAbsHeader*);
  virtual ~DmpEvtAbsSubDet();
  void  SetMode(ERunMode);
  ERunMode GetMode() const;
  Int_t GetHitNumber() const;
  virtual void Reset() = 0;
  virtual Bool_t BookBranch(TTree *tree, Bool_t read, TString detectorName) = 0;
  virtual void PrintEvent() const = 0;

  ClassDef(DmpEvtAbsSubDet,1)
};

//______________________________________________________________________________
inline void DmpEvtAbsSubDet::SetMode(DmpDcdRumMode M0){
  fMode = M0;
}

//______________________________________________________________________________
inline Int_t DmpEvtAbsSubDet::GetHitNumber() const {
  return fNHit;
}

//______________________________________________________________________________
inline ERunMode DmpEvtAbsSubDet::GetMode() const {
  return fMode;
}

#endif


