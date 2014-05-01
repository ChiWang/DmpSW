/*
 *  $Id: DmpSimSvcDataMgr.h, 2014-04-12 17:07:59 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpSimSvcDataMgr_H
#define DmpSimSvcDataMgr_H

#include "DmpVDataMgr.h"
#include "DmpVSvc.h"

class G4Event;
class DmpEvtMCPrimaryParticle;
class TClonesArray;

class DmpSimSvcDataMgr : public DmpVSvc, public DmpVDataMgr{
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
  void ResetEvent();            // delete all elements in TClonesArray

public:
  TClonesArray* GetOutCollection(DmpDetector::DmpEDetectorID) const;
  DmpEvtMCPrimaryParticle* GetPrimaryParticle() const {return fPrimaryParticle;}
  void Digitize();              // invoked from EndOfEventAction(), before FillEvent()

private:
  DmpEvtMCPrimaryParticle  *fPrimaryParticle;
  TClonesArray  *fPsdOutSet;
  TClonesArray  *fBgoOutSet;
  TClonesArray  *fStkOutSet;
  TClonesArray  *fNudOutSet;
};

#endif

