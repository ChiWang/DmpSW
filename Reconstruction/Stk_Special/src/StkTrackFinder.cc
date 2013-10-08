// Description: This class implements the cluster finding 
// algorithm of the Silicon-Tungsten Tracker (STK) of DAMPE
//
// Author(s):
//  - creation by X.Wu, 07/09/2013

#include "StkTrackFinder.h"

#include <map>
#include "TMath.h"
#include <iostream>
#include "StkTrack.h"
#include "StkParamDef.h"

#include "EventProcessor.h"

void StkTrackFinder::init() {
  if (EventProcessor::flag_dumpEvt == -100) std::cout << "In StkTrackFinder::init() " << std::endl;
  m_stkTracks.clear();

  return;
}

void StkTrackFinder::findTracks() {
  if (EventProcessor::flag_dumpEvt == -100) std::cout << "In StkTrackFinder::findTracks() " << std::endl;
  //clear the track collection
  m_stkTracks.clear();
  std::cout << "!!!!!!!! StkTrackFinder: track finding to be implemented !!!!!!!! " << std::endl;

  return;
}

