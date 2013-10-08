
#ifndef DmpEvtPsd_H
#define DmpEvtPsd_H

#include "DmpEvtVBasicSubDet.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtPsdRaw : public DmpEvtVBasicSubDet{
 public:
  DmpEvtPsdRaw();
  ~DmpEvtPsdRaw();
  TTree* GetTree(TString);          // create a new tree, with the name of argument
  TTree* GetTree(TString,TFile*);   // read a existed tree in a existed root file
  void  SetSignal(Float_t adc);

 private:
  Float_t   fADC;

};

//  class DmpEvtXXXXRec  for DmpRec
//class DmpEvtPsdRecL0 : public DmpEvtBasic{}


//  class DmpEvtXXXXDst  for Analysis part of DMPSW

#endif

