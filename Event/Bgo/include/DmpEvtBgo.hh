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

#include "DmpEvtVBasicSubDet.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtBgoRaw : public DmpEvtVBasicSubDet{
 public:
  DmpEvtBgoRaw();
  ~DmpEvtBgoRaw();
  TTree* GetTree(TString);          // create a new tree, with the name of argument
  TTree* GetTree(TString,TFile*);   // read a existed tree in a existed root file
  void   Reset();                   // reset a event
  void   SetSignal(Short_t layerID,Short_t barID,Short_t sideID,Short_t dyID,Float_t adc);        // set a signal of one channal in a event

 private:
  std::vector<Short_t>   fLayerID;         // one event 2016 channles signal at most.
  std::vector<Short_t>   fBarID;
  std::vector<Short_t>   fSideID;
  std::vector<Short_t>   fDyID;
  std::vector<Short_t>   fADC;
/*
  Short_t   fLayerID[2016];         // one event 2016 channles signal at most.
  Short_t   fBarID[2016];
  Short_t   fSideID[2016];
  Short_t   fDyID[2016];
  Float_t   fADC[2016];
*/

};


//  class DmpEvtXXXXRec  for DmpRec
//class DmpEvtBgoRecL0 : public DmpEvtBasic{}


//  class DmpEvtXXXXDst  for Analysis part of DMPSW


#endif

