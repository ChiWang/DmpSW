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
  DmpEvtPMT();
  DmpEvtPMT(short vectorSize);
  ~DmpEvtPMT();
  void Reset();
  void SetSignal(const int&id, const short&v){fADCDynode[id] = v;}

private:
  double    fEnergy;        // unit MeV
  short     fUsedDy;        // used which dynode
// *
// *  TODO: why can not save all values in this vetor into root file???
// *
#pragma message("TODO ----> why can not save all values in this vetor into root file???")
  std::vector<float>    fADCDynode;        // ADC channels of dynodes

  ClassDef(DmpEvtPMT,1)
};

#endif
