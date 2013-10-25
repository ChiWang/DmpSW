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

#include <vector>

#include "DmpEvtVSubDet.hh"

//typedef std::vector<int>  dmpContainerInt;
//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtBgoRaw : public DmpEvtVSubDet{
 public:
  DmpEvtBgoRaw(DmpEvtVHeader*);
  ~DmpEvtBgoRaw();
  void   Reset();                   // reset a event
  Bool_t BookBranch(TTree *tree, Bool_t read, TString detectorName);              // all branch of Bgo Raw
  void   PrintEvent() const;
  void   SetSignal(Short_t planeID,Short_t quadrantID,Short_t barID,Short_t dyID,Float_t adc);        // set a signal of one channal in a event
  std::vector<int>*     GetEvent(TString);
  std::vector<double>*  GetEventADC();

 private:
  void BookBranchBgoRaw(TTree *tree, Bool_t read, TString detectorName);

 private:
  std::vector<int>      *fPlaneID;      //! (1) must use vector<int> or vector<double> in branch. (2) must use pointer here, in order to SetBranchAddress() latter
  std::vector<int>      *fQuadrantID;   //! one plane has 2 layers, each layer has 2 quadrants. 0,2 -> X layer. 1,3 -> Y layer
  std::vector<int>      *fBarID;        //! 1 layer use the SAME bar ID for 2 quadrants
  std::vector<int>      *fDyID;
  std::vector<double>   *fADC;

};


//  class DmpEvtXXXXRec  for DmpRec
//  class DmpEvtBgoRecL0 : public DmpEvt{}

//  class DmpEvtXXXXDst  for Analysis part of DMPSW

#endif


