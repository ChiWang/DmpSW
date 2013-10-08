// Description: This class hinerits from  G4VHit. It is used to
// store the MC hit information of the BGO 
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "DmpSimHitBgo.hh"

G4Allocator<DmpSimHitBgo> DmpSimHitBgoAllocator;

DmpSimHitBgo::DmpSimHitBgo()
{
  EdepCAL = 0.; 
  CALBarNumber = 0;
  CALPlaneNumber = 0;
  IsCALPlane = 0;
  pos = G4ThreeVector(0.,0.,0.);
}

DmpSimHitBgo::~DmpSimHitBgo()
{;}

DmpSimHitBgo::DmpSimHitBgo(const DmpSimHitBgo& right)
  :G4VHit()
{
  EdepCAL = right.EdepCAL; 
  CALBarNumber = right.CALBarNumber;
  CALPlaneNumber = right.CALPlaneNumber;
  IsCALPlane = right.IsCALPlane;
  pos = right.pos;
}

const DmpSimHitBgo& DmpSimHitBgo::operator=(const DmpSimHitBgo& right)
{
  EdepCAL = right.EdepCAL; 
  CALBarNumber = right.CALBarNumber;
  CALPlaneNumber = right.CALPlaneNumber;
  IsCALPlane = right.IsCALPlane;
  pos = right.pos;
  return *this;
}

int DmpSimHitBgo::operator==(const DmpSimHitBgo& right) const
{
  return((EdepCAL==right.EdepCAL)&&(CALBarNumber==right.CALBarNumber)&&(CALPlaneNumber==right.CALPlaneNumber)&&(IsCALPlane==right.IsCALPlane)&& (pos==right.pos));
}

void DmpSimHitBgo::Draw()
{;}

void DmpSimHitBgo::Print()
{;}











