#ifndef DMPSIMUPSDHITNTUPLEMAKER_HH
#define DMPSIMUPSDHITNTUPLEMAKER_HH

#include <vector>
#include "globals.hh"

class TTree;
class G4Run;
class G4Event;

class DmpSimuPsdHitNtupleMaker
{
public:
    DmpSimuPsdHitNtupleMaker();
    ~DmpSimuPsdHitNtupleMaker();

    void book(const G4Run* aRun,TTree* aTree);
    void save();

    void beginEvent(const G4Event* evt);
    void FillEvent(const G4Event* evt);

private:
    TTree* tree;
    G4int debugEvent;
    G4int eventNumber;

    int tt_PsdHit_n;
    std::vector<int>*    tt_PsdHit_strip;
    std::vector<int>*    tt_PsdHit_ntracks;
    std::vector<int>*    tt_PsdHit_ntracksBack;
    std::vector<double>* tt_PsdHit_edep;
    std::vector<double>* tt_PsdHit_pos_x;
    std::vector<double>* tt_PsdHit_pos_y;
    std::vector<double>* tt_PsdHit_pos_z;
    std::vector<double>* tt_PsdHit_sumposition;

};

#endif // DMPSIMUPSDHITNTUPLEMAKER_HH
