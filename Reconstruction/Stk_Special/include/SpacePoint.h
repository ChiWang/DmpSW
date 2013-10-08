#ifndef SpacePoint_h
#define SpacePoint_h

#include "TROOT.h"
#include <TMatrixD.h>
#include <TVector3.h>
#include "SiCluster.h"

class SpacePoint 
{

 public:

 SpacePoint(): m_plane(-1), m_block(-1), m_xClus(-999999), m_yClus(-999999), m_energyX(0), m_energyY(0), m_clusterX(0), m_clusterY(0) {}  

 SpacePoint(Int_t plane, Int_t block, Double_t clusX, Double_t clusY, Double_t energyX, Double_t energyY, SiCluster* xclu, SiCluster* yclu): 
  m_plane(plane), m_block(block), m_xClus(clusX), m_yClus(clusY), 
    m_energyX(energyX), m_energyY(energyY), m_clusterX(xclu), m_clusterY(yclu) {}
  
  virtual ~SpacePoint() {}
 
  inline Int_t    getPlane()    {return m_plane;} 
  inline Int_t    getBlock()    {return m_block;} 
  inline Double_t getClusX()    {return m_xClus;} 
  inline Double_t getClusY()    {return m_yClus;}
  inline Double_t getEnergyX()  {return m_energyX;} 
  inline Double_t getEnergyY()  {return m_energyY;}

  inline SiCluster* getXClus()    {return m_clusterX;} 
  inline SiCluster* getYClus()    {return m_clusterY;} 
 
  TVector3 getPosition(); 
  Double_t getXlayerZ(); 
  Double_t getYlayerZ(); 
  void     Print();
  
 private:
  
  Int_t m_plane;
  Int_t m_block;
  Double_t m_xClus;
  Double_t m_yClus;
  Double_t m_energyX;
  Double_t m_energyY;
  SiCluster* m_clusterX;
  SiCluster* m_clusterY;
 
};

#endif
