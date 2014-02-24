// Description: This class hinerits from  G4VHit. It is used to
// store the MC hit information of the BGO 
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "DmpSimuBgoHit.hh"

G4Allocator<DmpSimuBgoHit> DmpSimuBgoHitAllocator;

DmpSimuBgoHit::DmpSimuBgoHit()
{
  EdepNeg = 0.;
  EdepPos = 0.;
  SumPosition = 0.;
  EdepCAL = 0.; 
  CALBarNumber = 0;
  CALLayerNumber = 0;
  IsCALLayer = 0;
  pos = G4ThreeVector(0.,0.,0.);
}

DmpSimuBgoHit::~DmpSimuBgoHit()
{;}

DmpSimuBgoHit::DmpSimuBgoHit(const DmpSimuBgoHit& right)
  :G4VHit()
{
  EdepNeg = right.EdepNeg; 
  EdepPos = right.EdepPos; 
  SumPosition = right.SumPosition;
  EdepCAL = right.EdepCAL; 
  CALBarNumber = right.CALBarNumber;
  CALLayerNumber = right.CALLayerNumber;
  IsCALLayer = right.IsCALLayer;
  pos = right.pos;
}

const DmpSimuBgoHit& DmpSimuBgoHit::operator=(const DmpSimuBgoHit& right)
{
  EdepNeg = right.EdepNeg; 
  EdepPos = right.EdepPos; 
  SumPosition = right.SumPosition;
  EdepCAL = right.EdepCAL; 
  CALBarNumber = right.CALBarNumber;
  CALLayerNumber = right.CALLayerNumber;
  IsCALLayer = right.IsCALLayer;
  pos = right.pos;
  return *this;
}

int DmpSimuBgoHit::operator==(const DmpSimuBgoHit& right) const
{
  return((EdepNeg==right.EdepNeg)&&(EdepPos==right.EdepPos)&&(SumPosition==right.SumPosition)&&(EdepCAL==right.EdepCAL)&&(CALBarNumber==right.CALBarNumber)&&(CALLayerNumber==right.CALLayerNumber)&&(IsCALLayer==right.IsCALLayer)&& (pos==right.pos));
}

void DmpSimuBgoHit::Draw()
{;}

void DmpSimuBgoHit::Print()
{;}











