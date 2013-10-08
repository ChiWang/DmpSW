#ifndef DmpSimHitBgo_h
#define DmpSimHitBgo_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimHitBgo : public G4VHit
{
public:
  
  DmpSimHitBgo();
  ~DmpSimHitBgo();
  DmpSimHitBgo(const DmpSimHitBgo&);
  const DmpSimHitBgo& operator=(const DmpSimHitBgo&);
  int operator==(const DmpSimHitBgo&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4double EdepCAL;      // Energy deposited on the BGO bar
  G4ThreeVector pos;     // Position of the hit
  G4int CALBarNumber;    // Number of the BGO bars
  G4int CALPlaneNumber;  // Number of the BGO planes
  G4int IsCALPlane;      // Type of the plane (0 X, 1 Y)

public:
  
  inline void AddEnergy(G4double de) {EdepCAL += de;};
  inline void SetCALBarNumber(G4int i) {CALBarNumber = i;};
  inline void SetCALPlaneNumber(G4int i) {CALPlaneNumber = i;};
  inline void SetCALType(G4int i) {IsCALPlane = i;};
  inline void SetPos(G4ThreeVector xyz){ pos = xyz; }
  
  inline G4double GetEdepCAL()     { return EdepCAL; };
  inline G4int    GetCALBarNumber()   { return CALBarNumber; };
  inline G4int    GetCALPlaneNumber()   { return CALPlaneNumber; };
  inline G4int    GetCALType()   {return IsCALPlane;};      
  inline G4ThreeVector GetPos() { return pos; };
  
};

typedef G4THitsCollection<DmpSimHitBgo> DmpSimHitBgosCollection;

extern G4Allocator<DmpSimHitBgo> DmpSimHitBgoAllocator;

inline void* DmpSimHitBgo::operator new(size_t)
{
  void* aHit;
  aHit = (void*) DmpSimHitBgoAllocator.MallocSingle();
  return aHit;
}

inline void DmpSimHitBgo::operator delete(void* aHit)
{
  DmpSimHitBgoAllocator.FreeSingle((DmpSimHitBgo*) aHit);
}

#endif










