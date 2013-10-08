#ifndef StkRecManager_h
#define StkRecManager_h

#include <vector>
#include <string>

#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TBranch.h>

class EventReader;
class StkClusterFinder;
class StkTrackFinder;

class StkRecManager {

 public:

  StkRecManager() {}
  virtual ~StkRecManager() {}

  void init(EventReader* evtReader); 
  void process();  

 private:
  EventReader*      m_eventReader; 
  StkClusterFinder* m_clusterFinder;
  StkTrackFinder*   m_trackFinder;

};

#endif
