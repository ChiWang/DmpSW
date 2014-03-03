/*
 *  $Id: DmpEvtPMT.h, 2014-03-02 22:52:13 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/02/2014
*/

#ifndef DmpEvtPMT_H
#define DmpEvtPMT_H

#include <vector>
#include "TObject.h"

class DmpEvtPMT : public TObject{
/*
 * DmpEvtPMT will be used in DmpEvtBgoHit and DmpEvtPsdHit
 *
 */
public:
  DmpEvtPMT(short vectorSize);
  ~DmpEvtPMT();
  void Reset();

private:
  double    fEnergy;        // unit MeV
  short     fUsedDy;        // used which dynode
  std::vector<float>    fADCDynode;        // ADC channels of dynodes

  ClassDef(DmpEvtPMT,1)
};

#endif
