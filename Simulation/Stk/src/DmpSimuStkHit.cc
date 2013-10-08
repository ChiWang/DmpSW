// Description: This class hinerits from  G4VHit. It is used to
// store the MC hit information of the STK 
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "DmpSimuStkHit.hh"

G4Allocator<DmpSimuStkHit> DmpSimuStkHitAllocator;

DmpSimuStkHit::DmpSimuStkHit()
{
  EdepSil = 0.; 
  EdepSilPrim = 0.; 
  NStrip = 0; NSilPlane = 0; IsXPlane = 0;
  trackID = 0; trackID1 = 0; PrimTrackID = 0;
  nTracks = 0;
  nTracksBack = 0;
  nTracksPrim = 0;
  pos = G4ThreeVector(0.,0.,0.);
}

DmpSimuStkHit::~DmpSimuStkHit()
{;}

DmpSimuStkHit::DmpSimuStkHit(const DmpSimuStkHit& right)
  :G4VHit()
{
  EdepSil     = right.EdepSil; 
  EdepSilPrim = right.EdepSilPrim; 
  NStrip = right.NStrip; NSilPlane = right.NSilPlane;
  trackID = right.trackID; PrimTrackID = right.PrimTrackID;
  nTracks = right.nTracks;
  IsXPlane = right.IsXPlane;
  pos = right.pos;
}

const DmpSimuStkHit& DmpSimuStkHit::operator=(const DmpSimuStkHit& right)
{
  EdepSil     = right.EdepSil; 
  EdepSilPrim = right.EdepSilPrim; 
  NStrip = right.NStrip; NSilPlane = right.NSilPlane;
  trackID = right.trackID; PrimTrackID = right.PrimTrackID;
  nTracks = right.nTracks;
  IsXPlane = right.IsXPlane;
  pos =right.pos;
  return *this;
}

int DmpSimuStkHit::operator==(const DmpSimuStkHit& right) const
{
  return((EdepSil==right.EdepSil)&&(NStrip==right.NStrip)&&(IsXPlane==right.IsXPlane)&& (pos==right.pos) &&
	 (EdepSilPrim==right.EdepSilPrim)&&(trackID==right.trackID)&&(PrimTrackID==right.PrimTrackID)&&(nTracks==right.nTracks));
}

void DmpSimuStkHit::Draw()
{;}

void DmpSimuStkHit::Print()
{;}












