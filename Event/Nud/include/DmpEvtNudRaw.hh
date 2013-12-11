
#ifndef DmpEvtNudRaw_H
#define DmpEvtNudRaw_H

#include <vector>

#include "DmpEvtAbsSubDet.hh"

class DmpEvtNudRaw : public DmpEvtAbsSubDet{
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


