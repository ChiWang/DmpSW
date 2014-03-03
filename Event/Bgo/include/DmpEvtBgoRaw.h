/*
 *  $Id: DmpEvtBgoRaw.h, 2014-02-24 23:26:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/13
*/ 

#ifndef DmpEvtBgoRaw_H
#define DmpEvtBgoRaw_H

#include <vector>
#include "TObject.h"

class DmpEvtBgoRaw : public TObject{
/*
 *  DmpEvtBgoRaw
 *
 *  hex data to dec root file, store raw data of Bgo.
 *
 *  For one event:
 *      1.  collection of ADC value from evry dynode    (fADCCollection)
 *      2.  collection of ID correspond to ADC values   (fLBSDCollection:   LBSD = LayerID*10000+BarID*100+SideID*10+DyID)
 *      3.  and, some variables inherit from TObject
 *
*/

 public:
  DmpEvtBgoRaw();
  ~DmpEvtBgoRaw();
  void  Reset();
  void  PrintEvent() const;
  double GetSignal(Int_t LBSDID);
  void  SetSignal(Int_t LBSD_ID,Double_t adc);

 private:
  std::vector<int>      fLBSDCollection;    // LayerID*10000 + BarID*100 + SideID*10 +DyID = LBSD   (must use vector<int> or vector<double>)
  std::vector<double>   fADCCollection;

  ClassDef(DmpEvtBgoRaw,1)

};

#endif

