/*=====================================================================
 *   File:   DmpEvtBgoCluster.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    16/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  16/12/2013   10:34:56
=====================================================================*/

#ifndef DmpEvtBgoCluster_H
#define DmpEvtBgoCluster_H

#include "DmpEvtSubDet.hh"

class DmpEvtBgoCluster : public DmpEvtSubDet{
/*
 *  DmpEvtBgoCluster
 *
 *
*/

 public:
  DmpEvtBgoCluster();
  ~DmpEvtBgoCluster();
  void  Reset();
  void  PrintEvent() const;

 private:

  ClassDef(DmpEvtBgoCluster,1)

};

#endif
