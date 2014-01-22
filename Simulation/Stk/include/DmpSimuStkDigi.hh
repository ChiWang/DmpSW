#ifndef DmpSimuStkDigi_h
#define DmpSimuStkDigi_h 1

#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class DmpSimuStkDigi : public G4VDigi
{

public:
  
  DmpSimuStkDigi();
  ~DmpSimuStkDigi();
  DmpSimuStkDigi(const DmpSimuStkDigi&);
  const DmpSimuStkDigi& operator=(const DmpSimuStkDigi&);
  int operator==(const DmpSimuStkDigi&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();

private:
  
  G4int PlaneNumber; //  (active detector)
  G4int PlaneType;   // (0 or 1 for X or Y plane)
  G4int StripNumber; // strip number
  G4int DigiType;    // (not used anymore! 0 == STK, 1 == BGO, 2 == PSD)
  G4double Energy;     //total energy deposit
  G4double EnergyPrim; //energy deposit from primary paricles
  G4int PrimTrackID; // primary trackID
  G4int hitID;                // current hit ID
  G4int hitID1;               // previous hit ID
  G4int hitID2;               // previous hit ID
  G4int nTracks;              // number of tracks
  G4int nTracksBack;          // number of back scattering tracks
  G4int nTracksPrim;          // number of primary tracks
  G4int nHits;                // number of hits
  G4int nHitsBack;            // number of back scattering hits
 
public:
  
  inline void SetPlaneNumber(G4int PlaneNum)  {PlaneNumber = PlaneNum;};
  inline void SetPlaneType(G4int PlaneTyp)    {PlaneType = PlaneTyp;};
  inline void SetStripNumber(G4int StripNum)  {StripNumber = StripNum;};
  inline void SetDigiType(G4int DigiID)       {DigiType = DigiID;};
  inline void SetEnergy(G4double Ene)         {Energy = Ene;};
  inline void SetEnergyPrim(G4double Ene)     {EnergyPrim = Ene;};
  inline void SetPrimTrackID(G4int trackID)   {PrimTrackID=trackID;};
  inline void SetNtracks(G4int i)       { nTracks = i;      };
  inline void SetNtracksBack(G4int i)   { nTracksBack = i;  };
  inline void SetNtracksPrim(G4int i)   { nTracksPrim = i;  };
  inline void SetNhits(G4int i)         { nHits = i;      };
  inline void SetNhitsBack(G4int i)     { nHitsBack = i;  };
  inline void SetHitID(G4int i)       { hitID  = i;  };
  inline void SetHitID1(G4int i)      { hitID1 = i;  };
  inline void SetHitID2(G4int i)      { hitID2 = i;  };

  inline G4int GetPlaneNumber()     {return PlaneNumber;};
  inline G4int GetPlaneType()       {return PlaneType;};
  inline G4int GetStripNumber()     {return StripNumber;};
  inline G4int GetDigiType()        {return DigiType;};
  inline G4double GetEnergy()       {return Energy;};
  inline G4double GetEnergyPrim()   {return EnergyPrim;};
  inline G4int GetPrimTrackID()     {return PrimTrackID;};
  inline G4int    GetNtracks()      { return nTracks;       };      
  inline G4int    GetNtracksBack()  { return nTracksBack;   };      
  inline G4int    GetNtracksPrim()  { return nTracksPrim;   };      
  inline G4int    GetNhits()        { return nHits;       };      
  inline G4int    GetNhitsBack()    { return nHitsBack;   };      
  inline G4int    GetHitID()        { return hitID;   };      
  inline G4int    GetHitID1()       { return hitID1;  };      
  inline G4int    GetHitID2()       { return hitID2;  };      
  

};

typedef G4TDigiCollection<DmpSimuStkDigi> DmpSimuStkDigitsCollection;

extern G4Allocator<DmpSimuStkDigi> DmpSimuStkDigiAllocator;

inline void* DmpSimuStkDigi::operator new(size_t)
{
  void* aDigi;
  aDigi = (void*) DmpSimuStkDigiAllocator.MallocSingle();
  return aDigi;
}

inline void DmpSimuStkDigi::operator delete(void* aDigi)
{
  DmpSimuStkDigiAllocator.FreeSingle((DmpSimuStkDigi*) aDigi);
}

#endif









