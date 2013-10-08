// Description: This class hinerits from  G4VDigi. It is used to
// store the MC digit information of the PSD 
//
// Author(s):
//  - creation by X.Wu, 14/07/2013

#include "DmpSimDigPsd.hh"

G4Allocator<DmpSimDigPsd> DmpSimDigPsdAllocator;

DmpSimDigPsd::DmpSimDigPsd()
{
  StripNumber = 0;
  Energy      = 0.;

}

DmpSimDigPsd::~DmpSimDigPsd()
{;}

DmpSimDigPsd::DmpSimDigPsd(const DmpSimDigPsd& right)
  :G4VDigi()
{
  StripNumber  = right.StripNumber;
  Energy      = right.Energy;

}

const DmpSimDigPsd& DmpSimDigPsd::operator=(const DmpSimDigPsd& right)
{
  StripNumber  = right.StripNumber;
  Energy      = right.Energy;
  return *this;
}

int DmpSimDigPsd::operator==(const DmpSimDigPsd& right) const
{ 
  return ((StripNumber==right.StripNumber)&&(Energy==right.Energy)); 
}

void DmpSimDigPsd::Draw()
{;}

void DmpSimDigPsd::Print()
{;}












