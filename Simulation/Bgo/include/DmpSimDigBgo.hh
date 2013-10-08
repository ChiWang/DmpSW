#ifndef DmpSimDigBgo_h
#define DmpSimDigBgo_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimDigBgo : public G4VDigi
{

public:
  
  DmpSimDigBgo();
  ~DmpSimDigBgo();
  DmpSimDigBgo(const DmpSimDigBgo&);
  const DmpSimDigBgo& operator=(const DmpSimDigBgo&);
  int operator==(const DmpSimDigBgo&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4int BarNumber; //  (active detector)
  G4double Energy;     //total energy deposit
 
public:
  
  inline void SetBarNumber(G4int Num)    {BarNumber = Num;};
  inline void SetEnergy(G4double Ene)    {Energy = Ene;};

  inline G4int    GetBarNumber()     {return BarNumber;};
  inline G4double GetEnergy()        {return Energy;};

};

typedef G4TDigiCollection<DmpSimDigBgo> DmpSimDigBgotsCollection;

extern G4Allocator<DmpSimDigBgo> DmpSimDigBgoAllocator;

inline void* DmpSimDigBgo::operator new(size_t)
{
  void* aDigi;
  aDigi = (void*) DmpSimDigBgoAllocator.MallocSingle();
  return aDigi;
}

inline void DmpSimDigBgo::operator delete(void* aDigi)
{
  DmpSimDigBgoAllocator.FreeSingle((DmpSimDigBgo*) aDigi);
}

#endif









