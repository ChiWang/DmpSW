
#ifndef DmpEvtNudRaw_H
#define DmpEvtNudRaw_H

#include <vector>

#include "DmpEvtSubDet.hh"

class DmpEvtNudRaw : public DmpEvtSubDet{
/*
 * DmpEvtNudRaw
 *
 *
 *
*/

 public:
  DmpEvtNudRaw();
  ~DmpEvtNudRaw();
  void  Reset();
  void  PrintEvent() const;
  void  SetSignal(Float_t adc);

 private:
  std::vector<double>   fADC;

};


#endif


