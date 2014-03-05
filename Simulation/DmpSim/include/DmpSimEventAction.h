/*
 *  $Id: DmpSimEventAction.h, 2014-03-04 11:11:31 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/03/2014
*/

#ifndef DmpSimEventAction_H
#define DmpSimEventAction_H

#include "G4UserEventAction.hh"
//#include "globals.hh"

class DmpSimDataManager;
class DmpSimEventAction : public G4UserEventAction{
public:
  DmpSimEventAction();
  ~DmpSimEventAction();
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  
private:
  DmpSimDataManager     *fDataMan;

};

#endif

