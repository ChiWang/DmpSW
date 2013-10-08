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

class TFile;
class TTree;
class TString;

class DmpEvtVBasic {
 public:
  DmpEvtVBasic();
  virtual ~DmpEvtVBasic();
  virtual TTree* GetTree(TString);          // create a new tree, with the name of argument
  virtual TTree* GetTree(TString,TFile*);   // read a existed tree in a existed root file
  virtual void   Reset();             // concrete class will implement it
  inline DmpDcdRunMode GetMode() const      {return fMode;}
  void BookTree(TString);             // book a new tree, with the name of argument
  void BookTree(TString,TFile*);      // read a existed tree in a existed root file

// protected:
 public:
  Bool_t        fNewTree;       //! fTree is new created or read from old root file
  TTree*        fTree;          //! sub-detector tree of root file
  DmpDcdRunMode fMode;          // run mode

};

#endif


