/*
 *  $Id: DmpCalDataBgoMSDRel.h, 2014-05-16 01:14:07 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 15/05/2014
*/

#ifndef DmpCalDataBgoMSDRel_H
#define DmpCalDataBgoMSDRel_H

#include "TObject.h"

//-------------------------------------------------------------------
class DmpCalDataBgoMSDRel : public TObject{
  /*
   * DmpCalDataBgoMSDRel
   *
   * not set SDID at here, since we will store all bars in DmpCalBgo
   *
   */
public:
  DmpCalDataBgoMSDRel(){
    for(short i=0;i<2;++i){
      for(short j=0;j<2;++j){
        fSlope[i][j] = 0;
        fIntercept[i][j] = 0;
      }
    }
  }
  ~DmpCalDataBgoMSDRel(){}
  void SetRelation(const short &sideID, const short &theSmallerDyID, const float &s, const float &i){
    fSlope[sideID][(theSmallerDyID-2)/3] = s;
    fIntercept[sideID][(theSmallerDyID-2)/3] = i;
  }
  const float& Slope(const short &sideID, const short &theSmallerDyID) const    {return fSlope[sideID][(theSmallerDyID-2)/3];}
  const float& Intercept(const short &sideID, const short &theSmallerDyID) const    {return fIntercept[sideID][(theSmallerDyID-2)/3];}

private:
  float     fSlope[2][2];       // slope
  /*
   *    fSlope[0][0]     side 0, dy5 vs dy2
   *    fSlope[0][1]     side 0, dy8 vs dy5
   *
   */
  float     fIntercept[2][2];   // intercept

  ClassDef(DmpCalDataBgoMSDRel,1)
};

#endif


