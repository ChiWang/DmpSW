/*
 *  $Id: DmpEvtMCStkMSD.h, 2014-06-09 11:12:27 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtMCStkMSD_H
#define DmpEvtMCStkMSD_H

#include <map>
#include "TObject.h"

class DmpEvtMCStkMSD : public TObject{
/*
 *  DmpEvtMCStkMSD
 *
 *      This class used to descrip a Stk strip.
*/
public:
  DmpEvtMCStkMSD();
  ~DmpEvtMCStkMSD();
  void  SetSDID(const int &id)   {fSDID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  void  SetBackTrack(const int&,const double&);
  const int&  GetSDID() const {return fSDID;}
  const double& GetEnergy() const {return fEnergy;}
  const double& PositionX() const  {return fPosX;}
  const double& PositionY() const  {return fPosY;}
  const double& PositionZ() const  {return fPosZ;}
  std::map<int,double>  GetBackTrack() const {return fBackTrack;}

private:
  int       fSDID;          // Stk strip ID. fSDID =  layerID*100000 +block*10000 + ladder*1000 + stripID
  double    fEnergy;        // total e. unit MeV
  double    fPosX;          // unit mm, position x
  double    fPosY;          // unit mm, position y
  double    fPosZ;          // unit mm, position z
  std::map<int,double>   fBackTrack;     // backward track. key is ID, value is total energy(unit MeV) deposited in this strip

  ClassDef(DmpEvtMCStkMSD,1)
};

#endif


