#include "StkTrack.h"

#include "TMath.h"

StkTrack::StkTrack()
{
  m_seedType = kUndefined;
  m_trackParams = StkTrackParams();
  m_nGapX = 0;
  m_nGapY = 0;
  m_nHitX = 0;
  m_nHitY = 0;
  m_chi2tot = 0.;
}
