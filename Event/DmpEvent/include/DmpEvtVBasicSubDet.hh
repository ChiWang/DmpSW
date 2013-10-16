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

#include "DmpEvtVBasic.hh"

class DmpEvtVBasicSubDet : public DmpEvtVBasic{
 public:
  DmpEvtVBasicSubDet();
  virtual ~DmpEvtVBasicSubDet();
  inline Short_t GetSignalNumber() const    {return fNSignal;}
  inline void  SetMode(DmpDcdRunMode M0)    {fMode = M0;}

 protected:
  void BookBranchSubDet(TString sub_detectorName);      // all Sub-detector has this branch

 protected:
  Short_t       fNSignal;       // max number of signal of sub-detector

};

#endif


