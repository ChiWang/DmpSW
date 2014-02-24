// Description: This class hinerits from  G4VDigi. It is used to
// store the MC digit information of the STK 
//
// Author(s):
//  - creation by X.Wu, 12/07/2013

#include "DmpSimuStkDigi.hh"

G4Allocator<DmpSimuStkDigi> DmpSimuStkDigiAllocator;

DmpSimuStkDigi::DmpSimuStkDigi()
{
  PlaneType   = 0; 
  PlaneNumber = 0;
  StripNumber = 0;
  DigiType    = 0;
  Energy      = 0.;
  EnergyPrim  = 0.;
  PrimTrackID = 0;
  hitID       = -1;               // current hit ID
  hitID1      = -1;               // previous hit ID 
  hitID2      = -1;               // previous hit ID 
  nTracks     = 0;                // number of tracks
  nTracksBack = 0;                // number of back scattering tracks
  nTracksPrim = 0;                // number of primary tracks
  nHits       = 0;                // number of hits
  nHitsBack   = 0;                // number of back scattering hits

}

DmpSimuStkDigi::~DmpSimuStkDigi()
{;}

DmpSimuStkDigi::DmpSimuStkDigi(const DmpSimuStkDigi& right)
  :G4VDigi()
{
  PlaneType   = right.PlaneType; 
  PlaneNumber = right.PlaneNumber;
  StripNumber = right.StripNumber;
  DigiType    = right.DigiType;
  Energy      = right.Energy;
  EnergyPrim  = right.EnergyPrim;
  PrimTrackID = right.PrimTrackID;
  hitID       = right.hitID;         
  hitID1      = right.hitID1;        
  hitID2      = right.hitID2;        
  nTracks     = right.nTracks;          
  nTracksBack = right.nTracksBack;      
  nTracksPrim = right.nTracksPrim;          
  nHits       = right.nHits;            
  nHitsBack   = right.nHitsBack;        

}

const DmpSimuStkDigi& DmpSimuStkDigi::operator=(const DmpSimuStkDigi& right)
{
  PlaneType   = right.PlaneType; 
  PlaneNumber = right.PlaneNumber;
  StripNumber = right.StripNumber;
  DigiType    = right.DigiType;
  Energy      = right.Energy;
  EnergyPrim  = right.EnergyPrim;
  PrimTrackID = right.PrimTrackID;
  hitID     = right.hitID;         
  hitID1    = right.hitID1;        
  nTracks     = right.nTracks;          
  nTracksBack = right.nTracksBack;      
  nTracksPrim = right.nTracksPrim;          
  nHits       = right.nHits;            
  nHitsBack   = right.nHitsBack;        
  return *this;
}

int DmpSimuStkDigi::operator==(const DmpSimuStkDigi& right) const
{ 
  return ((PlaneType==right.PlaneType)&&(PlaneNumber==right.PlaneNumber)&&(StripNumber==right.StripNumber)&&(DigiType==right.DigiType)&&(Energy==right.Energy)&&(EnergyPrim==right.EnergyPrim)&&(PrimTrackID==right.PrimTrackID)&&(hitID==right.hitID)&&(hitID1==right.hitID1)&&(hitID2==right.hitID2)&&(nTracks==right.nTracks)&&(nTracksBack==right.nTracksBack)&&(nTracksPrim==right.nTracksPrim)&&(nHits==right.nHits)&&(nHitsBack==right.nHitsBack)); 
}

void DmpSimuStkDigi::Draw()
{;}

void DmpSimuStkDigi::Print()
{;}












