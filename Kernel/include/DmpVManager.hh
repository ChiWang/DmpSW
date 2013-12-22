/*=====================================================================
 *   File:   DmpVManager.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  22/12/2013   20:18:07
=====================================================================*/

#ifndef DmpVManager_H
#define DmpVManager_H

#include "TObject.h"
#include "TString.h"

class DmpEvtHeader;
class DmpVEvtSubDet;

class DmpVManager : public TObject{
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
  DmpVManager();
  virtual ~DmpVManager();
  virtual Bool_t Core()=0;
  virtual DmpVEvtSubDet*  GetEventPointer(TString) const=0;
  void  SetInDataPath(TString);
  void  SetOutDataPath(TString);
  void  SetDataName(TString name)   {fDataName = name;}
  TString GetInDataPath() const     {return fInDataPath;}
  TString GetOutDataPath() const    {return fOutDataPath;}

 protected:
  TString       fInDataPath;
  TString       fOutDataPath;
  TString       fDataName;
  DmpEvtHeader  *fHeader;

  ClassDef(DmpVManager,0)

};

#endif

