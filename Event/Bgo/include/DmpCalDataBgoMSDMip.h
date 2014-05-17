/*
 *  $Id: DmpCalDataBgoMSDMip.h, 2014-05-16 01:38:05 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/05/2014
*/

#ifndef DmpCalDataBgoMSDMip_H
#define DmpCalDataBgoMSDMip_H

#include "TObject.h"

//-------------------------------------------------------------------
class DmpCalDataBgoMSDMip : public TObject{
  /*
   * DmpCalDataBgoMSDMip
   *
   * not set SDID at here, since we will store all bars in DmpCalBgo
   *
   */
public:
  DmpCalDataBgoMSDMip():fMeanEng(0),fSigmaEng(0){
    for(short i=0;i<2;++i){
      fMeanAdc[i] = 0;
      fSigmaAdc[i] = 0;
    }
  }
  ~DmpCalDataBgoMSDMip(){}
  void SetMipAdc(const short &sideID, const float &m, const float &s){
    fMeanAdc[sideID] = m;
    fSigmaAdc[sideID] = s;
  }
  void SetMipEnergy(const float &m, const float &s)    {fMeanEng = m; fSigmaEng =s;}
  const float& MeanAdc(const short &sideID) const   {return fMeanAdc[sideID];}
  const float& SigmaAdc(const short &sideID) const  {return fSigmaAdc[sideID];}
  const float& MeanEnergy() const {return fMeanEng;}
  const float& SigmaEnergy() const {return fSigmaEng;}

private:
  float     fMeanAdc[2];        // mean of Adc, dy8
  /*
   *    fMeanAdc[0]     side 0, dy8
   *    fMeanAdc[1]     side 1, dy8
   *
   */
  float     fSigmaAdc[2];       // sigma of Adc, dy8

private:
  float     fMeanEng;           // mean of energy, MeV
  float     fSigmaEng;          // sigma of energy, MeV

  ClassDef(DmpCalDataBgoMSDMip,1)
};

#endif


