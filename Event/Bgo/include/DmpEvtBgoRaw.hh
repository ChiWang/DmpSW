/*=====================================================================
 *   File:   DmpEvtBgoRaw.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  16/12/2013   11:33:44
=====================================================================*/

#ifndef DmpEvtBgoRaw_H
#define DmpEvtBgoRaw_H

#include <vector>

#include "DmpVEvtSubDet.hh"

class DmpEvtBgoRaw : public DmpVEvtSubDet{
/*
 *  DmpEvtBgoRaw
 *
 *  hex data to dec root file, store raw data of Bgo.
 *
 *  For one event:
 *      1.  collection of ADC value from evry dynode    (fADCCollection)
 *      2.  collection of ID correspond to ADC values   (fLBSDCollection:   LBSD = LayerID*10000+BarID*100+SideID*10+DyID)
 *      3.  and, some variables inherit from DmpVEvtSubDet
 *
*/

 public:
  DmpEvtBgoRaw();
  ~DmpEvtBgoRaw();
  void  Reset();
  void  PrintEvent() const;
  double PrintSignal(Short_t layerID,Short_t barID,Short_t sideID,Short_t dyID);
  void  SetSignal(Int_t LBSD_ID,Double_t adc);

 private:
  std::vector<int>      fLBSDCollection;    // LayerID*10000 + BarID*100 + SideID*10 +DyID = LBSD   (must use vector<int> or vector<double>)
  std::vector<double>   fADCCollection;

 private:
  Int_t CreateLBSDID(Short_t Layer,Short_t Bar,Short_t Side,Short_t Dy);

  ClassDef(DmpEvtBgoRaw,1)

};

#endif

