// Description: This class hinerits from  G4VDigi. It is used to
// store the MC digit information of the BGO 
//
// Author(s):
//  - creation by X.Wu, 14/07/2013

#include "DmpSimuBgoDigi.hh"

G4Allocator<DmpSimuBgoDigi> DmpSimuBgoDigiAllocator;

DmpSimuBgoDigi::DmpSimuBgoDigi()
{
  BarNumber   = 0;
  Energy      = 0.;

}

DmpSimuBgoDigi::~DmpSimuBgoDigi()
{;}

DmpSimuBgoDigi::DmpSimuBgoDigi(const DmpSimuBgoDigi& right)
  :G4VDigi()
{
  BarNumber   = right.BarNumber;
  Energy      = right.Energy;

}

const DmpSimuBgoDigi& DmpSimuBgoDigi::operator=(const DmpSimuBgoDigi& right)
{
  BarNumber  = right.BarNumber;
  Energy      = right.Energy;
  return *this;
}

int DmpSimuBgoDigi::operator==(const DmpSimuBgoDigi& right) const
{ 
  return ((BarNumber==right.BarNumber)&&(Energy==right.Energy)); 
}

void DmpSimuBgoDigi::Draw()
{;}

void DmpSimuBgoDigi::Print()
{;}












