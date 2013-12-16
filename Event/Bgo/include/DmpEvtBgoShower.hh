/*=====================================================================
 *   File:   DmpEvtBgoShower.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    16/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  16/12/2013   10:38:45
=====================================================================*/

#ifndef DmpEvtBgoShower_H
#define DmpEvtBgoShower_H

#include "DmpEvtSubDet.hh"

class DmpEvtBgoShower : public DmpEvtSubDet{
/*
 *  DmpEvtBgoShower
 *
 *
*/

 public:
  DmpEvtBgoShower();
  ~DmpEvtBgoShower();
  void  Reset();
  void  PrintEvent() const;

 private:

  ClassDef(DmpEvtBgoShower,1)

};

#endif

