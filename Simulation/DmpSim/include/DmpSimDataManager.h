/*
 *  $Id: DmpSimDataManager.h, 2014-02-25 16:32:41 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpDataManager_H
#define DmpDataManager_H

#include "globals.hh"

#include "DmpDataMessenger.hh"

class TTree;
class G4Run;
class DmpEvtRaw;
class DmpEvtSimPrimaryParticle;

// *
// *  TODO:  for Primary Generation;
// *

class DmpDataManager{
public:
  static DmpDataManager* GetInstance();
  static void Clear();
  ~DmpDataManager();
  void BookFile(const G4Run*);      // invoked from BeginOfRunAcction()
  void SaveFile();                  // invoked from EndOgRunAction()
  void FillEvent(const G4Event*);   // invoked from EndOfEventAction()
 
private:
  DmpDataManager();
  static DmpDataManager     *fInstance;  //!

private:
  TTree             *fTree;
  DmpEvtRaw         *fEvtRaw;
  DmpEvtSimPrimaryParticle   *fPrimaryParticle;

};

#endif

