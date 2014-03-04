/*
 *  $Id: DmpEventRaw.cc, 2014-03-02 22:37:03 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include "TClonesArray.h"
#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"
//#include "DmpEvtPsdHit.h"
//#include "DmpEvtStkHit.h"
#include "DmpEvtBgoHit.h"
//#include "DmpEvtNudHit.h"
// *
// *  TODO: add hits collection of Psd, Stk and Nud
// *

ClassImp(DmpEventRaw)

DmpEventRaw::DmpEventRaw()
 :fEvtHeader(0),
  fPsdHits(0),
  fStkHits(0),
  fBgoHits(0),
  fNudHits(0)
{
  fEvtHeader = new DmpEvtHeader();
  fBgoHits = new TClonesArray("DmpEvtBgoHit",300);
// *
// *  TODO: add hits collection of Psd, Stk and Nud
// *
  //fPsdHits = new TClonesArray("DmpEvtPsdHit",300);
  //fStkHits = new TClonesArray("DmpEvtStkHit",300);
  //fNudHits = new TClonesArray("DmpEvtNudHit",300);
}

DmpEventRaw::~DmpEventRaw(){
  delete fEvtHeader;
  fBgoHits->Delete();
  fBgoHits->Clear();
  delete fBgoHits;
// *
// *  TODO: add hits collection of Psd, Stk and Nud
// *
}


