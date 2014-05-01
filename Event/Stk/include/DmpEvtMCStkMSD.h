/*
 *  $Id: DmpEvtMCStkMSD.h, 2014-04-30 21:16:44 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtMCStkMSD_H
#define DmpEvtMCStkMSD_H

#include "TObject.h"

class DmpEvtMCStkMSD : public TObject{
/*
 *  DmpEvtMCStkMSD
 *  
 *  One DmpEvtMCStkMSD is a response of one Stk Bar.
 *  The class DmpEvtRaw is a collection of DmpEvtMCStkMSDs and other sub-dets' hit collection
*/
public:
  DmpEvtMCStkMSD();
  ~DmpEvtMCStkMSD();
  void  SetSDID(const short &id)   {fSDID = id;}
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  const short&  GetSDID() const    {return fSDID;}
  const double& GetEnergy() const  {return fEnergy;}
  double* GetPosition() {return fPosition;}

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Stk bar ID. fSDID =  layerID*100 + barID
  double    fEnergy;        // unit MeV
  double    fPosition[3];   // unit cm

  ClassDef(DmpEvtMCStkMSD,1)
};

#endif

