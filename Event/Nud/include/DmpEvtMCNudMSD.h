/*
 *  $Id: DmpEvtMCNudMSD.h, 2014-05-01 21:18:59 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtNudMSD_H
#define DmpEvtNudMSD_H

#include "TObject.h"

class DmpEvtMCNudMSD : public TObject{
/*
 *  DmpEvtMCNudMSD
 *  
 *  One DmpEvtMCNudMSD is a response of one Nud Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtMCNudMSDs and other sub-dets' hit collection
*/
public:
  DmpEvtMCNudMSD();
  ~DmpEvtMCNudMSD();
  void  SetSDID(const short &id)   {fSDID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  const short&  GetSDID() const    {return fSDID;}
  const double& GetEnergy() const  {return fEnergy;}
  double* GetPosition() {return fPosition;}

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Nud bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  double    fPosition[3];   // unit cm

  ClassDef(DmpEvtMCNudMSD,1)
};

#endif

