/*
 *  $Id: DmpCalBgoBarPed.h, 2014-07-19 15:08:43 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/05/2014
*/

#ifndef DmpCalBgoBarPed_H
#define DmpCalBgoBarPed_H

#include "TObject.h"

//-------------------------------------------------------------------
class DmpCalBgoBarPed : public TObject{
  /*
   * DmpCalBgoBarPed
   *
   * not set SDID at here, since we will store all bars in DmpCalBgo
   *
   */
public:
  DmpCalBgoBarPed(){
    for(short i=0;i<2;++i){
      for(short j=0;j<3;++j){
        fMean[i][j] = 0;
        fSigma[i][j] = 0;
      }
    }
  }
  ~DmpCalBgoBarPed(){}
  void  SetGlobalBarID(const short &id) {fGlobalBarID = id;}
  void SetPedestal(const short &sideID, const short &dyID, const float &m, const float &s){
    fMean[sideID][(dyID-2)/3] = m;
    fSigma[sideID][(dyID-2)/3] = s;
  }
  short GetLayerID() const {return fGlobalBarID/100;}
  short GetBarID() const {return fGlobalBarID%100;}   // in one layer
  short GetGlobalBarID() const {return fGlobalBarID;} // in whole layer
  const float& GetMean(const short &sideID, const short &dyID) const   {return fMean[sideID][(dyID-2)/3];}
  const float& GetSigma(const short &sideID, const short &dyID) const  {return fSigma[sideID][(dyID-2)/3];}

private:
  short     fGlobalBarID;   // unique sensitive detector(minimum detector unit) ID. Bgo bar ID. fGlobalBarID =  layerID*100 + barID
  float     fMean[2][3];    // mean. fMean[SideID][DyID]
  float     fSigma[2][3];   // sigma

  ClassDef(DmpCalBgoBarPed,1)
};

#endif


