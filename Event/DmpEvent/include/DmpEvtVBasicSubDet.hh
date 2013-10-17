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

class DmpEvtVBasicSubDet {
 public:
  DmpEvtVBasicSubDet();
  virtual ~DmpEvtVBasicSubDet();
  virtual void Reset();
  virtual Bool_t BookBranch(TTree* tree, Bool_t read, TString detectorName);
  inline Short_t GetSignalNumber() const    {return fNSignal;}
  inline void  SetMode(DmpDcdRunMode M0)    {fMode = M0;}
  inline DmpDcdRunMode GetMode() const      {return fMode;}

 protected:
  void BookBranchSubDet(TTree* tree, Bool_t read, TString detectorName);      // all Sub-detector has this branch

 protected:
  DmpDcdRunMode fMode;          // run mode
  Short_t       fNSignal;       // max number of signal of sub-detector

};

#endif


