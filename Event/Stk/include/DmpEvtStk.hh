
#ifndef DmpEvtStk_H
#define DmpEvtStk_H

#include "DmpEvtVBasicSubDet.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtStkRaw : public DmpEvtVBasicSubDet{
 public:
  DmpEvtStkRaw();
  ~DmpEvtStkRaw();
  TTree* GetTree(TString);          // create a new tree, with the name of argument
  TTree* GetTree(TString,TFile*);   // read a existed tree in a existed root file
  void  SetSignal(Float_t adc);

 private:
  Float_t   fADC;

};

//  class DmpEvtXXXXRec  for DmpRec
//class DmpEvtBgoRecL0 : public DmpEvtBasic{}


//  class DmpEvtXXXXDst  for Analysis part of DMPSW




#endif

