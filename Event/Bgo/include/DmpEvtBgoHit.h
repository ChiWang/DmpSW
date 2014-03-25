/*
 *  $Id: DmpEvtBgoHit.h, 2014-03-03 23:47:21 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtBgoHit_H
#define DmpEvtBgoHit_H

#include "TObject.h"

//-------------------------------------------------------------------
struct DmpPMTBgo :public TObject{
  short     fAdcDy2;    // Adc value of dynode 2
  short     fAdcDy5;    // Adc value of dynode 5
  short     fAdcDy8;    // Adc value of dynode 8
  short     fUsedDy;    // used which dynode
  double    fEnergy;    // unit MeV
  DmpPMTBgo()
  :fAdcDy2(0),fAdcDy5(0),fAdcDy8(0),
   fUsedDy(0),fEnergy(0){}
  ClassDef(DmpPMTBgo,1)
};

//-------------------------------------------------------------------
class DmpEvtBgoHit : public TObject{
/*
 *  DmpEvtBgoHit
 *  
 *  One DmpEvtBgoHit is a response of one Bgo Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtBgoHits and other sub-dets' hit collection
 *
 *  Both of Simulation and Analysis will use this class, but, DmpPMTBgo will not be used while Simulation
 *
*/

public:
  DmpEvtBgoHit();
  ~DmpEvtBgoHit();
  void  Reset();
  void  PrintHit() const;
  void  AddG4Hit(double e,double x,double y,double z);     // only for simulation, invoke from G4Step or Sensitive Detector
  int   GetSDID() const     {return fSDID;}
  int   SetSDID(int id)     {fSDID = id;}
  double GetEnergy() const  {return fEnergy;}
  void  SetEnergy(double e) {fEnergy = e;}
  short GetUsedSide() const {return fUsedSide;}
  void SetUsedSide(short i) {fUsedSide = i;}
  double* GetPosition() {return fPosition;}
  void SetPosition(double x, double y, double z) {fPosition[0]=x;fPosition[1]=y;fPosition[2]=z;}
  void SetSignal(const int&,const short&);

private:
  int       fSDID;          // unique sensitive detector(minimum detector unit) ID. Bgo bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  short     fUsedSide;      // used which side for fEnergy
  double    fPosition[3];   // unit cm
  DmpPMTBgo *fPMT0;         // side 0
  DmpPMTBgo *fPMT1;         // side 1

  ClassDef(DmpEvtBgoHit,1)

};

#endif
