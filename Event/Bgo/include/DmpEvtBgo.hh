/*=============================================================================
#       FileName :          DmpEvtBgo.hh
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-03   20:01:19
#
#------------------------------------------------------------------------------
#       Description  :
#           all type of Bgo Event
#           *   DmpEvtBgoRaw
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-03   20:01:19
=============================================================================*/

#ifndef DmpEvtBgo_H
#define DmpEvtBgo_H

#include <iostream>
//#include <vector>

#include "DmpEvtVBasicSubDet.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtBgoRaw : public DmpEvtVBasicSubDet{
 public:
  DmpEvtBgoRaw();
  ~DmpEvtBgoRaw();
  void   Reset();                   // reset a event
  Bool_t BookBranch(TTree* tree, Bool_t read, TString detectorName);              // all branch of Bgo Raw
  void   SetSignal(Short_t layerID,Short_t barID,Short_t sideID,Short_t dyID,Float_t adc);        // set a signal of one channal in a event

 private:
  void BookBranchBgoRaw(TTree* tree, Bool_t read, TString detectorName);

 private:
  std::vector<int>   *fLayerID;     // must use vector<int> or vector<double> in branch 
  std::vector<int>   *fBarID;
  std::vector<int>   *fSideID;
  std::vector<int>   *fDyID;
  std::vector<double> *fADC;

};


//  class DmpEvtXXXXRec  for DmpRec
//class DmpEvtBgoRecL0 : public DmpEvtBasic{}


//  class DmpEvtXXXXDst  for Analysis part of DMPSW


#endif

