/*
 *  $Id: DmpEventRaw.cc, 2014-03-02 22:37:03 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include "TClonesArray.h"

#include "DmpEvtHeader.h"
#include "DmpEvtBgoHit.h"
#include "DmpEventRaw.h"

ClassImp(DmpEventRaw)

DmpEventRaw::DmpEventRaw()
 :fEvtHeader(0),
  fBgoHits(0)
{
  fEvtHeader = new DmpEvtHeader();
  fBgoHits = new TClonesArray("DmpEvtBgoHit",300);
}

DmpEventRaw::~DmpEventRaw(){
  fBgoHits->Delete();
  fBgoHits->Clear();
  delete fBgoHits;
  DmpEvtHeader::Clear();
}

