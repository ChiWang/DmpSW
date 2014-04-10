/*
 *  $Id: DmpRdcSvcDataMgr.h, 2014-04-10 21:23:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcDataManager_H
#define DmpRdcDataManager_H

#include <fstream>
#include "DmpVIOSvc.h"
#include "DmpDetectorID.h"

class DmpEvtHeader;
class TClonesArray;

class DmpRdcDataManager : public DmpVIOSvc{
/*
 *  DmpRdcDataManager
 *
 *
*/
public:
  static DmpRdcDataManager* GetInstance(){
    static DmpRdcDataManager instance;
    return &instance;
  }
  ~DmpRdcDataManager();
  bool InputData(const std::string&);
  void BookBranch();
  void FillEvent();

private:
  DmpRdcDataManager();
  void ResetEvent();            // delete all elements in TClonesArray

public:
  std::ifstream gInDataStream;  // inFile stream. update it for every binary data
  DmpEvtHeader* GetEventHeader() const {return fEvtHeader;}
  TClonesArray* GetOutCollection(DmpDetector::DmpEDetectorID) const;

private:
  DmpEvtHeader      *fEvtHeader;
  TClonesArray      *fPsdOutSet;
  TClonesArray      *fBgoOutSet;
  TClonesArray      *fStkOutSet;
  TClonesArray      *fNudOutSet;
};

//-------------------------------------------------------------------
extern DmpRdcDataManager    *gRdcDataMgr;

#endif

