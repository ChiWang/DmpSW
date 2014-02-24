// Description: This class hinerits from  G4VHit. It is used to
// store the MC hit information of the PSD 
//
// Author(s):
//  - added by Tiekuang Dong 2012/12/23

#include "DmpSimuNudHit.hh"

G4Allocator<DmpSimuNudHit> DmpSimuNudHitAllocator;

DmpSimuNudHit::DmpSimuNudHit()
{
  Edep = 0.; 
 // StripNumber = 0; 
  time = 0.;
  pos = G4ThreeVector(0.,0.,0.);
}

DmpSimuNudHit::~DmpSimuNudHit()
{;}

DmpSimuNudHit::DmpSimuNudHit(const DmpSimuNudHit& right)
  : G4VHit()
{
  Edep = right.Edep; 
//  StripNumber = right.StripNumber;
  time = right.time;
  pos = right.pos;
}

const DmpSimuNudHit& DmpSimuNudHit::operator=(const DmpSimuNudHit& right)
{
  Edep = right.Edep; 
 // StripNumber = right.StripNumber;
  time = right.time;
  pos = right.pos;
  return *this;
}

int DmpSimuNudHit::operator==(const DmpSimuNudHit& right) const
{
   return((Edep==right.Edep)&&(time==right.time)&&(pos==right.pos));
}

void DmpSimuNudHit::Draw()
{;}

void DmpSimuNudHit::Print()
{;}











