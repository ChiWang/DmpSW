// Description: This class hinerits from  G4VDigi. It is used to
// store the MC digit information of the PSD 
//
// Author(s):
//  - added by Tiekuang Dong 2012/12/23

#include "DmpSimuNudDigi.hh"

G4Allocator<DmpSimuNudDigi> DmpSimuNudDigiAllocator;

DmpSimuNudDigi::DmpSimuNudDigi()
{
 // StripNumber = 0;
  Energy      = 0.;

}

DmpSimuNudDigi::~DmpSimuNudDigi()
{;}

DmpSimuNudDigi::DmpSimuNudDigi(const DmpSimuNudDigi& right)
  :G4VDigi()
{
//  StripNumber  = right.StripNumber;
  Energy      = right.Energy;

}

const DmpSimuNudDigi& DmpSimuNudDigi::operator=(const DmpSimuNudDigi& right)
{
 // StripNumber  = right.StripNumber;
  Energy      = right.Energy;
  return *this;
}

int DmpSimuNudDigi::operator==(const DmpSimuNudDigi& right) const
{ 
  return Energy==right.Energy; 
}

void DmpSimuNudDigi::Draw()
{;}

void DmpSimuNudDigi::Print()
{;}












