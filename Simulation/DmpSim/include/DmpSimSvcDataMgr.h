/*
 *  $Id: DmpSimSvcDataMgr.h, 2014-04-10 21:08:36 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpSimSvcDataMgr_H
#define DmpSimSvcDataMgr_H

#include "DmpVIOSvc.h"
#include "DmpDetectorID.h"

class G4Event;
class DmpEvtSimPrimaryParticle;
class DmpEvtHeader;
class TClonesArray;

class DmpSimSvcDataMgr : public DmpVIOSvc{
/*
 *  DmpSimSvcDataMgr
 *
 *  
 */
public:
  static DmpSimSvcDataMgr* GetInstance(){
    static DmpSimSvcDataMgr instance;
    return &instance;
  }
  ~DmpSimSvcDataMgr();
  void BookBranch();            // invoked from BeginOfRunAction()

private:
  DmpSimSvcDataMgr();
  void ResetEvent();            // delete all elements in TClonesArray

public:
  DmpEvtHeader* GetEventHeader() const  {return fEvtHeader;}
  TClonesArray* GetOutCollection(DmpDetector::DmpEDetectorID) const;
  DmpEvtSimPrimaryParticle* GetPrimaryParticle() const {return fPrimaryParticle;}
  void UpdatePrimaryParticleInformation(const G4Event*);    // invoked from GeneratePrimaries()
  void Digitize();              // invoked from EndOfEventAction(), before FillEvent()

private:
  DmpEvtSimPrimaryParticle  *fPrimaryParticle;
  DmpEvtHeader  *fEvtHeader;
  TClonesArray  *fPsdOutSet;
  TClonesArray  *fBgoOutSet;
  TClonesArray  *fStkOutSet;
  TClonesArray  *fNudOutSet;
};

//-------------------------------------------------------------------
extern DmpSimSvcDataMgr *gSimDataMgr;

#endif

