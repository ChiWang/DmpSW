#ifndef DmpSimDigPsd_h
#define DmpSimDigPsd_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimDigPsd : public G4VDigi
{

public:
  
  DmpSimDigPsd();
  ~DmpSimDigPsd();
  DmpSimDigPsd(const DmpSimDigPsd&);
  const DmpSimDigPsd& operator=(const DmpSimDigPsd&);
  int operator==(const DmpSimDigPsd&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4int StripNumber; //  (active detector)
  G4double Energy;     //total energy deposit
 
public:
  
  inline void SetStripNumber(G4int Num)  {StripNumber = Num;};
  inline void SetEnergy(G4double Ene)    {Energy = Ene;};

  inline G4int    GetStripNumber()   {return StripNumber;};
  inline G4double GetEnergy()        {return Energy;};

};

typedef G4TDigiCollection<DmpSimDigPsd> DmpSimDigPsdtsCollection;

extern G4Allocator<DmpSimDigPsd> DmpSimDigPsdAllocator;

inline void* DmpSimDigPsd::operator new(size_t)
{
  void* aDigi;
  aDigi = (void*) DmpSimDigPsdAllocator.MallocSingle();
  return aDigi;
}

inline void DmpSimDigPsd::operator delete(void* aDigi)
{
  DmpSimDigPsdAllocator.FreeSingle((DmpSimDigPsd*) aDigi);
}

#endif









