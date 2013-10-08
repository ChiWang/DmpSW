// Description: This class hinerits from  G4VHit. It is used to
// store the MC hit information of the PSD 
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "DmpSimHitPsd.hh"

G4Allocator<DmpSimHitPsd> DmpSimHitPsdAllocator;

DmpSimHitPsd::DmpSimHitPsd()
{
  Edep = 0.; 
  StripNumber = 0; 
  pos = G4ThreeVector(0.,0.,0.);
}

DmpSimHitPsd::~DmpSimHitPsd()
{;}

DmpSimHitPsd::DmpSimHitPsd(const DmpSimHitPsd& right)
  : G4VHit()
{
  Edep = right.Edep; 
  StripNumber = right.StripNumber;
  pos = right.pos;
}

const DmpSimHitPsd& DmpSimHitPsd::operator=(const DmpSimHitPsd& right)
{
  Edep = right.Edep; 
  StripNumber = right.StripNumber;
  pos = right.pos;
  return *this;
}

int DmpSimHitPsd::operator==(const DmpSimHitPsd& right) const
{
   return((Edep==right.Edep)&&(StripNumber==right.StripNumber)&&(pos==right.pos));
}

void DmpSimHitPsd::Draw()
{;}

void DmpSimHitPsd::Print()
{;}











