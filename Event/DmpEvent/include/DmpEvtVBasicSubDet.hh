/*=============================================================================
#       FileName :          DmpEvtVBasicSubDet.hh
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
#                                          Update:  2013-10-04   17:38:22
=============================================================================*/


#ifndef DmpEvtVBasicSubDet_H
#define DmpEvtVBasicSubDet_H

#include "TROOT.h"

#include "DmpDcdRunMode.hh"

class TTree;
class TString;
class DmpEvtVBasicHeader;

class DmpEvtVBasicSubDet {
 public:
  DmpEvtVBasicSubDet(DmpEvtVBasicHeader* header=0);
  virtual ~DmpEvtVBasicSubDet();
  inline Int_t GetHitNumber() const       {return fNHit;}
  inline void  SetMode(DmpDcdRunMode M0)    {fMode = M0;}
  inline DmpDcdRunMode GetMode() const      {return fMode;}
  virtual void Reset() = 0;
  virtual Bool_t BookBranch(TTree* tree, Bool_t read, TString detectorName) = 0;
  virtual void PrintEvent() const;

 protected:
  void BookBranchSubDet(TTree* tree, Bool_t read, TString detectorName);      // all Sub-detector has this branch

 protected:
  DmpEvtVBasicHeader*   fEvtHeader;     //! sub-detector could get event header by this
  DmpDcdRunMode         fMode;          // run mode
  Int_t                 fNHit;          // max number of signal of sub-detector

};

#endif


