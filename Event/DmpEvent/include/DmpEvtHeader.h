/*
 *  $Id: DmpEvtHeader.h, 2014-03-09 02:01:25 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include <vector>
#include "TObject.h"

#include "DmpCore.h"

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
  void  SetTime(long time)      {fTime = time;}
  long  GetTime() const         {return fTime;}
  void  SetParticlePdgCode(int);
  TParticle* GetParticle() const {return fParticle;}
  void SetRunMode(DmpEDetectorID id, DmpERunMode mode) {fRunModes[int(id)] = mode;}
  DmpERunMode GetRunMode(DmpEDetectorID id) const {return fRunModes[int(id)];}

private:
  long      fEventID;               // valid event count
  long      fTime;                  // Unit msec
  TParticle *fParticle;             // this particle
// *
// *  TODO: just save one value of Run Mode, why ??
// *
  std::vector<DmpERunMode>  fRunModes;

  ClassDef(DmpEvtHeader,1)
};

#endif

