/*
 *  $Id: DmpEvtHeader.h, 2014-03-02 22:20:49 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include <vector>
#include "TObject.h"

class TParticle;
class DmpEvtHeader : public TObject{
/*
 * DmpEvtHeader
 *
 * Anywhere could use this singleton
 *
*/
public:
  enum DmpRunMode{
    kUnknow = -1,
    kCompress = 5,
    kCalPed = 6,
    kCalADC = 7,
  };

public:
  DmpEvtHeader();
  ~DmpEvtHeader();

  void  SetRunID(int id)        {fEventID = id;}
  int   GetRunID() const        {return fEventID;}
  void  SetEventID(long id)     {fEventID = id;}
  long  GetEventID() const      {return fEventID;}
  void  SetTime(long time)      {fTime = time;}
  long  GetTime() const         {return fTime;}
  TParticle* GetParticle() const {return fParticle;}
  void SetRunMode(short SubDet_ID, DmpRunMode mode) {fRunModes[SubDet_ID] = mode;}
  DmpRunMode GetRunMode(short SubDet_ID) const {fRunModes[SubDet_ID] = mode;}

private:
  int       fRunID;                 // Run ID
  long      fEventID;               // valid event count
  long      fTime;                  // Unit msec
  TParticle *fParticle;             // this particle
  std::vector<DmpRunMode>   fRunModes;

  ClassDef(DmpEvtHeader,1)
};

#endif

