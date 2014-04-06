/*
 *  $Id: DmpCalBgoMSD.h, 2014-04-05 17:05:57 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/12/2013
*/

#ifndef DmpCalBgoMSD_H
#define DmpCalBgoMSD_H

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
struct DmpCalBgoMSD : public TObject{
  /*
   * DmpCalBgoMSD
   *
   * not set SDID at here, since we will store all bars in DmpCalBgo
   *
   */
  DmpCalBgoPMT  PMT0;       // side 0
  DmpCalBgoPMT  PMT1;       // side 1

  ClassDef(DmpCalBgoMSD,1)
};

#endif


