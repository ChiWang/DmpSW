/*
 *  $Id: DmpDataBgoBarPed.h, 2014-07-24 09:39:43 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/05/2014
*/

#ifndef DmpDataBgoBarPed_H
#define DmpDataBgoBarPed_H

#include "TObject.h"

//-------------------------------------------------------------------
class DmpDataBgoBarPed : public TObject{
  /*
   * DmpDataBgoBarPed
   *
   */
public:
  DmpDataBgoBarPed(){
    for(short i=0;i<2;++i){
      for(short j=0;j<3;++j){
        fMean[i][j] = 0;
        fSigma[i][j] = 0;
      }
    }
  }
  ~DmpDataBgoBarPed(){}
  void SetGlobalBarID(const short &id) {fGlobalBarID = id;}
  void SetPedestal(const short &sideID, const short &dyID, const float &m, const float &s){
    fMean[sideID][(dyID-2)/3] = m;
    fSigma[sideID][(dyID-2)/3] = s;
  }
  short GetLayerID() const {return fGlobalBarID/100;}
  short GetBarID() const {return fGlobalBarID%100;}   // in one layer
  short GetGlobalBarID() const {return fGlobalBarID;} // in whole layer
  float GetMean(const short &sideID, const short &dyID) const   {return fMean[sideID][(dyID-2)/3];}
  float GetSigma(const short &sideID, const short &dyID) const  {return fSigma[sideID][(dyID-2)/3];}

private:
  short     fGlobalBarID;   // unique sensitive detector(minimum detector unit) ID. Bgo bar ID. fGlobalBarID =  layerID*100 + barID
  float     fMean[2][3];    // mean. fMean[SideID][DyID]
  float     fSigma[2][3];   // sigma

  ClassDef(DmpDataBgoBarPed,1)
};

#endif


