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
  static Bool_t BookTree(TString treeName, TFile* rootFile=0);
    // treeName: all level data in one root file with different tree name.
    // rootFile != 0, return the treePointer in the rootFile; rootFile = 0, create a new tree;
  static TTree* GetTreePointer()            {return fTree;}
  inline DmpDcdRunMode GetMode() const      {return fMode;}

 protected:
  void BookBranchBasic(TString sub_detectorName);                // Book Branch of data members

 protected:
  static  TTree*    fTree;          //! tree pointers of sub-detector are the same
  static  TFile*    fRootFile;      //! fRootFile == 0, will create a new one later; fRootFileName != 0, fTree in fRootFileName

 protected:
  DmpDcdRunMode     fMode;          // run mode

};

#endif


