#ifndef SiCluster_h
#define SiCluster_h

#include "TROOT.h"

class SiCluster 
{

 public:
  enum ClusterType { kPass1 = 0,
		     kPass2};

 SiCluster(): m_ladder(-1), m_pass(-1) {}  

  virtual ~SiCluster() {}

  Int_t    getTRB();
  Int_t    getBlock();
  Int_t    getPlane();
  Double_t getLayerZ();
  Int_t    getSiLayer();
  Int_t    getView(); //1: x-view, 0: y-view

  inline   Int_t    getLadder()    {return m_ladder;}
  inline   Double_t getCentroid()  {return m_centroid;}
  inline   Double_t getXcentroid() {return m_Xcentroid;}
  inline   Double_t getWidth()     {return m_width;}
  inline   Double_t getEnergy()    {return m_energy;}
  inline   Double_t getMaxstripEnergy()    {return m_maxstripEnergy;}
  inline   Int_t    getNstrip()    {return m_nstrip;}
  inline   Int_t    getMaxstrip()  {return m_maxstrip;}
  inline   Int_t    getIndex1()    {return m_index1;}
  inline   Int_t    getShared()    {return m_shared;}
  inline   Int_t    getPass()      {return m_pass;}

  inline   void    setLadder    (Int_t ladder)       {m_ladder = ladder;}
  inline   void    setCentroid  (Double_t centroid)  {m_centroid = centroid;}
  inline   void    setXcentroid (Double_t Xcentroid) {m_Xcentroid = Xcentroid;}
  inline   void    setWidth     (Double_t width)     {m_width = width;}
  inline   void    setEnergy    (Double_t energy)    {m_energy = energy;}
  inline   void    setNstrip    (Int_t nstrip)       {m_nstrip = nstrip;}
  inline   void    setMaxstrip  (Int_t maxstrip)     {m_maxstrip = maxstrip;}
  inline   void    setMaxstripEnergy  (Double_t energy)     {m_maxstripEnergy = energy;}
  inline   void    setIndex1    (Int_t index1)       {m_index1 = index1;}
  inline   void    setShared    (Int_t shared)       {m_shared = shared;}
  inline   void    setPass      (Int_t pass)         {m_pass = pass;}

  void     Print();
  
 private:
  
  Int_t    m_ladder;
  Double_t m_centroid;
  Double_t m_Xcentroid;
  Double_t m_width;
  Double_t m_energy;
  Double_t m_maxstripEnergy;
  Int_t    m_nstrip;
  Int_t    m_maxstrip;
  Int_t    m_index1;
  Int_t    m_shared; //0 no sharedstrip, 1, first strip shared, 2 last strip shared, 3 both first and last strip shared
  Int_t    m_pass;

};

#endif
