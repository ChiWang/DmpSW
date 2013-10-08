#ifndef StkTrackParams_h
#define StkTrackParams_h

#include "TROOT.h"
#include <TMatrixD.h>

class StkTrackParams 
{

 public:
  
  StkTrackParams();  
  StkTrackParams(Double_t xpos, Double_t xslope, Double_t ypos, Double_t yslope,
		Double_t c00, Double_t c01, Double_t c02, Double_t c03,
			      Double_t c11, Double_t c12, Double_t c13,
		                            Double_t c22, Double_t c23,
		                                          Double_t c33);

  virtual ~StkTrackParams() {}
  void setStateVector(TMatrixD m)    {m_StateVector = m;}
  void setCovMatrix  (TMatrixD m)    {m_CovMatrix = m;}

  TMatrixD getStateVector()  {return m_StateVector;}
  TMatrixD getCovMatrix()    {return m_CovMatrix;}
   
 private:
  TMatrixD m_StateVector;//state vector
  TMatrixD m_CovMatrix;  //Convariant matrix: C
  
};

#endif
