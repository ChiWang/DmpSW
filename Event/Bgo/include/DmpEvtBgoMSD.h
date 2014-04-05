/*
 *  $Id: DmpEvtBgoMSD.h, 2014-04-05 14:34:41 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtBgoMSD_H
#define DmpEvtBgoMSD_H

#include "TObject.h"

//-------------------------------------------------------------------
struct DmpEvtBgoPMT : public TObject{
  short     fAdcDy2;    // Adc value of dynode 2
  short     fAdcDy5;    // Adc value of dynode 5
  short     fAdcDy8;    // Adc value of dynode 8
  short     fUsedDy;    // used which dynode
  double    fEnergy;    // unit MeV
  DmpEvtBgoPMT()
  :fAdcDy2(-1),fAdcDy5(-1),fAdcDy8(-1),
   fUsedDy(-1),fEnergy(-1){}
  ClassDef(DmpEvtBgoPMT,1)
};

//-------------------------------------------------------------------
class DmpEvtBgoMSD : public TObject{
/*
 *  DmpEvtBgoMSD
 *  
 *  One DmpEvtBgoMSD is a response of one Bgo Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtBgoMSDs and other sub-dets' hit collection
 *
 *  Both of Simulation and Analysis will use this class, but, DmpEvtBgoPMT will not be used while Simulation
 *
*/

public:
  DmpEvtBgoMSD();
  ~DmpEvtBgoMSD();
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

public:
  DmpEvtBgoPMT *PMT0;       // side 0
  DmpEvtBgoPMT *PMT1;       // side 1

  ClassDef(DmpEvtBgoMSD,1)

};

#endif

