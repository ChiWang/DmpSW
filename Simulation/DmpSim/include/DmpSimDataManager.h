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
class G4TouchableHistory;
class DmpEvtSimPrimaryParticle;
class DmpEventRaw;

class DmpSimDataManager : public DmpVDataManager{
public:
  static DmpSimDataManager* GetInstance();
  static void Vanish();
  void SetOutDataName(std::string name = "default"); // invoked from BeginOfRunAction()
  void BookBranch();    // invoked from BeginOfRunAction()

private:
  DmpSimDataManager();
  ~DmpSimDataManager();
  static DmpSimDataManager  *fInstance;  //!

public:
  DmpEvtSimPrimaryParticle* GetPrimaryParticle() const {return fPrimaryParticle;}
  DmpEventRaw*  GetRawEvent() const     {return fEvtRaw;}
  void UpdatePrimaryParticleInformation(const G4Event*);    // invoked from GeneratePrimaries()
  void UpdateEventHeader(const G4Event*); // invoked from BeginOfEventAction()
  void Digitize();                  // invoked from EndOfEventAction(), before FillEvent()
  void FillEvent();                 // invoked from EndOfEventAction()

private:
  DmpEvtSimPrimaryParticle  *fPrimaryParticle;
  DmpEventRaw   *fEvtRaw;

};

#endif

