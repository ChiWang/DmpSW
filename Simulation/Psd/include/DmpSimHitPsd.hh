#ifndef DmpSimHitPsd_h
#define DmpSimHitPsd_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimHitPsd : public G4VHit
{
public:
  
  DmpSimHitPsd();
  ~DmpSimHitPsd();
  DmpSimHitPsd(const DmpSimHitPsd&);
  const DmpSimHitPsd& operator=(const DmpSimHitPsd&);
  int operator==(const DmpSimHitPsd&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4double     Edep;  // Energy deposited
  G4ThreeVector pos;  // Position of the hit
  G4int StripNumber;  // Number of the strip

public:
  
  inline void AddEnergy(G4double de)      {Edep += de;};
  inline void SetStripNumber(G4int i)     {StripNumber = i;};
  inline void SetPos(G4ThreeVector xyz)   { pos = xyz; }
  
  inline G4double GetEdep()          { return Edep; };
  inline G4int    GetStripNumber()   { return StripNumber; };
  inline G4ThreeVector GetPos()      { return pos; };
  
};

typedef G4THitsCollection<DmpSimHitPsd> DmpSimHitPsdsCollection;

extern G4Allocator<DmpSimHitPsd> DmpSimHitPsdAllocator;

inline void* DmpSimHitPsd::operator new(size_t)
{
  void* aHit;
  aHit = (void*) DmpSimHitPsdAllocator.MallocSingle();
  return aHit;
}

inline void DmpSimHitPsd::operator delete(void* aHit)
{
  DmpSimHitPsdAllocator.FreeSingle((DmpSimHitPsd*) aHit);
}

#endif










