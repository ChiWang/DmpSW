/*=====================================================================
 *   File:   DmpEvtBgoHit.hh
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

#include "DmpEvtSubDet.hh"

class DmpEvtBgoHit : public DmpEvtSubDet{
/*
 *  DmpEvtBgoHit
 *
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
