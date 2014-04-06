/*
 *  $Id: DmpSimDataManager.h, 2014-04-06 17:16:01 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpSimDataManager_H
#define DmpSimDataManager_H

#include "DmpVIOSvc.h"
#include "DmpDetectorID.h"

class G4Event;
class DmpEvtSimPrimaryParticle;
class DmpEvtHeader;
class TClonesArray;

class DmpSimDataManager : public DmpVIOSvc{
/*
 *  DmpSimDataManager
 *
 *  
 */
public:
  static DmpSimDataManager* GetInstance(){
    static DmpSimDataManager instance;
    return &instance;
  }
  ~DmpSimDataManager();
  bool Initialize();            // invoked from BeginOfrunAction()
  void BookBranch();            // invoked from BeginOfRunAction()

private:
  DmpSimDataManager();
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
extern DmpSimDataManager *gDataMgr;

#endif

