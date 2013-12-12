
#ifndef DmpEvtStkRaw_H
#define DmpEvtStkRaw_H

#include <vector>

#include "DmpEvtSubDet.hh"

class DmpEvtStkRaw : public DmpEvtSubDet{
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


