/*
 *  $Id: DmpRdcSvcDataMgr.h, 2014-05-20 14:32:48 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcSvcDataMgr_H
#define DmpRdcSvcDataMgr_H

#include <fstream>

#include "DmpVDataMgr.h"
#include "DmpVSvc.h"
#include "DmpDetectorID.h"

class DmpEvtRdcHeader;
class TClonesArray;

class DmpRdcSvcDataMgr : public DmpVSvc, public DmpVDataMgr{
/*
 *  DmpRdcSvcDataMgr
 *
 *
*/
public:
  DmpRdcSvcDataMgr();
  ~DmpRdcSvcDataMgr();
  bool Initialize() {return true;}
  bool Finalize()   {return true;}
  void Set(const std::string&, const std::string&);
  void BookBranch();
  void FillEvent();
  void ResetEvent();    // delete all elements in TClonesArray

public:
  bool OpenInputData();
  std::ifstream* InFileStream() {return &fInDataStream;}
  DmpEvtRdcHeader* GetEventHeader() const {return fEvtHeader;}
  TClonesArray* GetOutCollection(DmpDetector::DmpEDetectorID) const;

private:
  std::ifstream     fInDataStream;  // inFile stream. update it for every binary data

private:
  DmpEvtRdcHeader   *fEvtHeader;
  TClonesArray      *fPsdOutSet;
  TClonesArray      *fBgoOutSet;
  TClonesArray      *fStkOutSet;
  TClonesArray      *fNudOutSet;
};

#endif


