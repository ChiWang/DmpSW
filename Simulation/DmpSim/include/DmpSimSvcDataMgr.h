/*
 *  $Id: DmpSimSvcDataMgr.h, 2014-04-12 17:07:59 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpSimSvcDataMgr_H
#define DmpSimSvcDataMgr_H

#include "DmpVSvcDataMgr.h"
#include "DmpVSvc.h"

class G4Event;
class DmpEvtSimPrimaryParticle;
class DmpEvtHeader;
class TClonesArray;

class DmpSimSvcDataMgr : public DmpVSvcDataMgr{
/*
 *  DmpSimSvcDataMgr
 *
 *  
 */
public:
  DmpSimSvcDataMgr();
  ~DmpSimSvcDataMgr();
  bool Initialize() {return true;}
  bool Finalize()   {return true;}
  void Set(const std::string&, const std::string&);
  void BookBranch();            // invoked from BeginOfRunAction()

private:
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

#endif

