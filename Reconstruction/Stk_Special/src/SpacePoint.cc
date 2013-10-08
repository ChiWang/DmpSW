// Description: This class implements the STK space point definition:  
//   a pair of x- and y-view clusters of the same tracking plane and 
//   at the same 4-ladder block 
//
// Author(s):
//  - creation by X.Wu, 07/09/2013

#include "SpacePoint.h"

#include "StkParamDef.h"
#include "TMath.h"
#include <iostream>

Double_t SpacePoint:: getXlayerZ() 
{
  if(m_plane<0 && m_plane>5) {
    std::cout << " SpacePoint has plane number " << m_plane << " out of range! " << std::endl;
    return -999999.;
  } 

  if(m_block<0 && m_block>3) {
    std::cout << " SpacePoint has block number " << m_block << " out of range! " << std::endl;
    return -999999.;
  } 
  //return Xlayer_z[m_plane]; 
  return StkParamDef::Xstrips_z[m_plane]; 
}

Double_t SpacePoint:: getYlayerZ() 
{
  if(m_plane<0 && m_plane>5) {
    std::cout << " SpacePoint has plane number " << m_plane << " out of range! " << std::endl;
    return -999999.;
  } 
  if(m_block<0 && m_block>3) {
    std::cout << " SpacePoint has block number " << m_block << " out of range! " << std::endl;
    return -999999.;
  } 
  //return Ylayer_z[m_plane]; 
  return StkParamDef::Ystrips_z[m_plane]; 
}

TVector3 SpacePoint::getPosition() {
  TVector3 pos( getClusX(), getClusY(), 0.5*(getXlayerZ() + getYlayerZ()) );
  return pos;
}

void SpacePoint::Print() {
  std::cout << "==== SpacePoint in plane " << m_plane <<", block "<< m_block << std::endl;
  std::cout << "                x cluster at z = " << getXlayerZ()  << ", x = " << m_xClus << std::endl;
  std::cout << "                y cluster at z = " << getYlayerZ()  << ", y = " << m_yClus << std::endl;
}
