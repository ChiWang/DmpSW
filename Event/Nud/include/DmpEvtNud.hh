
#ifndef DmpEvtNud_H
#define DmpEvtNud_H

#include "DmpEvtVBasicSubDet.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtNudRaw : public DmpEvtVBasicSubDet{
 public:
  DmpEvtNudRaw(DmpEvtVBasicHeader*);
  ~DmpEvtNudRaw();
  Bool_t BookBranch(TTree* tree, Bool_t read, TString detector);              // book all branches of Nud Raw
  void   Reset();                   // reset a event
  void   SetSignal(Float_t adc);

 private:
  void BookBranchNudRaw(TTree* tree, Bool_t read, TString detector);

 private:
  Float_t   fADC;

};


//  class DmpEvtXXXXRec  for DmpRec
//class DmpEvtNudRecL0 : public DmpEvtBasic{}


//  class DmpEvtXXXXDst  for Analysis part of DMPSW


#endif
