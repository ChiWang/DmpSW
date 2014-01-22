#ifndef DmpG4RunManager_h
#define DmpG4RunManager_h 1

#include "G4RunManager.hh"

class DmpG4RunManager : public G4RunManager {

protected:
  virtual void ProcessOneEvent(G4int i_event);

public:
  //static G4RunManager *Instance(G4bool genOnly); 

private:

};

#endif
