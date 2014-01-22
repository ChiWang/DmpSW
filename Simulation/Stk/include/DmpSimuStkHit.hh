#ifndef DmpSimuStkHit_h
#define DmpSimuStkHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimuStkHit : public G4VHit
{
public:
  
  DmpSimuStkHit();
  ~DmpSimuStkHit();
  DmpSimuStkHit(const DmpSimuStkHit&);
  const DmpSimuStkHit& operator=(const DmpSimuStkHit&);
  int operator==(const DmpSimuStkHit&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4double EdepSil;      // Energy deposited on the silicon strip
  G4double EdepSilPrim;  // Energy deposited on the silicon strip by e+/e- from conversion
  G4ThreeVector pos; // Position of the hit 
  G4int NStrip;      // Number of the strip
  G4int NSilPlane;   // Number of the plane (0-5)
  G4int NSilBlock;   // Number of the block (0-3)
  G4int IsXPlane;    // Type of the plane (1 X, 0 Y)
  G4int trackID;                // current track ID
  G4int trackID1;               // previous track ID not primary
  unsigned int PrimTrackID;     // primary track ID word
  G4int nTracks;                // number of tracks
  G4int nTracksBack;            // number of back scattering tracks
  G4int nTracksPrim;            // number of primary tracks

public:
  
  inline void AddSil(G4double de)       { EdepSil      += de;};
  inline void AddSilPrim(G4double de)   { EdepSilPrim  += de;};
  inline void SetNStrip(G4int i)        { NStrip = i;   };
  inline void SetNSilPlane(G4int i)     { NSilPlane = i;};
  inline void SetNSilBlock(G4int i)     { NSilBlock = i;};
  inline void SetPlaneType(G4int i)     { IsXPlane = i; };
  inline void SetPos(G4ThreeVector xyz) { pos = xyz;    };
  inline void SetTrackID(G4int i)       { trackID  = i;  };
  inline void SetTrackID1(G4int i)      { trackID1 = i;  };
  inline void SetPrimTrackID(unsigned int i)   { PrimTrackID = i;  };
  inline void SetNtracks(G4int i)       { nTracks = i;      };
  inline void SetNtracksBack(G4int i)   { nTracksBack = i;  };
  inline void SetNtracksPrim(G4int i)   { nTracksPrim = i;  };
  
  inline G4double GetEdepSil()          { return EdepSil;       };
  inline G4double GetEdepSilPrim()      { return EdepSilPrim;   };
  inline G4int    GetNStrip()      { return NStrip;    };
  inline G4int    GetNSilPlane()   { return NSilPlane; };
  inline G4int    GetNSilBlock()   { return NSilBlock; };
  inline G4int    GetPlaneType()   { return IsXPlane;  };      
  inline G4ThreeVector GetPos()    { return pos;       };
  inline G4int    GetTrackID()     { return trackID;   };      
  inline G4int    GetTrackID1()    { return trackID1;  };      
  inline unsigned int    GetPrimTrackID()     { return PrimTrackID;   };      
  inline G4int    GetNtracks()     { return nTracks;       };      
  inline G4int    GetNtracksBack() { return nTracksBack;   };      
  inline G4int    GetNtracksPrim() { return nTracksPrim;   };      
  
};

typedef G4THitsCollection<DmpSimuStkHit> DmpSimuStkHitsCollection;

extern G4Allocator<DmpSimuStkHit> DmpSimuStkHitAllocator;

inline void* DmpSimuStkHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) DmpSimuStkHitAllocator.MallocSingle();
  return aHit;
}

inline void DmpSimuStkHit::operator delete(void* aHit)
{
  DmpSimuStkHitAllocator.FreeSingle((DmpSimuStkHit*) aHit);
}

#endif









