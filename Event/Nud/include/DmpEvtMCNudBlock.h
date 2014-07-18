/*
 *  $Id: DmpEvtMCNudBlock.h, 2014-07-18 22:13:03 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
 *    Yang LIU (liuy@ustc.edu) 05/05/2014
*/

#ifndef DmpEvtNudBlock_H
#define DmpEvtNudBlock_H

#include "TObject.h"

class DmpEvtMCNudBlock : public TObject{
/*
 *  DmpEvtMCNudBlock
 *  
 *  One DmpEvtMCNudBlock is a response of one Nud Block.
*/
public:
  DmpEvtMCNudBlock();
  ~DmpEvtMCNudBlock();
  void  SetGlobalBlockID(const short &id)    {fGlobalBlockID = id;}
  void  AddG4Hit(const double &e,const double &t);     // invoke from G4Step or Sensitive Detector
  const short&  GetGlobalBlockID() const     {return fGlobalBlockID;}
  const double& GetStartTime() const  {return fMinTime;}
  const double& GetStopTime() const   {return fMaxTime;}
  std::vector<double> GetEnergy() const   {return fEnergy;}

public:
  static void SetDeltaTime(const short &t) {fDeltaTime = t;}
  static short GetDeltaTime() {return fDeltaTime;}

private:
  static short  fDeltaTime;     //! sum energy (position) of all G4Step in fDeltaTime, and puth it into vector

private:
  short     fGlobalBlockID; // unique sensitive detector(minimum detector unit) ID. Nud block ID. fGlobalBlockID =  layerID*100 + blockID
  std::vector<double>    fEnergy;       // unit MeV
  double    fMinTime;       // unit nanosecond. All G4Step in this SD, which has the minmum time
  double    fMaxTime;       // unit nanosecond. All G4Step in this SD, which has the maxmum time

  ClassDef(DmpEvtMCNudBlock,1)
};

#endif

