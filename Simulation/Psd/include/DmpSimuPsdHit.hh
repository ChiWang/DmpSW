#ifndef DmpSimuPsdHit_h
#define DmpSimuPsdHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimuPsdHit : public G4VHit
{
public:
  
  DmpSimuPsdHit();
  ~DmpSimuPsdHit();
  DmpSimuPsdHit(const DmpSimuPsdHit&);
  const DmpSimuPsdHit& operator=(const DmpSimuPsdHit&);
  int operator==(const DmpSimuPsdHit&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4double Edep;         // Energy deposited
  G4ThreeVector pos;     // Position of the hit
  G4double SumPosition;  // Sum of Energy*position
  G4int StripNumber;     // Number of the strip
  G4int nTracksBack;     // number of back scattering tracks
  G4int nTracks;         // number of tracks

  G4int trackID;         // current track ID

public:
  
  inline void AddEnergy(G4double de)      { Edep += de;        };
  inline void SetStripNumber(G4int i)     { StripNumber = i;   };
  inline void SetPos(G4ThreeVector xyz)   { pos = xyz;         };
  inline void AddSumPosition(G4double de) { SumPosition += de; };
  inline void SetNtracksBack(G4int i)     { nTracksBack = i;   };
  inline void SetNtracks(G4int i)         { nTracks = i;       };
  inline void SetTrackID(G4int i)         { trackID = i;       };

  
  inline G4double GetEdep()          { return Edep;        };
  inline G4int    GetStripNumber()   { return StripNumber; };
  inline G4ThreeVector GetPos()      { return pos;         };
  inline G4double GetSumPosition()   { return SumPosition; };
  inline G4int    GetNtracks()       { return nTracks;     };      
  inline G4int    GetNtracksBack()   { return nTracksBack; };      
  inline G4int    GetTrackID()       { return trackID;     };      
  
};

typedef G4THitsCollection<DmpSimuPsdHit> DmpSimuPsdHitsCollection;

extern G4Allocator<DmpSimuPsdHit> DmpSimuPsdHitAllocator;

inline void* DmpSimuPsdHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) DmpSimuPsdHitAllocator.MallocSingle();
  return aHit;
}

inline void DmpSimuPsdHit::operator delete(void* aHit)
{
  DmpSimuPsdHitAllocator.FreeSingle((DmpSimuPsdHit*) aHit);
}

#endif










