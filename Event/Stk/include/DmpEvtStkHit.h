/*
 *  $Id: DmpEvtStkHit.h, 2014-03-03 23:47:21 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtStkHit_H
#define DmpEvtStkHit_H

#include "TObject.h"

class DmpEvtStkHit : public TObject{
/*
 *  DmpEvtStkHit
 *  
 *  One DmpEvtStkHit is a response of one Stk Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtStkHits and other sub-dets' hit collection
 *
 *  Both of Simulation and Analysis will use this class, but, DmpEvtPMT will not be used while Simulation
 *
*/

public:
  DmpEvtStkHit();
  ~DmpEvtStkHit();
  void  Reset();
  void  PrintHit() const;
  void  AddThisHit(double e,double x,double y,double z);     // only for simulation, invoke from G4Step or Sensitive Detector
  int   GetSDID() const     {return fSDID;}
  int   SetSDID(int id)     {fSDID = id;}
  double GetEnergy() const  {return fEnergy;}
  void  SetEnergy(double e) {fEnergy = e;}
  short GetUsedSide() const {return fUsedSide;}
  void SetUsedSide(short i) {fUsedSide = i;}
  double* GetPosition() {return fPosition;}
  void SetPosition(double x, double y, double z) {fPosition[0]=x;fPosition[1]=y;fPosition[2]=z;}

private:
  int       fSDID;          // unique sensitive detector(minimum detector unit) ID. Stk bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  short     fUsedSide;      // used which side for fEnergy
  double    fPosition[3];   // unit cm

  ClassDef(DmpEvtStkHit,1)

};

#endif
