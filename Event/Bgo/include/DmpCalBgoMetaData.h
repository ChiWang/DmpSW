/*
 *  $Id: DmpCalBgoMetaData.h, 2014-04-04 21:24:38 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/12/2013
*/

#ifndef DmpCalBgoMetaData_H
#define DmpCalBgoMetaData_H

#include "TObject.h"

//-------------------------------------------------------------------
struct DmpCalBgoPMT : public TObject{
  float     fPedDy2[2];     // pedestal of dynode 2
  float     fPedDy5[2];     // pedestal of dynode 5
  float     fPedDy8[2];     // pedestal of dynode 8
  float     fMipDy8[2];     // mips of Dy8
  float     fRelDy25[2];    // relation of dy 2, 5
  float     fRelDy58[2];    // relation of dy 2, 5
  DmpCalBgoPMT();
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

class TClonesArray;
//-------------------------------------------------------------------
class DmpCalBgoMetaData : public TObject{
/*
 * DmpCalBgoMetaData
 *
 * This class used to recore caliration results of Bgo
 *
 */
public:
  DmpCalBgoMetaData();
  ~DmpCalBgoMetaData();
  DmpCalBgoBar* GetBar(const int &SDID)const;
  DmpCalBgoBar* GetRefBar(const short &layer, const short &side)const;

private:
  std::string   fUsedDate_Ped;      // used which data to calibration Pedestal
  std::string   fUsedDate_Mip;      // used which data to calibration Mips
  std::string   fUsedDate_Rel;      // used which data to calibration Relation

  TClonesArray  *fBarCollection;    //->
  TClonesArray  *fRefBarCollection; //->

  ClassDef(DmpCalBgoMetaData,1)
};


#endif


