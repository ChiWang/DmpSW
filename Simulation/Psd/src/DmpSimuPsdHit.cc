// Description: This class hinerits from  G4VHit. It is used to
// store the MC hit information of the PSD 
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "DmpSimuPsdHit.hh"

G4Allocator<DmpSimuPsdHit> DmpSimuPsdHitAllocator;

DmpSimuPsdHit::DmpSimuPsdHit()
{
  Edep        = 0.; 
  StripNumber = 0;
  nTracks     = 0; 
  nTracksBack = 0;
  SumPosition = 0;
  pos         = G4ThreeVector(0.,0.,0.);
}

DmpSimuPsdHit::~DmpSimuPsdHit()
{;}

DmpSimuPsdHit::DmpSimuPsdHit(const DmpSimuPsdHit& right)
  : G4VHit()
{
  Edep        = right.Edep; 
  StripNumber = right.StripNumber;
  pos         = right.pos;
  nTracks     = right.nTracks;
  SumPosition = right.SumPosition;
  nTracksBack = right.nTracksBack;

}

const DmpSimuPsdHit& DmpSimuPsdHit::operator=(const DmpSimuPsdHit& right)
{
  Edep        = right.Edep; 
  StripNumber = right.StripNumber;
  SumPosition = right.SumPosition;
  pos         = right.pos;
  nTracks     = right.nTracks;
  nTracksBack = right.nTracksBack;

  return *this;
}

int DmpSimuPsdHit::operator==(const DmpSimuPsdHit& right) const
{
   return((Edep==right.Edep)&&(StripNumber==right.StripNumber)&&(SumPosition==right.SumPosition)&&(nTracksBack==right.nTracksBack));
}

void DmpSimuPsdHit::Draw()
{;}

void DmpSimuPsdHit::Print()
{;}











