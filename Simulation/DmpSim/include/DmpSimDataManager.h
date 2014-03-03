/*
 *  $Id: DmpSimDataManager.h, 2014-03-03 22:58:21 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpSimDataManager_H
#define DmpSimDataManager_H

//#include "globals.hh"
#include "DmpDataMessenger.hh"
// *
// *  TODO:  book event information for Primary Generation;
// *

class TTree;
class G4Run;
class DmpEvtRaw;
class DmpEvtSimPrimaryParticle;

class DmpSimDataManager{
public:
  static DmpSimDataManager* GetInstance();
  static void Vanish();
  ~DmpSimDataManager();
  void BookFile(const G4Run*);      // invoked from BeginOfRunAcction()
  void SaveFile();                  // invoked from EndOgRunAction()
  void FillEvent(const G4Event*);   // invoked from EndOfEventAction()
  DmpEvtRaw* GetRawEvent() const {return fEvtRaw;};
  DmpEvtSimPrimaryParticle* GetPrimaryParticle() const {return fPrimaryParticle;}
 
private:
  DmpSimDataManager();
  static DmpSimDataManager     *fInstance;  //!

private:
  TTree             *fTree;
  DmpEvtRaw         *fEvtRaw;
  DmpEvtSimPrimaryParticle   *fPrimaryParticle;

};

#endif

