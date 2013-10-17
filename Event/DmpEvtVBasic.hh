/*=============================================================================
#       FileName :          DmpEvtVBasic.hh
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-03   21:58:25
#
#------------------------------------------------------------------------------
#       Description  :
#           Abstruct class of DmpEvtXXXX
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-03   21:58:25
=============================================================================*/


#ifndef DmpEvtVBasic_H
#define DmpEvtVBasic_H

#include "TROOT.h"

#include "DmpDcdRunMode.hh"

class TTree;
class TString;

class DmpEvtVBasic {
 public:
  DmpEvtVBasic();
  virtual ~DmpEvtVBasic();
  virtual Bool_t BookBranch(TTree* tree, Bool_t read, TString detectorName);
  inline DmpDcdRunMode GetMode() const      {return fMode;}

 protected:
  void BookBranchBasic(TTree* tree,Bool_t read, TString detectorName);                // Book Branch of data members

 protected:
  DmpDcdRunMode     fMode;          // run mode

};

#endif


