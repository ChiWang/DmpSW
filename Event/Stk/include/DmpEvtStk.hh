
#ifndef DmpEvtStk_H
#define DmpEvtStk_H

#include "DmpEvtVSubDet.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtStkRaw : public DmpEvtVSubDet{
 public:
  DmpEvtStkRaw(DmpEvtVHeader*);
  ~DmpEvtStkRaw();
  Bool_t BookBranch(TTree *tree, Bool_t read, TString detector);              // book all branches of Stk Raw
  void   Reset();                   // reset a event
  void  SetSignal(Float_t adc);

 private:
  void BookBranchStkRaw(TTree *tree, Bool_t read, TString detector);

 private:
  Float_t   fADC;

};

//  class DmpEvtXXXXRec  for DmpRec
//class DmpEvtBgoRecL0 : public DmpEvt{}


//  class DmpEvtXXXXDst  for Analysis part of DMPSW




#endif

