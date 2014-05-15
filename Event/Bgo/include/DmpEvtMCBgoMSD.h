/*
 *  $Id: DmpEvtMCBgoMSD.h, 2014-05-01 21:18:44 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtMCBgoMSD_H
#define DmpEvtMCBgoMSD_H

#include "TObject.h"

class DmpEvtMCBgoMSD : public TObject{
/*
 *  DmpEvtMCBgoMSD
 *  
 *  One DmpEvtMCBgoMSD is a response of one Bgo Bar.
*/
public:
  DmpEvtMCBgoMSD();
  ~DmpEvtMCBgoMSD();
  void  SetSDID(const short &id)   {fSDID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  const short&  GetSDID() const    {return fSDID;}
  const double& GetEnergy() const  {return fEnergy;}
  const double& PositionX() const  {return fPosX;}
  const double& PositionY() const  {return fPosY;}
  const double& PositionZ() const  {return fPosZ;}

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Bgo bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  double    fPosX;          // unit mm, position x
  double    fPosY;          // unit mm, position y
  double    fPosZ;          // unit mm, position z

  ClassDef(DmpEvtMCBgoMSD,1)
};

#endif

