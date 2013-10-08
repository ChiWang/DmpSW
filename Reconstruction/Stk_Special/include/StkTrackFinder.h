#ifndef StkTrackFinder_h
#define StkTrackFinder_h

#include <TH2.h>
#include "TROOT.h"
#include <iostream>
#include <TMatrixD.h>
#include "TVector3.h"
#include <TObjArray.h>

#include "StkTrack.h"
#include "SpacePoint.h"

class StkClusterFinder;
class EventReader;

class StkTrackFinder {

 private:

 public:
  StkTrackFinder() { init(); }
  virtual ~StkTrackFinder() {
    for (unsigned int i = 0; i < m_stkTracks.size(); ++i) {
      delete m_stkTracks[i]; 
    }
    m_stkTracks.clear();
}

  void init();

  std::vector<StkTrack*>& getTracks() { return m_stkTracks; }

  void setStkClusterFinder(StkClusterFinder* clusterFinder) { m_clusterFinder = clusterFinder; }
  void setEventReader(EventReader* eventReader)             { m_eventReader   = eventReader;   }

  void findTracks();

 private:

  EventReader*      m_eventReader; 
  StkClusterFinder* m_clusterFinder;

  std::vector<StkTrack*>  m_stkTracks;  

};

#endif
