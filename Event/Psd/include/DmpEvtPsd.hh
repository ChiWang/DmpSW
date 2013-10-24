
#ifndef DmpEvtPsd_H
#define DmpEvtPsd_H

#include "DmpEvtVBasicSubDet.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtPsdRaw : public DmpEvtVBasicSubDet{
 public:
  DmpEvtPsdRaw(DmpEvtVBasicHeader*);
  ~DmpEvtPsdRaw();
  Bool_t BookBranch(TTree* tree, Bool_t read, TString detector);              // book all branches of Psd Raw
  void   Reset();                   // reset a event
  void   SetSignal(Float_t adc);

 private:
  void BookBranchPsdRaw(TTree* tree, Bool_t read, TString detector);

 private:
  Float_t   fADC;

};

//  class DmpEvtXXXXRec  for DmpRec
//class DmpEvtPsdRecL0 : public DmpEvtBasic{}


//  class DmpEvtXXXXDst  for Analysis part of DMPSW

#endif

