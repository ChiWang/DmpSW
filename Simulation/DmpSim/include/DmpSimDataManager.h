/*
 *  $Id: DmpSimDataManager.h, 2014-03-07 00:00:48 chi $
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
  static DmpSimDataManager* GetInstance();
  static void Vanish();
  void BookBranch();            // invoked from BeginOfRunAction()
  void SetOutDataName(std::string name="stamp");     // invoked from BeginOfRunAction()

private:
  DmpSimDataManager();
  ~DmpSimDataManager();
  static DmpSimDataManager  *sInstance;  //!

public:
  DmpEvtSimPrimaryParticle* GetPrimaryParticle() const {return fPrimaryParticle;}
  DmpEventRaw*  GetRawEvent() const     {return fEvtRaw;}
  void UpdatePrimaryParticleInformation(const G4Event*);    // invoked from GeneratePrimaries()
  void UpdateEventHeader(const G4Event*); // invoked from BeginOfEventAction()
  void Digitize();                  // invoked from EndOfEventAction(), before FillEvent()

private:
  DmpEvtSimPrimaryParticle  *fPrimaryParticle;
  DmpEventRaw   *fEvtRaw;

};

#endif

