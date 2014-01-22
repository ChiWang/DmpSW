/*=====================================================================
 *   File:   DmpVManager.h
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  26/12/2013   03:41:24
=====================================================================*/

#ifndef DmpVManager_H
#define DmpVManager_H

#include "TString.h"

class DmpEvtHeader;
class DmpVEvtSubDet;

class DmpVManager{
/*
 *  DmpVManager
 *
 *  defined fHeader, and attach the fHeader to DmpVEvtSubDet::SetHeader();
 *
 *  So, any class inherit from this class, must declare and define fPsd, fStk, fBgo, fNud in it own constructor.
 *
 *
*/

 public:
  enum DmpEPhase {
    kBT2012,
    kCT2013,
    kFinal,
  };

  DmpVManager();
  virtual ~DmpVManager();
  virtual Bool_t Core()=0;
  virtual DmpVEvtSubDet*  GetEventPointer(TString) const=0;

  void  SetInDataPath(TString);
  void  SetOutDataPath(TString);
  void  SetDataName(TString name)   {fDataName = name;}
  TString GetInDataPath() const     {return fInDataPath;}
  TString GetOutDataPath() const    {return fOutDataPath;}
  static void SetPhase(DmpEPhase p) {fPhase=p;}
  static DmpEPhase  GetPhase()      {return fPhase;}
  Int_t GetDynodeIDBgo(Short_t Layer,Short_t Bar,Short_t Side,Short_t Dy);

 protected:
  TString       fInDataPath;
  TString       fOutDataPath;
  TString       fDataName;
  DmpEvtHeader  *fHeader;
  static DmpEPhase fPhase;

};

#endif

