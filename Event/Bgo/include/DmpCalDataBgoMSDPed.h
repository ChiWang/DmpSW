/*
 *  $Id: DmpCalDataBgoMSDPed.h, 2014-05-16 01:08:18 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/05/2014
*/

#ifndef DmpCalDataBgoMSDPed_H
#define DmpCalDataBgoMSDPed_H

#include "TObject.h"

//-------------------------------------------------------------------
class DmpCalDataBgoMSDPed : public TObject{
  /*
   * DmpCalDataBgoMSDPed
   *
   * not set SDID at here, since we will store all bars in DmpCalBgo
   *
   */
public:
  DmpCalDataBgoMSDPed(){
    for(short i=0;i<2;++i){
      for(short j=0;j<3;++j){
        fMean[i][j] = 0;
        fSigma[i][j] = 0;
      }
    }
  }
  ~DmpCalDataBgoMSDPed();
  void SetPedestal(const short &sideID, const short &dyID, const float &m, const float &s){
    fMean[sideID][(dyID-2)/3] = m;
    fSigma[sideID][(dyID-2)/3] = s;
  }
  const float& Mean(const short &sideID, const short &dyID) const   {return fMean[sideID][(dyID-2)/3];}
  const float& Sigma(const short &sideID, const short &dyID) const  {return fSigma[sideID][(dyID-2)/3];}

private:
  float     fMean[2][3];     // mean
  /*
   *    fMean[0][0]     side 0, dy2
   *    fMean[0][1]     side 0, dy5
   *    fMean[0][2]     side 0, dy8
   *
   */
  float     fSigma[2][3];    // sigma

  ClassDef(DmpCalDataBgoMSDPed,1)
};

#endif


