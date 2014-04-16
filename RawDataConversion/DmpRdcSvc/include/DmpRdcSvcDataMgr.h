/*
 *  $Id: DmpRdcSvcDataMgr.h, 2014-04-10 21:23:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcSvcDataMgr_H
#define DmpRdcSvcDataMgr_H

#include <fstream>
#include "DmpVDataMgr.h"
#include "DmpVSvc.h"
#include "DmpDetectorID.h"

class DmpEvtHeader;
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

public:
  std::ifstream gInDataStream;  // inFile stream. update it for every binary data
  DmpEvtHeader* GetEventHeader() const {return fEvtHeader;}
  TClonesArray* GetOutCollection(DmpDetector::DmpEDetectorID) const;

private:
  bool SetInputData(const std::string&);
  void ResetEvent();            // delete all elements in TClonesArray

private:
  DmpEvtHeader      *fEvtHeader;
  TClonesArray      *fPsdOutSet;
  TClonesArray      *fBgoOutSet;
  TClonesArray      *fStkOutSet;
  TClonesArray      *fNudOutSet;
};

#endif

