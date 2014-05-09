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
  void  AddG4Hit(const double &e,const double &x,const double &y,const double &z);     // invoke from G4Step or Sensitive Detector
  void  SetStartTime(const long &t) {fTimeFirstStep = t;}
  void  SetStopTime(const long &t)  {fTimeLastStep = t;}
  const short&  GetSDID() const     {return fSDID;}
  const long& GetStartTime() const  {return fTimeFirstStep;}
  const long& GetStopTime() const   {return fTimeLastStep;}
  std::vector<double> GetEnergy() const   {return fEnergy;}
  std::vector<double> GetPosition(const std::string&) const;

public:
  static void SetDeltaTime(const short &t) {fDeltaTime = t;}

private:
  static short     fDeltaTime;     //! sum energy (position) of all G4Step in fDeltaTime, and puth it into vector

private:
  short     fSDID;          // unique sensitive detector(minimum detector unit) ID. Nud bar ID. fSDID =  layerID*100 + barID
  std::vector<double>    fEnergy;       // unit MeV
  std::vector<double>    fPositionX;    // unit mm
  std::vector<double>    fPositionY;    // unit mm
  std::vector<double>    fPositionZ;    // unit mm
  long      fTimeFirstStep; // unit nanosecond. Time of the first G4Step in this SD
  long      fTimeLastStep;  // unit nanosecond. Time of the last G4Step in this SD

  ClassDef(DmpEvtMCNudMSD,1)
};

#endif

