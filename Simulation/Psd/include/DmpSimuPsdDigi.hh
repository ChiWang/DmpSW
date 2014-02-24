#ifndef DmpSimuPsdDigi_h
#define DmpSimuPsdDigi_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimuPsdDigi : public G4VDigi
{

public:
  
  DmpSimuPsdDigi();
  ~DmpSimuPsdDigi();
  DmpSimuPsdDigi(const DmpSimuPsdDigi&);
  const DmpSimuPsdDigi& operator=(const DmpSimuPsdDigi&);
  int operator==(const DmpSimuPsdDigi&) const;
  
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

typedef G4TDigiCollection<DmpSimuPsdDigi> DmpSimuPsdDigitsCollection;

extern G4Allocator<DmpSimuPsdDigi> DmpSimuPsdDigiAllocator;

inline void* DmpSimuPsdDigi::operator new(size_t)
{
  void* aDigi;
  aDigi = (void*) DmpSimuPsdDigiAllocator.MallocSingle();
  return aDigi;
}

inline void DmpSimuPsdDigi::operator delete(void* aDigi)
{
  DmpSimuPsdDigiAllocator.FreeSingle((DmpSimuPsdDigi*) aDigi);
}

#endif









