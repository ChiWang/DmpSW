
#ifndef DmpEvtPsdRaw_H
#define DmpEvtPsdRaw_H

#include <vector>

#include "DmpEvtAbsSubDet.hh"

class DmpEvtPsdRaw : public DmpEvtAbsSubDet{
/*
 * DmpEvtPsdRaw
 *
 *
 *
*/

 public:
  DmpEvtPsdRaw();
  ~DmpEvtPsdRaw();
  void  Reset();
  void  PrintEvent() const;
  void  SetSignal(Float_t adc);

 private:
  std::vector<double>   fADC;

};


#endif


