#include "StkTrackParams.h"

#include "TMath.h"
#include <iostream>

StkTrackParams::StkTrackParams() : m_StateVector(4,1),m_CovMatrix(4,4) {
}

StkTrackParams::StkTrackParams(Double_t xpos, Double_t xslope, Double_t ypos, Double_t yslope,
			     Double_t c00, Double_t c01, Double_t c02, Double_t c03,
			                   Double_t c11, Double_t c12, Double_t c13,
		                                         Double_t c22, Double_t c23,
		             	                                       Double_t c33):
  m_StateVector(4,1),m_CovMatrix(4,4) {

  m_StateVector(0,0) = xpos;
  m_StateVector(1,0) = xslope;
  m_StateVector(2,0) = ypos;
  m_StateVector(3,0) = yslope;

  //std::cout << "StkTrackParams constructor: state vector " << std::endl;
  //m_StateVector.Print();

  m_CovMatrix(0,0) = c00;
  m_CovMatrix(0,1) = c01;
  m_CovMatrix(0,2) = c02;
  m_CovMatrix(0,3) = c03;

  m_CovMatrix(1,1) = c11;
  m_CovMatrix(1,2) = c12;
  m_CovMatrix(1,3) = c13;

  m_CovMatrix(2,2) = c22;
  m_CovMatrix(2,3) = c23;

  m_CovMatrix(3,3) = c33;

}



