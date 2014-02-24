#ifndef DmpSimuNudDigi_h
#define DmpSimuNudDigi_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimuNudDigi : public G4VDigi
{

public:
  
  DmpSimuNudDigi();
  ~DmpSimuNudDigi();
  DmpSimuNudDigi(const DmpSimuNudDigi&);
  const DmpSimuNudDigi& operator=(const DmpSimuNudDigi&);
  int operator==(const DmpSimuNudDigi&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
//  G4int StripNumber; //  (active detector)

  G4double Energy;     //total energy deposit
 
public:
  
//  inline void SetStripNumber(G4int Num)  {StripNumber = Num;};
  inline void SetEnergy(G4double Ene)    {Energy = Ene;};

//  inline G4int    GetStripNumber()   {return StripNumber;};
  inline G4double GetEnergy()        {return Energy;};

};

typedef G4TDigiCollection<DmpSimuNudDigi> DmpSimuNudDigitsCollection;

extern G4Allocator<DmpSimuNudDigi> DmpSimuNudDigiAllocator;

inline void* DmpSimuNudDigi::operator new(size_t)
{
  void* aDigi;
  aDigi = (void*) DmpSimuNudDigiAllocator.MallocSingle();
  return aDigi;
}

inline void DmpSimuNudDigi::operator delete(void* aDigi)
{
  DmpSimuNudDigiAllocator.FreeSingle((DmpSimuNudDigi*) aDigi);
}

#endif









