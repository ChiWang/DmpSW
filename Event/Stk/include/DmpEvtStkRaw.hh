
#ifndef DmpEvtStkRaw_H
#define DmpEvtStkRaw_H

#include <vector>

#include "DmpVEvtSubDet.hh"

class DmpEvtStkRaw : public DmpVEvtSubDet{
/*
 * DmpEvtStkRaw
 *
 *
 *
*/

 public:
  DmpEvtStkRaw();
  ~DmpEvtStkRaw();
  void  Reset();
  void  PrintEvent() const;
  void  SetSignal(Float_t adc);

 private:
  std::vector<double>   fADCCollection;

  ClassDef(DmpEvtStkRaw,1)

};


#endif


