// Description: This class implements the STK cluster definition  
//
// Author(s):
//  - creation by X.Wu, 07/09/2013

#include "SiCluster.h"

#include "StkParamDef.h"
#include "TMath.h"
#include <iostream>

Double_t SiCluster:: getLayerZ() 
{
  int plane = getPlane();
  if(plane<0 && plane>5) {
    std::cout << " SiCluster has plane number " << plane << " out of range! " << std::endl;
    return -999999.;
  } 

  int block = getBlock();
  if(block<0 && block>3) {
    std::cout << " SiCluster has block number " << block << " out of range! " << std::endl;
    return -999999.;
  } 

  int view = getView();
  if(block<0 && block>1) {
    std::cout << " SiCluster has view number " << view << " out of range! " << std::endl;
    return -999999.;
  } 

  if(view==1) return StkParamDef::Xstrips_z[plane]; 
  else return StkParamDef::Ystrips_z[plane]; 

}

Int_t SiCluster:: getPlane() {
  //return plane number 0-5 (from calorimenter)
  return m_ladder/32;
}

Int_t SiCluster:: getTRB() {
  return getBlock()*2+getView();
}

Int_t SiCluster:: getBlock() {
  return (m_ladder%16)/4;
}

Int_t SiCluster:: getView() {
  return (m_ladder/16)%2;
}

void SiCluster::Print() {
  std::cout << "    SiCluster in plane " << getPlane() <<", block "<< getBlock() << " isX = " << getView()<< std::endl;
  std::cout << "           centroid = " << m_Xcentroid  << ", energy = " << m_energy << " nstrip = " 
	    << m_nstrip << " maxstripE = " << m_maxstripEnergy << std::endl;
}
