// Description: This class hinerits from  G4VDigi. It is used to
// store the MC digit information of the PSD 
//
// Author(s):
//  - creation by X.Wu, 14/07/2013

#include "DmpSimuPsdDigi.hh"

G4Allocator<DmpSimuPsdDigi> DmpSimuPsdDigiAllocator;

DmpSimuPsdDigi::DmpSimuPsdDigi()
{
  StripNumber = 0;
  Energy      = 0.;

}

DmpSimuPsdDigi::~DmpSimuPsdDigi()
{;}

DmpSimuPsdDigi::DmpSimuPsdDigi(const DmpSimuPsdDigi& right)
  :G4VDigi()
{
  StripNumber  = right.StripNumber;
  Energy      = right.Energy;

}

const DmpSimuPsdDigi& DmpSimuPsdDigi::operator=(const DmpSimuPsdDigi& right)
{
  StripNumber  = right.StripNumber;
  Energy      = right.Energy;
  return *this;
}

int DmpSimuPsdDigi::operator==(const DmpSimuPsdDigi& right) const
{ 
  return ((StripNumber==right.StripNumber)&&(Energy==right.Energy)); 
}

void DmpSimuPsdDigi::Draw()
{;}

void DmpSimuPsdDigi::Print()
{;}












