// Description: This class hinerits from  G4VDigi. It is used to
// store the MC digit information of the BGO 
//
// Author(s):
//  - creation by X.Wu, 14/07/2013

#include "DmpSimDigBgo.hh"

G4Allocator<DmpSimDigBgo> DmpSimDigBgoAllocator;

DmpSimDigBgo::DmpSimDigBgo()
{
  BarNumber   = 0;
  Energy      = 0.;

}

DmpSimDigBgo::~DmpSimDigBgo()
{;}

DmpSimDigBgo::DmpSimDigBgo(const DmpSimDigBgo& right)
  :G4VDigi()
{
  BarNumber   = right.BarNumber;
  Energy      = right.Energy;

}

const DmpSimDigBgo& DmpSimDigBgo::operator=(const DmpSimDigBgo& right)
{
  BarNumber  = right.BarNumber;
  Energy      = right.Energy;
  return *this;
}

int DmpSimDigBgo::operator==(const DmpSimDigBgo& right) const
{ 
  return ((BarNumber==right.BarNumber)&&(Energy==right.Energy)); 
}

void DmpSimDigBgo::Draw()
{;}

void DmpSimDigBgo::Print()
{;}












