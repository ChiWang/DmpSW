/*=====================================================================
 *   File:   DmpEvtBgoRaw.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:10:44
=====================================================================*/

#ifndef DmpEvtBgoRaw_H
#define DmpEvtBgoRaw_H

#include <vector>

#include "DmpEvtSubDet.hh"

class DmpEvtBgoRaw : public DmpEvtSubDet{
/*
 *  DmpEvtBgoRaw
 *
 *  hex data to dec root file, store raw data of Bgo.
 *
 *  For one event:
 *      1.  how many dynode has signal?     (fNSignal)
 *      2.  and, what is the ADC value from evry dynode?    (fADC)
 *      3.  and, where is this dynode?      (fLayerId, fBarID, fSideID, fDyID)
 *      4.  and, some variables inherit from DmpEvtSubDet
 *
*/

 public:
  DmpEvtBgoRaw();
  ~DmpEvtBgoRaw();
  void  Reset();
  void  PrintEvent() const;
  void  PrintEvent(Short_t layerID,Short_t barID,Short_t sideID,Short_t dyID);
  void  SetSignal(Int_t LBSD_ID,Double_t adc);
  Int_t GetSignalNumber() const {return fNSignal;}

 private:
  Int_t                 fNSignal;       // signal number of Bgo of current event
  std::vector<int>      fLBSD_ID;       //  LayerID*10000 + BarID*100 + SideID*10 +DyID= fLBSD_ID   (must use vector<int> or vector<double>)
  std::vector<double>   fADC;

 private:
  Int_t CreateLBSDID(Short_t Layer,Short_t Bar,Short_t Side,Short_t Dy);

  ClassDef(DmpEvtBgoRaw,1)

};

#endif


