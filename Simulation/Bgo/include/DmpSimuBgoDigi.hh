#ifndef DmpSimuBgoDigi_h
#define DmpSimuBgoDigi_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimuBgoDigi : public G4VDigi
{

public:
  
  DmpSimuBgoDigi();
  ~DmpSimuBgoDigi();
  DmpSimuBgoDigi(const DmpSimuBgoDigi&);
  const DmpSimuBgoDigi& operator=(const DmpSimuBgoDigi&);
  int operator==(const DmpSimuBgoDigi&) const;
  
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

typedef G4TDigiCollection<DmpSimuBgoDigi> DmpSimuBgoDigitsCollection;

extern G4Allocator<DmpSimuBgoDigi> DmpSimuBgoDigiAllocator;

inline void* DmpSimuBgoDigi::operator new(size_t)
{
  void* aDigi;
  aDigi = (void*) DmpSimuBgoDigiAllocator.MallocSingle();
  return aDigi;
}

inline void DmpSimuBgoDigi::operator delete(void* aDigi)
{
  DmpSimuBgoDigiAllocator.FreeSingle((DmpSimuBgoDigi*) aDigi);
}

#endif









