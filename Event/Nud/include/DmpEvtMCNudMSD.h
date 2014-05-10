/*
 *  $Id: DmpEvtMCNudMSD.h, 2014-05-09 11:07:37 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
 *    Yang LIU (liuy@ustc.edu) 05/05/2014
*/

#ifndef DmpEvtNudMSD_H
#define DmpEvtNudMSD_H

#include "TObject.h"

class DmpEvtMCNudMSD : public TObject{
/*
 *  DmpEvtMCNudMSD
 *  
 *  One DmpEvtMCNudMSD is a response of one Nud Block.
*/
public:
  DmpEvtMCNudMSD();
  ~DmpEvtMCNudMSD();
  void  SetSDID(const short &id)    {fSDID = id;}
  void  AddG4Hit(const double &e,const double &t);     // invoke from G4Step or Sensitive Detector
  const short&  GetSDID() const     {return fSDID;}
  const double& GetStartTime() const  {return fMinTime;}
  const double& GetStopTime() const   {return fMaxTime;}
  std::vector<double> GetEnergy() const   {return fEnergy;}

public:
  static void SetDeltaTime(const short &t) {fDeltaTime = t;}

private:
  static short  fDeltaTime;     //! sum energy (position) of all G4Step in fDeltaTime, and puth it into vector

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Nud bar ID. fSDID =  layerID*100 + barID
  std::vector<double>    fEnergy;       // unit MeV
  double    fMinTime;       // unit nanosecond. All G4Step in this SD, which has the minmum time
  double    fMaxTime;       // unit nanosecond. All G4Step in this SD, which has the maxmum time

  ClassDef(DmpEvtMCNudMSD,1)
};

#endif

