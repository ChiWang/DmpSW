/*
 *  $Id: DmpRdcDataManager.h, 2014-04-08 14:51:08 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcDataManager_H
#define DmpRdcDataManager_H

#include <fstream>
#include "DmpVIO.h"
#include "DmpDetectorID.h"

class DmpEvtHeader;
class TClonesArray;

class DmpRdcDataManager : public DmpVIO{
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
extern DmpRdcDataManager    *gDataMgr;

#endif

