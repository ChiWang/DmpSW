/*
 *  $Id: DmpEvtMCPsdMSD.h, 2014-05-01 20:53:20 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtMCPsdMSD_H
#define DmpEvtMCPsdMSD_H

#include "TObject.h"

class DmpEvtMCPsdMSD : public TObject{
/*
 *  DmpEvtMCPsdMSD
 *
 *      This class used to descrip a Psd strip.
*/
public:
  DmpEvtMCPsdMSD();
  ~DmpEvtMCPsdMSD();
  void  SetSDID(const short &id)   {fSDID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  void  SetBackTrack(const int&,const double&,const double&);
  const short&  GetSDID() const    {return fSDID;}
  const double& GetEnergy() const  {return fEnergy;}
  const double& PositionX() const  {return fPosX;}
  const double& PositionY() const  {return fPosY;}
  const double& PositionZ() const  {return fPosZ;}
  std::vector<int>  GetBackTrackID() const {return fBackTrackID;}

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Psd strip ID. fSDID =  layerID*100 + stripID
  double    fEnergy;        // unit MeV
  double    fPosX;          // unit mm, position x
  double    fPosY;          // unit mm, position y
  double    fPosZ;          // unit mm, position z
  std::vector<int>      fBackTrackID;       // ID of back track
  std::vector<double>   fBackTrackPosZ;     // where is the track created, Z position
  std::vector<double>   fBTDepositedE;      // Total energy of back track deposited in Psd

  ClassDef(DmpEvtMCPsdMSD,1)
};

#endif

