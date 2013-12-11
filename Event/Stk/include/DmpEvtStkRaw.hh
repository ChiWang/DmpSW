
#ifndef DmpEvtStkRaw_H
#define DmpEvtStkRaw_H

#include <vector>

#include "DmpEvtAbsSubDet.hh"

class DmpEvtStkRaw : public DmpEvtAbsSubDet{
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
  std::vector<double>   fADC;

};


#endif


