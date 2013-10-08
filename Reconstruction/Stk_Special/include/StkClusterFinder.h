#ifndef StkClusterFinder_h
#define StkClusterFinder_h

#include <TH2.h>
#include "TROOT.h"
#include <iostream>
#include <TMatrixD.h>
#include "TVector3.h"
#include <TObjArray.h>

#include "SiCluster.h"
#include "SpacePoint.h"

class StkClusterFinder {

 private:

 public:
  StkClusterFinder() { init(); }
  virtual ~StkClusterFinder() {
    for (unsigned int i = 0; i < m_siClusters_pass1.size(); ++i) {
      delete m_siClusters_pass1[i]; 
    }
    m_siClusters_pass1.clear();
    for (unsigned int i = 0; i < m_siClusters_pass2.size(); ++i) {
      delete m_siClusters_pass2[i]; 
    }
    m_siClusters_pass2.clear();

    m_siClusters_layer_pass1.clear();
    m_siClusters_layer_pass2.clear();
  }

  void findCluster(std::vector<int>* SiDigit_strip, std::vector<double>* SiDigit_e, std::vector<unsigned int> * SiDigit_trackID);
  void init();
  void clearCluster();

  inline void set3sigma(double thrhld)     {m_3sigma      = thrhld;}
  inline void setNsigmaWidth(double width) {m_nsigmaWidth = width; }
  inline void setSeedThr(double thrhld)    {m_seedThr     = thrhld;}
  inline void setSeedThrSub(double thrhld) {m_seedThrSub  = thrhld;}

  std::vector<SiCluster*>& getClusters(SiCluster::ClusterType type);
  std::vector<std::vector<SiCluster*> >& getClusters_layer(SiCluster::ClusterType type);

  void findSpacePointInFullPlane(int plane, SiCluster::ClusterType type, std::vector<SpacePoint>& spacePoints);
  void findSpacePointInFullPlane(int plane, SiCluster::ClusterType type, std::vector<SpacePoint>& spacePoints, int view);

  void findSpacePointInPlane(int plane, TVector3 pos, TVector3 dir, double radius, SiCluster::ClusterType type, std::vector<SpacePoint>& spacePoints);
  //bool findNearestCluInLayer(int layer, double coord, double sigma, SiCluster::ClusterType type, SiCluster& clu);
  SiCluster* findNearestCluInLayer(int layer, double coord, double sigma, SiCluster::ClusterType type);

  int getNclusterInLayer(int layer, SiCluster::ClusterType type);
  int getNclusterInPlane(int plane, SiCluster::ClusterType type);
  void plotDelX(TVector3 pos, TVector3 dir, SiCluster::ClusterType type);
  
  int getTotalMaxTRB()                     {return m_totalMaxTRB;} 
  int getNmaxTRB()                         {return m_nMaxTRB;}
  int getTotalMaxClusPass1TRB()            {return m_totalMaxClusPass1TRB;}
  int getNmaxClusPass1TRB()                {return m_nMaxClusPass1TRB;}
  int getTotalMaxClusPass2TRB()            {return m_totalMaxClusPass2TRB;}
  int getNmaxClusPass2TRB()                {return m_nMaxClusPass2TRB;}
  double getLayerEnergy(int layer)         {return  m_layerEnergy[layer];} 
  double getLayerEnergyCluster(int layer)  {return  m_layerEnergyCluster[layer];} 
  int getNdigiLayer(int layer)             {return  m_nDigiLayer[layer];} 
  int getNdigiPlane(int plane)             {return  m_nDigiPlane[plane];} 
  int getNdigiTotal()                      {return  m_nDigitTot;}              

 private:

  TH1F* m_hNDigitTot;
  TH1F* m_hNDigit3sig;
  TH1F* m_hNDigit3sigL;
  
  TH1F* m_hSiDigit002;
  TH1F* m_hSiDigit003;
  TH1F* m_hSiDigit004;
  TH1F* m_hSiDigit005;
  TH1F* m_hSiDigit006;
  TH1F* m_hSiDigit007;
  TH1F* m_hSiDigit008;
  
  TH1F* m_hSiClus000;
  TH1F* m_hSiClus300;

  TH1F* m_hSiClus002;
  TH1F* m_hSiClus003;

  TH1F* m_hSiClus005;
  TH1F* m_hSiClus007;
  TH1F* m_hSiClus008;

  TH1F* m_hSiClus105;
  TH1F* m_hSiClus107;
  TH1F* m_hSiClus108;

  TH2F* m_hSiClusX;
  TH2F* m_hSiClusY;

  TObjArray* m_hNCluLayer;
  TObjArray* m_hNClu1Layer;

  TObjArray* m_hCluDelX;
  TObjArray* m_hCluMinDelX;

  double m_nsigmaWidth;
  double m_3sigma;
  double m_seedThr;  //cluster seed threshold_layer
  double m_seedThrSub; //sub cluster seed threshold
  double m_ladder0Center[4][2];
  double m_ladderDistance;

  std::vector<SiCluster*>  m_siClusters_pass1;  
  std::vector<SiCluster*>  m_siClusters_pass2;  
  std::vector<std::vector<SiCluster*> > m_siClusters_layer_pass1;
  std::vector<std::vector<SiCluster*> > m_siClusters_layer_pass2;

  int m_nDigitTot;
  int m_totalMaxTRB;
  int m_nMaxTRB;
  int m_totalMaxClusPass1TRB;
  int m_nMaxClusPass1TRB;
  int m_totalMaxClusPass2TRB;
  int m_nMaxClusPass2TRB;
  int m_nDigiLayer[12];
  int m_nDigiPlane[6];
  double m_layerEnergy[12];
  double m_layerEnergyCluster[12];

};

#endif
