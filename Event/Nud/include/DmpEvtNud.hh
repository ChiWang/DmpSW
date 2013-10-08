
#ifndef DmpEvtNud_H
#define DmpEvtNud_H

#include "DmpEvtVBasicSubDet.hh"

//  class DmpEvtXXXXRaw  for DmpRDC and DmpCalPed
class DmpEvtNudRaw : public DmpEvtVBasicSubDet{
 public:
  DmpEvtNudRaw();
  ~DmpEvtNudRaw();
  TTree* GetTree(TString);          // create a new tree, with the name of argument
  TTree* GetTree(TString,TFile*);   // read a existed tree in a existed root file
  void   Reset();                   // reset a event
  void   SetSignal(Float_t adc);

 private:
  Float_t   fADC;

};


//  class DmpEvtXXXXRec  for DmpRec
//class DmpEvtNudRecL0 : public DmpEvtBasic{}


//  class DmpEvtXXXXDst  for Analysis part of DMPSW


#endif
