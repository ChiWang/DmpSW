/*
 *  $Id: DmpSimRunAction.h, 2014-03-04 11:19:22 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/03/2014
*/

#ifndef DmpSimRunAction_H
#define DmpSimRunAction_H

#include "G4UserRunAction.hh"

class DmpSimSvcDataMgr;

class DmpSimRunAction : public G4UserRunAction{
public:
  DmpSimRunAction();
  ~DmpSimRunAction();
  
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
  
public:
  bool Initialize();
  bool Finalize()   {return true;}

private:
  DmpSimSvcDataMgr  *fDataMgr;
};

#endif


