#ifndef StkTrack_h
#define StkTrack_h

#include "TROOT.h"
#include <iostream>
#include <TVector.h>
#include <TVector3.h>
#include <TMatrixD.h>

#include "SiCluster.h"
#include "StkTrackParams.h"

class StkTrack 
{

 public:
  //status represent 4 steps of Kalman filter
  enum SeedType { kUndefined = 0,
		  kCaloSeed,
		  kCPseed,
		  kTreeSeed};
  
  StkTrack();  
  
  virtual ~StkTrack() {}

  inline unsigned int getSeedType()            {return m_seedType; }
  inline int getNhits()                        {return m_nHitX+m_nHitY; }
  inline int getNhitX()                        {return m_nHitX;    }
  inline int getNhitY()                        {return m_nHitY;    }
  inline int getNGapX()                        {return m_nGapX;    }
  inline int getNGapY()                        {return m_nGapY;    }
  inline double getChi2()                      {return m_chi2tot;  }
  inline TVector3 getDirection()               {return m_direction;}
  StkTrackParams& getTrackParams()             {return m_trackParams;}; 

  void setTrackParams(StkTrackParams& trackParams) { m_trackParams = trackParams; }

  inline void setNGapX(int gap)                {m_nGapX = gap;}
  inline void setNGapY(int gap)                {m_nGapY = gap;}
  inline void setNHitX(int nhit)               {m_nHitX = nhit;}
  inline void setNHitY(int nhit)               {m_nHitY = nhit;}
  
 private:
  unsigned int m_seedType;
  int m_nGapX;
  int m_nGapY;
  int m_nHitX;
  int m_nHitY;

  Double_t m_chi2tot;
  TVector3 m_direction;
  StkTrackParams m_trackParams;

};

#endif
