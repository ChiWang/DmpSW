/*
 *  $Id: DmpEvtMCNudMSD.h, 2014-05-06 10:25:45 DAMPE $
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
  void  SetSDID(const short &id)    {fSDID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  void  SetStartTime(const long &t) {fTimeFirstStep = t;}
  void  SetStopTime(const long &t)  {fTimeLastStep = t;}
  const short&  GetSDID() const     {return fSDID;}
  const double& GetEnergy() const   {return fEnergy;}
  double* GetPosition() {return fPosition;}
  const long& GetStartTime() const  {return fTimeFirstStep;}
  const long& GetStopTime() const   {return fTimeLastStep;}

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Nud bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  double    fPosition[3];   // unit cm
  long      fTimeFirstStep; // unit millisecond. Time of the first G4Step in this SD
  long      fTimeLastStep;  // unit millisecond. Time of the last G4Step in this SD

  ClassDef(DmpEvtMCNudMSD,1)
};

#endif

