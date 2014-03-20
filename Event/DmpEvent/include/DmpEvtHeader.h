/*
 *  $Id: DmpEvtHeader.h, 2014-03-20 19:42:44 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include "TObject.h"

#include "DmpDetectorID.h"
#include "DmpRunMode.h"

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
  void  PrintTime() const;
  void  SetParticlePdgCode(const int &i)    {fPdgCode = i;}
  int   GetParticlePdgCode() const {return fPdgCode;}
  void  SetTrigger(const DmpDetector::DmpEDetectorID&, const short&);
  short GetTrigger(const DmpDetector::DmpEDetectorID&) const ;
  bool  TriggerMatch() const  {return (fTrgBgo==fTrgPsd && fTrgBgo==fTrgStk && fTrgBgo==fTrgNud);}
  void  SetRunMode(const DmpDetector::DmpEDetectorID&, const short&);
  DmpDetector::DmpERunMode GetRunMode(const DmpDetector::DmpEDetectorID&) const;

private:
  long      fEventID;       // valid event count
  short     fTime[8];       // 8 bytes from satellite
  /*
   *    fTime[0~1] = 
   *    fTime[2~4] = 
   *    fTime[5~7] = 
   *
   */
  int       fPdgCode;       // particle pdg code
  short     fTrgPsd;        // trigger Psd
  short     fTrgStk;        // trigger Stk
  short     fTrgBgo;        // trigger Bgo
  short     fTrgNud;        // trigger Nud
  DmpDetector::DmpERunMode fModePsd;    // Psd run mode
  DmpDetector::DmpERunMode fModeStk;    // Stk run mode
  DmpDetector::DmpERunMode fModeBgo;    // Bgo run mode
// *
// *  TODO: confirm mode of Stk, Nud
// *
  DmpDetector::DmpERunMode fModeNud;    // Need? Nud run mode

  ClassDef(DmpEvtHeader,1)
};

#endif

