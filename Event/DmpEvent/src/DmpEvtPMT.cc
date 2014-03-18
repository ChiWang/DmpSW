/*
 *  $Id: DmpEvtPMT.cc, 2014-03-02 22:44:49 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include "DmpEvtPMT.h"

ClassImp(DmpEvtPMT)

DmpEvtPMT::DmpEvtPMT()
 :fEnergy(0),
  fUsedDy(0)
{
  for (int i=0;i<2;++i) fADCDynode.push_back(i*10);
}

DmpEvtPMT::DmpEvtPMT(short size)
 :fEnergy(0),
  fUsedDy(0)
{
  for (int i=0;i<size;++i) fADCDynode.push_back(i*10);
}

DmpEvtPMT::~DmpEvtPMT(){
}

void DmpEvtPMT::Reset(){
}

