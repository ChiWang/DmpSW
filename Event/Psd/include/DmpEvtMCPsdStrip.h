/*
 *  $Id: DmpEvtMCPsdStrip.h, 2014-07-18 10:40:23 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtMCPsdStrip_H
#define DmpEvtMCPsdStrip_H

#include <map>
#include "TObject.h"

class DmpEvtMCPsdStrip : public TObject{
/*
 *  DmpEvtMCPsdStrip
 *
 *      This class used to descrip one Psd strip.
*/
public:
  DmpEvtMCPsdStrip();
  ~DmpEvtMCPsdStrip();
  void  SetGlobalStripID(const short &id)   {fGlobalStripID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  void  SetBackTrack(const int&,const double&);
  const short&  GetGlobalStripID() const    {return fGlobalStripID;}
  const double& GetEnergy() const  {return fEnergy;}
  const double& PositionX() const  {return fPosX;}
  const double& PositionY() const  {return fPosY;}
  const double& PositionZ() const  {return fPosZ;}
  std::map<int,double>  GetBackTrack() const {return fBackTrack;}

private:
  short     fGlobalStripID; // unique sensitive detector(minimum detector unit) ID. Psd strip ID. fGlobalStripID =  layerID*100 + stripID
  double    fEnergy;        // total e. unit MeV
  double    fPosX;          // unit mm, position x
  double    fPosY;          // unit mm, position y
  double    fPosZ;          // unit mm, position z
  std::map<int,double>      fBackTrack;     // key = id of back track, value = Total energy deposited in this strip by this back track

  ClassDef(DmpEvtMCPsdStrip,1)
};

#endif

