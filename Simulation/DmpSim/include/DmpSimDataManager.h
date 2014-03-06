/*
 *  $Id: DmpSimDataManager.h, 2014-03-06 17:03:59 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpSimDataManager_H
#define DmpSimDataManager_H

#include "DmpVDataManager.h"

class TTree;
class G4Run;
class G4Event;
class G4TouchableHistory;
class DmpEvtSimPrimaryParticle;

class DmpSimDataManager : public DmpVDataManager{
public:
  static DmpSimDataManager* GetInstance();
  static void Vanish();
  ~DmpSimDataManager();
public:
  DmpEvtSimPrimaryParticle* GetPrimaryParticle() const {return fPrimaryParticle;}
  void BookFile(const G4Run*);      // invoked from BeginOfRunAcction()
  void SaveFile();                  // invoked from EndOgRunAction()
  void UpdatePrimaryParticleInformation(const G4Event*);    // invoked from GeneratePrimaries()
  void UpdateEventHeader(const G4Event*); // invoked from BeginOfEventAction()
  void Digitize();                  // invoked from EndOfEventAction(), before FillEvent()
  void FillEvent();                 // invoked from EndOfEventAction()

private:
  DmpSimDataManager();
  static DmpSimDataManager  *fInstance;  //!

private:
  TTree                     *fTree;
  DmpEvtSimPrimaryParticle  *fPrimaryParticle;

};

#endif

