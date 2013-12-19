/*=====================================================================
 *   File:   DmpVEvtManager.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:06:09
=====================================================================*/

#ifndef DmpVEvtManager_H
#define DmpVEvtManager_H

#include "TObject.h"

class DmpEvtHeader;
class DmpVEvtSubDet;

class DmpVEvtManager : virtual public TObject{
/*
 *  DmpVEvtManager
 *
 *  only defined fHeader, and attach the fHeader to DmpVEvtSubDet::SetHeader();
 *
 *  So, any class inherit from this class, must declare and define fPsd, fStk, fBgo, fNud in it own constructor.
 *
 *
*/
 public:
  DmpVEvtManager();
  virtual ~DmpVEvtManager();
  virtual Bool_t Core()=0;
  virtual DmpVEvtSubDet*  GetEventPointer(TString) const=0;

 protected:
  DmpEvtHeader  *fHeader;

  ClassDef(DmpVEvtManager,0)

};

#endif

