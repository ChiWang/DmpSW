/*
 *  $Id: DmpSimDataManager.h, 2014-03-04 10:18:30 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpSimDataManager_H
#define DmpSimDataManager_H

#include "DmpSubDetectors.h"
// *
// *  TODO:  book event information for Primary Generation;
// *

class TClonesArray;
class TTree;
class G4Run;
class G4Event;
class G4TouchableHistory;
class DmpEvtHeader;
class DmpEvtSimPrimaryParticle;
class DmpEventRaw;

class DmpSimDataManager{
public:
  static DmpSimDataManager* GetInstance();
  static void Vanish();
  ~DmpSimDataManager();
public:
  void BookFile(const G4Run*);      // invoked from BeginOfRunAcction()
  void SaveFile();                  // invoked from EndOgRunAction()
  void UpdatePrimaryParticleInformation(const G4Event*);    // invoked from GeneratePrimaries()
  void UpdateEventHeader(const G4Event*); // invoked from BeginOfEventAction()
  void Digitize();                  // invoked from EndOfEventAction(), before FillEvent()
  void FillEvent();                 // invoked from EndOfEventAction()
public:
  DmpEvtHeader* GetEventHeader() const;     // DmpSimDataManager is a friend class of DmpEventRaw
  TClonesArray* GetHitCollection(DmpParameters::DmpSubDetectors SubDet_ID) const;
  DmpEvtSimPrimaryParticle* GetPrimaryParticle() const {return fPrimaryParticle;}
 
private:
  DmpSimDataManager();
  static DmpSimDataManager  *fInstance;  //!

private:
  TTree                     *fTree;
  DmpEvtSimPrimaryParticle  *fPrimaryParticle;
  DmpEventRaw               *fEvtRaw;

};

#endif

