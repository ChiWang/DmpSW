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

#include "DmpEvtVBasicHeader.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtHeaderRaw : public DmpEvtVBasicHeader{
 public:
  DmpEvtHeaderRaw();
  ~DmpEvtHeaderRaw();
  inline void   Reset()                     {fSec = 0; fmSec = 0; fTimeGap = 0; fPID = kUnknown;}
  inline Long64_t   GetPackageID() const    {return fPackageID;}
  Bool_t BookBranch();              // book all branches of Header Raw
  void   IsValidPackage();          // count fPackageID if package header of science data is correct
  Bool_t IsValidEvent();
  void  SetMode(DmpDcdRunMode, DmpDcdRunMode, DmpDcdRunMode, DmpDcdRunMode);

 private:
  void BookBranchHeaderRaw();

 private:
  Long64_t      fPackageID;         // Discard wrong package. may not continue

};

#endif

