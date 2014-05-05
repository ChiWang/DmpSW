/*
 *  $Id: DmpEvtMCNudMSD.h, 2014-05-05 14:42:42 DAMPE $
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
 *  One DmpEvtMCNudMSD is a response of one Nud Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtMCNudMSDs and other sub-dets' hit collection
*/
public:
  DmpEvtMCNudMSD();
  ~DmpEvtMCNudMSD();
  void  SetSDID(const short &id)   {fSDID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  void  SetTime(const long&) 
  const short&  GetSDID() const    {return fSDID;}
  const double& GetEnergy() const  {return fEnergy;}
  double* GetPosition() {return fPosition;}
  long GetTime(const short &i=0) const {return fTime[i];}

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Nud bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  double    fPosition[3];   // unit cm
  long      fTime[2];       // milliscond

  ClassDef(DmpEvtMCNudMSD,1)
};

#endif

