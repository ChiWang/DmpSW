/*
 *  $Id: DmpRdcDataManager.h, 2014-03-09 20:12:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcDataManager_H
#define DmpRdcDataManager_H

#include <fstream>
#include "DmpVDataManager.h"

//class DmpEventRaw;
class DmpEvtHeader;
class TClonesArray;

class DmpRdcDataManager : public DmpVDataManager{
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
  void Initialize();
  void BookBranch();
  void FillEvent();

private:
  DmpRdcDataManager();

public:
  std::ifstream gInDataStream;   // inFile stream. update it for every binary data
  DmpEvtHeader* GetEventHeader() const {return fEvtHeader;}
  TClonesArray* GetMSDCollection(DmpDetector::DmpEDetectorID) const;
  //DmpEventRaw*  GetRawEvent() const {return fEvtRaw;}

private:
  //DmpEventRaw   *fEvtRaw;
  DmpEvtHeader      *fEvtHeader;
  TClonesArray      *fPsdMSDSet;
  TClonesArray      *fBgoMSDSet;
  TClonesArray      *fStkMSDSet;
  TClonesArray      *fNudMSDSet;
};

//-------------------------------------------------------------------
extern DmpRdcDataManager    *gDataMgr;

#endif

