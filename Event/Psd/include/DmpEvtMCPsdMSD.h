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
 *  One DmpEvtMCPsdMSD is a response of one Psd Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtMCPsdMSDs and other sub-dets' hit collection
*/
public:
  DmpEvtMCPsdMSD();
  ~DmpEvtMCPsdMSD();
  void  SetSDID(const short &id)   {fSDID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  const short&  GetSDID() const    {return fSDID;}
  const double& GetEnergy() const  {return fEnergy;}
  double* GetPosition() {return fPosition;}

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Psd bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  double    fPosition[3];   // unit mm

  ClassDef(DmpEvtMCPsdMSD,1)
};

#endif

