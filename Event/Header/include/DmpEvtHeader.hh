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
#                                          Update:  2013-11-12   23:13:29
=============================================================================*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include "DmpEvtAbsHeader.hh"

class DmpEvtHeaderRaw : public DmpEvtAbsHeader{
 private:
  Long64_t      fPackageID;         // Discard wrong package. may not continue

 private:
  void BookBranchHeaderRaw(TTree *tree, Bool_t read, TString detectorName);

 public:
  DmpEvtHeaderRaw();
  ~DmpEvtHeaderRaw();
  void  SetTime(Short_t *time);     // converte hex time to dec time and cal. time gap
  void      Reset();
  Long64_t  GetPackageID() const;
  Bool_t BookBranch(TTree *tree, Bool_t read, TString detector);              // book all branches of Header Raw
  void   IsValidPackage();          // count fPackageID if package header of science data is correct
  Bool_t IsValidEvent();

};

//______________________________________________________________________________
inline DmpEvtHeaderRaw::Reset(){
  fEvtID = -1;
  fSec = 0;
  fmSec = 0;
  fTimeGap = 0;
  fPID = kUnknown;
  fPackageID = -1;
}

//______________________________________________________________________________
inline DmpEvtHeaderRaw::GetPackageID() const {
  return fPackageID;
}

#endif

