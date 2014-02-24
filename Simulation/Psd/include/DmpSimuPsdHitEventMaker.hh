#ifndef DMPSIMUPSDHITEVENTMAKER_HH
#define DMPSIMUPSDHITEVENTMAKER_HH

#include <vector>
#include "globals.hh"

#include "DmpEvtPsdHit.hh"

class TTree;
class G4Run;
class G4Event;

class DmpSimuPsdHitEventMaker
{
public:
    DmpSimuPsdHitEventMaker();
    ~DmpSimuPsdHitEventMaker();

    void book(const G4Run* aRun,TTree* aTree);
    void save();

    void beginEvent(const G4Event* evt);
    void FillEvent(const G4Event* evt);

private:
    TTree* tree;
    G4int debugEvent;
    G4int eventNumber;

    DmpEvtPsdHit* PsdHitEvt;
};

#endif
