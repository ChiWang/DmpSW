/*
 *  $Id: DmpEventRaw.cc, 2014-03-02 22:37:03 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include "TClonesArray.h"

#include "DmpEventRaw.h"
#include "DmpEvtHeader.h"
// *
// *  TODO: add hits collection of Psd, Stk and Nud
// *
//#include "DmpEvtPsdMSD.h"
//#include "DmpEvtStkMSD.h"
#include "DmpEvtBgoMSD.h"
//#include "DmpEvtNudMSD.h"

ClassImp(DmpEventRaw)

DmpEventRaw::DmpEventRaw()
 :fEvtHeader(0),
  fPsdMSDSet(0),
  fStkMSDSet(0),
  fBgoMSDSet(0),
  fNudMSDSet(0)
{
  fEvtHeader = new DmpEvtHeader();
  fBgoMSDSet = new TClonesArray("DmpEvtBgoMSD",300);
// *
// *  TODO: add hits collection of Psd, Stk and Nud
// *
  fPsdMSDSet = new TClonesArray("DmpEvtPsdMSD",300);
  fStkMSDSet = new TClonesArray("DmpEvtStkMSD",300);
  fNudMSDSet = new TClonesArray("DmpEvtNudMSD",300);
}

//-------------------------------------------------------------------
DmpEventRaw::~DmpEventRaw(){
  delete fEvtHeader;
  fBgoMSDSet->Delete();
  fBgoMSDSet->Clear();
  delete fBgoMSDSet;
// *
// *  TODO: add hits collection of Psd, Stk and Nud
// *
  fPsdMSDSet->Delete();
  fPsdMSDSet->Clear();
  delete fPsdMSDSet;
  fStkMSDSet->Delete();
  fStkMSDSet->Clear();
  delete fStkMSDSet;
  fNudMSDSet->Delete();
  fNudMSDSet->Clear();
  delete fNudMSDSet;
}

void DmpEventRaw::Reset(){
  // event header not need reset function.
  fPsdMSDSet->Delete();   fPsdMSDSet->Clear();
  fStkMSDSet->Delete();   fStkMSDSet->Clear();
  fBgoMSDSet->Delete();   fBgoMSDSet->Clear();
  fNudMSDSet->Delete();   fNudMSDSet->Clear();
}

//-------------------------------------------------------------------
TClonesArray* DmpEventRaw::GetMSDCollection(DmpDetector::DmpEDetectorID id) const {
  if(id == DmpDetector::kPsd)    return fPsdMSDSet;
  if(id == DmpDetector::kStk)    return fStkMSDSet;
  if(id == DmpDetector::kBgo)    return fBgoMSDSet;
  if(id == DmpDetector::kNud)    return fNudMSDSet;
}


