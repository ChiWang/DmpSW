/*=====================================================================
 *   File:   DmpEvtNudRaw.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:10:44
=====================================================================*/

#ifndef DmpEvtNudRaw_H
#define DmpEvtNudRaw_H

#include <vector>

#include "DmpEvtSubDet.hh"

class DmpEvtNudRaw : public DmpEvtSubDet{
/*
 *  DmpEvtNudRaw
 *
 *  hex data to dec root file, store raw data of Nud.
 *
 *  For one event:
 *      1.  collection of ADC value from evry dynode    (fADC)
 *      2.  collection of ID correspond to ADC values   (fLayerId, fBarID, fSideID, fDyID)
 *      3.  and, some variables inherit from DmpEvtSubDet
 *
*/

 public:
  DmpEvtNudRaw();
  ~DmpEvtNudRaw();
  void  Reset();
  void  PrintEvent() const;
  void  PrintEvent(Short_t layerID,Short_t barID,Short_t sideID,Short_t dyID);
  void  SetSignal(Int_t LBSD_ID,Double_t adc);

 private:
  std::vector<int>      fLBSD_ID;       //  LayerID*10000 + BarID*100 + SideID*10 +DyID= fLBSD_ID   (must use vector<int> or vector<double>)
  std::vector<double>   fADC;

 private:
  Int_t CreateLBSDID(Short_t Layer,Short_t Bar,Short_t Side,Short_t Dy);

  ClassDef(DmpEvtNudRaw,1)

};

#endif

