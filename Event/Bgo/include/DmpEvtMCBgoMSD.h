/*
 *  $Id: DmpEvtMCBgoMSD.h, 2014-04-30 21:16:44 DAMPE $
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
 *  The class DmpEvtRaw is a collection of DmpEvtMCBgoMSDs and other sub-dets' hit collection
*/
public:
  DmpEvtMCBgoMSD();
  ~DmpEvtMCBgoMSD();
  void  SetSDID(const short &id)   {fSDID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  const short&  GetSDID() const    {return fSDID;}
  const double& GetEnergy() const  {return fEnergy;}
  double* GetPosition() {return fPosition;}

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Bgo bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  double    fPosition[3];   // unit cm

  ClassDef(DmpEvtMCBgoMSD,1)
};

#endif

