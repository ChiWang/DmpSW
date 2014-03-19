/*
 *  $Id: DmpEvtPsdHit.h, 2014-03-03 23:47:21 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtPsdHit_H
#define DmpEvtPsdHit_H

#include "TObject.h"

class DmpEvtPMT;
class DmpEvtPsdHit : public TObject{
/*
 *  DmpEvtPsdHit
 *  
 *  One DmpEvtPsdHit is a response of one Psd Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtPsdHits and other sub-dets' hit collection
 *
 *  Both of Simulation and Analysis will use this class, but, DmpEvtPMT will not be used while Simulation
 *
*/

public:
  DmpEvtPsdHit();
  ~DmpEvtPsdHit();
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
  DmpEvtPMT* GetPMT(short id=0) {return id==0 ? fPMT0 : fPMT1;}

private:
  int       fSDID;          // unique sensitive detector(minimum detector unit) ID. Psd bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  short     fUsedSide;      // used which side for fEnergy
  double    fPosition[3];   // unit cm
  DmpEvtPMT  *fPMT0;        // side 0
  DmpEvtPMT  *fPMT1;        // side 1

  ClassDef(DmpEvtPsdHit,1)

};

#endif
