/*
 *  $Id: DmpSimDataManager.h, 2014-04-04 17:22:52 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpSimDataManager_H
#define DmpSimDataManager_H

#include "DmpVDataManager.h"

class G4Run;
class G4Event;
class DmpEvtSimPrimaryParticle;
class DmpEventRaw;

class DmpSimDataManager : public DmpVDataManager{
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
  void Initialize();
  void BookBranch();            // invoked from BeginOfRunAction()

private:
  DmpSimDataManager();
  ~DmpSimDataManager();

public:
  DmpEvtSimPrimaryParticle* GetPrimaryParticle() const {return fPrimaryParticle;}
  DmpEventRaw*  GetRawEvent() const     {return fEvtRaw;}
  void UpdatePrimaryParticleInformation(const G4Event*);    // invoked from GeneratePrimaries()
  void Digitize();                  // invoked from EndOfEventAction(), before FillEvent()

private:
  DmpEvtSimPrimaryParticle  *fPrimaryParticle;
  DmpEventRaw   *fEvtRaw;
};

extern DmpSimDataManager *gDataMgr;

#endif

