/*=============================================================================
#       FileName :          DmpEvtHeader.hh
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-15   21:38:32
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-08-16   08:40:41
=============================================================================*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include "DmpEvtVHeader.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtHeaderRaw : public DmpEvtVHeader{
 public:
  DmpEvtHeaderRaw();
  ~DmpEvtHeaderRaw();
  inline void   Reset()     {fEvtID = -1; fSec = 0; fmSec = 0; fTimeGap = 0; fPID = kUnknown;fPackageID = -1;}
  inline Long64_t   GetPackageID() const    {return fPackageID;}
  Bool_t BookBranch(TTree *tree, Bool_t read, TString detector);              // book all branches of Header Raw
  void   IsValidPackage();          // count fPackageID if package header of science data is correct
  Bool_t IsValidEvent();

 private:
  void BookBranchHeaderRaw(TTree *tree, Bool_t read, TString detectorName);

 private:
  Long64_t      fPackageID;         // Discard wrong package. may not continue

};

#endif

