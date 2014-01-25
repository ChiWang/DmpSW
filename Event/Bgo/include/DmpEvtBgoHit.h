/*=====================================================================
 *   File:   DmpEvtBgoHit.h
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    16/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  16/12/2013   10:34:56
=====================================================================*/

#ifndef DmpEvtBgoHit_H
#define DmpEvtBgoHit_H

#include "DmpVEvtSubDet.h"

class DmpEvtBgoHit : public DmpVEvtSubDet{
/*
 *  DmpEvtBgoHit
 *   this class used in reconstruction,
 *   hit all one Bgo crystal
 *
*/

 public:
  DmpEvtBgoHit();
  ~DmpEvtBgoHit();
  void  Reset();
  void  PrintEvent() const;

 private:

  ClassDef(DmpEvtBgoHit,1)

};

#endif
