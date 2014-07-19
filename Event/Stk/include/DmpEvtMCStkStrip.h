/*
 *  $Id: DmpEvtMCStkStrip.h, 2014-06-09 11:12:27 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtMCStkStrip_H
#define DmpEvtMCStkStrip_H

#include <map>
#include "TObject.h"

class DmpEvtMCStkStrip : public TObject{
/*
 *  DmpEvtMCStkStrip
 *
 *      This class used to descrip a Stk strip.
*/
public:
  DmpEvtMCStkStrip();
  ~DmpEvtMCStkStrip();
  void  SetGlobalStripID(const int &id)   {fGlobalStripID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  void  SetBackTrack(const int&,const double&);
  short GetLayerID() const {return fGlobalStripID/100000;}
  short GetBlockID() const {return (fGlobalStripID%100000)/10000;}
  short GetLadderID() const {return (fGlobalStripID%10000)/1000;}
  short GetStripID() const {return fGlobalStripID%1000;}
  const int&    GetGlobalStripID() const {return fGlobalStripID;}
  const double& GetEnergy() const {return fEnergy;}
  const double& PositionX() const  {return fPosX;}
  const double& PositionY() const  {return fPosY;}
  const double& PositionZ() const  {return fPosZ;}
  std::map<int,double>  GetBackTrack() const {return fBackTrack;}

private:
  int       fGlobalStripID; // Stk strip ID. fGlobalStripID =  layerID*100000 + block*10000 + ladder*1000 + stripID. layerID = {0~11}, blockID = {0~3},ladderID = {0~3},stripID = {0~384*2-1}
  double    fEnergy;        // total e. unit MeV
  double    fPosX;          // unit mm, position x
  double    fPosY;          // unit mm, position y
  double    fPosZ;          // unit mm, position z
  std::map<int,double>   fBackTrack;     // backward track. key is ID, value is total energy(unit MeV) deposited in this strip

  ClassDef(DmpEvtMCStkStrip,1)
};

#endif


