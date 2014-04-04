/*
 *  $Id: DmpCalBgo.h, 2014-04-04 10:37:20 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/12/2013
*/

#ifndef DmpCalBgo_H
#define DmpCalBgo_H

#include "TObject.h"

//-------------------------------------------------------------------
struct DmpCalBgoPMT : public TObject{
  float     fPedDy2[2];     // pedestal of dynode 2
  float     fPedDy5[2];     // pedestal of dynode 5
  float     fPedDy8[2];     // pedestal of dynode 8
  float     fMipDy8[2];     // mips of Dy8
  float     fRelDy25[2];    // relation of dy 2, 5
  float     fRelDy58[2];    // relation of dy 2, 5
  DmpCalBgoPMT(){
    fPedDy2[0]  = -1; fPedDy2[1]  = -1;
    fPedDy5[0]  = -1; fPedDy5[1]  = -1;
    fPedDy8[0]  = -1; fPedDy8[1]  = -1;
    fRelDy25[0] = -1; fRelDy25[1] = -1;
    fRelDy58[0] = -1; fRelDy58[1] = -1;
  }
  ClassDef(DmpCalBgoPMT,1)
};

//-------------------------------------------------------------------
struct DmpCalBgoBar : public TObject{
  /*
   * DmpCalBgoBar
   *
   * not set SDID at here, since we will store all bars in DmpCalBgo
   *
   */
  DmpCalBgoPMT  PMT0;       // side 0
  DmpCalBgoPMT  PMT1;       // side 1

  ClassDef(DmpCalBgoBar,1)
};

//-------------------------------------------------------------------
#include "DmpDetectorBgo.h"
class DmpCalBgo : public TObject{
/*
 * DmpCalBgo
 *
 * This class used to recore caliration results of Bgo
 *
 */
public:
  DmpCalBgo();
  ~DmpCalBgo(){}
  DmpCalBgoBar* GetBar(const int &SDID)const{
    // get one bar;
    return &fBarSet[SDID%100*DmpDetector::Bgol::kBarNo+SDID/100];
  }
  DmpCalBgoBar* GetRefBar(const short &Layer, const short &side)const{
    // get one Ref. bar;
    return &fRefBarSet[Layer*DmpDetector::Bgo::kRefBarNo+side];
  }

private:
  std::string   fUsedDate_Ped;      // used which data to calibration Pedestal
  std::string   fUsedDate_Mip;      // used which data to calibration Mips
  std::string   fUsedDate_Rel;      // used which data to calibration Relation

  DmpCalBgoBar  fBarSet[DmpDetector::Bgo::kPlaneNo*2*DmpDetector::Bgo::kBarNo];         // all bar const.
  DmpCalBgoBar  fRefBarSet[DmpDetector::Bgo::kPlaneNo*2*DmpDetector::Bgo::kRefBarNo];   // all Ref. bar

  ClassDef(DmpCalBgo,1)
};


#endif



