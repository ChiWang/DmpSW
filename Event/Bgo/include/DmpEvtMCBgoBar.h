/*
 *  $Id: DmpEvtMCBgoBar.h, 2014-07-17 15:34:28 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtMCBgoBar_H
#define DmpEvtMCBgoBar_H

#include "TObject.h"

class DmpEvtMCBgoBar : public TObject{
/*
 *  DmpEvtMCBgoBar
 *  
 *  One DmpEvtMCBgoBar is a response of one Bgo Bar.
*/
public:
  DmpEvtMCBgoBar();
  ~DmpEvtMCBgoBar();
  void  SetGlobalBarID(const short &id) {fGlobalBarID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  short GetLayerID() const {return fGlobalBarID/100;}
  short GetBarID() const {return fGlobalBarID%100;}   // in one layer
  short GetGlobalBarID() const {return fGlobalBarID;} // in whole layer
  double GetEnergy() const  {return fEnergy;}
  const double& PositionX() const  {return fPosX;}
  const double& PositionY() const  {return fPosY;}
  const double& PositionZ() const  {return fPosZ;}

private:
  short     fGlobalBarID;   // unique sensitive detector(minimum detector unit) ID. Bgo bar ID. fGlobalBarID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  double    fPosX;          // unit mm, position x
  double    fPosY;          // unit mm, position y
  double    fPosZ;          // unit mm, position z

  ClassDef(DmpEvtMCBgoBar,1)
};

#endif

