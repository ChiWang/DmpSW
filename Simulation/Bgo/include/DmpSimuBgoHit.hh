#ifndef DmpSimuBgoHit_h
#define DmpSimuBgoHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimuBgoHit : public G4VHit
{
public:
  
  DmpSimuBgoHit();
  ~DmpSimuBgoHit();
  DmpSimuBgoHit(const DmpSimuBgoHit&);
  const DmpSimuBgoHit& operator=(const DmpSimuBgoHit&);
  int operator==(const DmpSimuBgoHit&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4double EdepNeg;      // Energy readout from the negative side of BGO bar
  G4double EdepPos;      // Energy readout from the positive side of BGO bar
  G4double SumPosition;  // Sum of Energy*position
  G4double EdepCAL;      // Energy deposited on the BGO bar
  G4ThreeVector pos;     // Position of the hit
  G4int CALBarNumber;    // Number of the BGO bars
  G4int CALLayerNumber;  // Number of the BGO layers
  G4int IsCALLayer;      // Type of the layer (0 X, 1 Y)

  G4int CALPlaneNumber;  // Provide number of BGO plane, to suit Xin's DmpSimuBgoHitNtupleMaker

public:
  
  inline void AddEnergyNeg(G4double de) {EdepNeg += de;};
  inline void AddEnergyPos(G4double de) {EdepPos += de;};
  inline void AddSumPosition(G4double de) { SumPosition += de;};
  inline void AddEnergy(G4double de) {EdepCAL += de;};
  inline void SetCALBarNumber(G4int i) {CALBarNumber = i;};
  inline void SetCALLayerNumber(G4int i) {CALLayerNumber = i;};
  inline void SetCALType(G4int i) {IsCALLayer = i;};
  inline void SetPos(G4ThreeVector xyz){ pos = xyz; }

  inline void SetCALPlaneNumber(G4int i){CALPlaneNumber = i;};
  
  inline G4double GetEdepCAL()          { return EdepCAL; };
  inline G4double GetEdepPos()          { return EdepPos; };
  inline G4double GetEdepNeg()          { return EdepNeg; };
  inline G4double GetSumPosition()      { return SumPosition; };
  inline G4int    GetCALBarNumber()     { return CALBarNumber; };
  inline G4int    GetCALLayerNumber()   { return CALLayerNumber; };
  inline G4int    GetCALType()          { return IsCALLayer;};      
  inline G4ThreeVector GetPos()         { return pos; };
  
  inline G4int    GetCALPlaneNumber()   { return CALPlaneNumber; };
};

typedef G4THitsCollection<DmpSimuBgoHit> DmpSimuBgoHitsCollection;

extern G4Allocator<DmpSimuBgoHit> DmpSimuBgoHitAllocator;

inline void* DmpSimuBgoHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*) DmpSimuBgoHitAllocator.MallocSingle();
  return aHit;
}

inline void DmpSimuBgoHit::operator delete(void* aHit)
{
  DmpSimuBgoHitAllocator.FreeSingle((DmpSimuBgoHit*) aHit);
}

#endif










