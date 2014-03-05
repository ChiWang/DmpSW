/*
 *  $Id: DmpEvtBgoHit.h, 2014-03-03 23:47:21 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtBgoHit_H
#define DmpEvtBgoHit_H

#include "TObject.h"

class DmpEvtPMT;
class DmpEvtBgoHit : public TObject{
/*
 *  DmpEvtBgoHit
 *  
 *  One DmpEvtBgoHit is a response of one Bgo Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtBgoHits and other sub-dets' hit collection
 *
 *  Both of Simulation and Analysis will use this class, but, DmpEvtPMT will not be used while Simulation
 *
*/

public:
  DmpEvtBgoHit();
  ~DmpEvtBgoHit();
  void  Reset();
  void  PrintHit() const;
  void  AppendThisHit(double e,double x,double y,double z);     // only for simulation, invoke from G4Step or Sensitive Detector
  int   GetUID() const      {return fUniqueID;}
  int   SetUID(int id)      {fUniqueID = id;}
  double GetEnergy() const  {return fEnergy;}
  void  SetEnergy(double e) {fEnergy = e;}
  short GetUsedSide() const {return fUsedSide;}
  void SetUsedSide(short i) {fUsedSide = i;}
  double* GetPosition() {return fPosition;}
  void SetPosition(double x, double y, double z) {fPosition[0]=x;fPosition[1]=y;fPosition[2]=z;}
  DmpEvtPMT* GetPMT(short id=0) {return id==0 ? fPMT0 : fPMT1;}

private:
  int       fUniqueID;      // for Bgo Bar(minimum detector unit). fUniqueID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  short     fUsedSide;      // used which side for fEnergy
  double    fPosition[3];   // unit cm
  DmpEvtPMT  *fPMT0;     // side 0
  DmpEvtPMT  *fPMT1;     // side 1

  ClassDef(DmpEvtBgoHit,1)

};

#endif