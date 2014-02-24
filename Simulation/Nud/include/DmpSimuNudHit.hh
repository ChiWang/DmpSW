#ifndef DmpSimuNudHit_h
#define DmpSimuNudHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimuNudHit : public G4VHit
{
public:
  
  DmpSimuNudHit();
  ~DmpSimuNudHit();
  DmpSimuNudHit(const DmpSimuNudHit&);
  const DmpSimuNudHit& operator=(const DmpSimuNudHit&);
  int operator==(const DmpSimuNudHit&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4double     Edep;  // Energy deposited
  G4ThreeVector pos;  // Position of the hit
   G4double  time;  // Time of the hit
 //G4int StripNumber;  // Number of the strip

public:
  
  inline void AddEnergy(G4double de)      {Edep += de;};
  //inline void SetStripNumber(G4int i)     {StripNumber = i;};
  inline void SetTime(G4double t)     {time = t;}; // only record the time of the first hit
  inline void SetPos(G4ThreeVector xyz)   { pos = xyz; }
  
  inline G4double GetEdep()          { return Edep; };
 // inline G4int    GetStripNumber()   { return StripNumber; };
  inline G4double    GetTime()   { return time; };
  inline G4ThreeVector GetPos()      { return pos; };
  
};

typedef G4THitsCollection<DmpSimuNudHit> DmpSimuNudHitsCollection;

extern G4Allocator<DmpSimuNudHit> DmpSimuNudHitAllocator;

inline void* DmpSimuNudHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) DmpSimuNudHitAllocator.MallocSingle();
  return aHit;
}

inline void DmpSimuNudHit::operator delete(void* aHit)
{
  DmpSimuNudHitAllocator.FreeSingle((DmpSimuNudHit*) aHit);
}

#endif










