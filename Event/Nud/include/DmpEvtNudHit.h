/*
 *  $Id: DmpEvtNudHit.h, 2014-03-22 02:29:58 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtNudHit_H
#define DmpEvtNudHit_H

#include "TObject.h"

class DmpEvtNudHit : public TObject{
/*
 *  DmpEvtNudHit
 *  
 *  One DmpEvtNudHit is a response of one Nud Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtNudHits and other sub-dets' hit collection
 *
 *  Both of Simulation and Analysis will use this class, but, DmpEvtPMT will not be used while Simulation
 *
*/

public:
  DmpEvtNudHit();
  ~DmpEvtNudHit();
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
  int       fSDID;          // unique sensitive detector(minimum detector unit) ID. Nud bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  short     fUsedSide;      // used which side for fEnergy
  double    fPosition[3];   // unit cm

  ClassDef(DmpEvtNudHit,1)

};

#endif
