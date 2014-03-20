/*
 *  $Id: DmpEvtHeader.h, 2014-03-19 18:09:51 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include "TObject.h"

#include "DmpDetectorID.h"
#include "DmpRunMode.h"

class TParticle;
class DmpEvtHeader : public TObject{
/*
 * DmpEvtHeader
 *
 * Anywhere could use this singleton
 *
*/
public:
  DmpEvtHeader();
  ~DmpEvtHeader();

  void  SetEventID(long id)     {fEventID = id;}
  long  GetEventID() const      {return fEventID;}
  void  SetTime(short id,short v)     {fTime[id] = v;}
  short GetTimeSize() const     {return 8;}
  void  SetParticlePdgCode(int);
  TParticle* GetParticle() const {return fParticle;}
  void SetRunMode(DmpDetector::DmpEDetectorID id, DmpDetector::DmpERunMode mode) {fRunMode[id] = mode;}
  DmpDetector::DmpERunMode GetRunMode(DmpDetector::DmpEDetectorID id) const {return fRunMode[id];}
  void PrintTime()const;

private:
  long      fEventID;               // valid event count
  short     fTime[8];               // 8 bytes from satellite
  /*
   *    fTime[0] = 
   *    fTime[1] = 
   *    fTime[2] = 
   *    fTime[3] = 
   *    fTime[4] = 
   *    fTime[5] = 
   *    fTime[6] = 
   *    fTime[7] = 
   *
   */
  TParticle *fParticle;             // this particle
  DmpDetector::DmpERunMode fRunMode[DmpDetector::gSubDetNo];    // size = gSubDetNo

  ClassDef(DmpEvtHeader,1)
};

#endif

