// Description: This class is used to manage the reconstruction of 
// the Silicon-Tungsten Tracker (STK) of DAMPE
//
// Author(s):
//  - creation by X.Wu, 07/09/2013

#include "StkRecManager.h"

#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

#include "EventProcessor.h"
#include "EventReader.h"

#include "StkClusterFinder.h"
#include "StkTrackFinder.h"

void StkRecManager::init(EventReader* evtReader) {
  if (EventProcessor::flag_dumpEvt == -100) std::cout << "In StkRecManager::init() " << std::endl;
  m_eventReader = evtReader;
  m_clusterFinder = new StkClusterFinder();
  m_trackFinder   = new StkTrackFinder();
  m_trackFinder   -> setEventReader(m_eventReader);
  m_trackFinder   -> setStkClusterFinder(m_clusterFinder);
}

void StkRecManager::process() {

  //find clusters
  m_clusterFinder->findCluster(m_eventReader->SiDigit_strip(), m_eventReader->SiDigit_e(), m_eventReader->SiDigit_trackID());
  //plot residuals
  TVector3 vecPrim(m_eventReader->pvpart_px(),m_eventReader->pvpart_py(),m_eventReader->pvpart_pz());
  TVector3 dirPrim = vecPrim.Unit();
  TVector3 posPrim(m_eventReader->pv_x(),m_eventReader->pv_y(),m_eventReader->pv_z());
  m_clusterFinder->plotDelX(posPrim, dirPrim, SiCluster::kPass2);

  //find tracks (to be implemented)
  //m_trackFinder   ->findTracks();

  return;
}
