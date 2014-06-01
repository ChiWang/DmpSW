/*
 *  $Id: DmpEvtRdcHeader.h, 2014-05-29 21:41:45 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpEvtRdcHeader_H
#define DmpEvtRdcHeader_H

#include "TObject.h"

#include "DmpDetectorID.h"
#include "DmpRunMode.h"

//-------------------------------------------------------------------
class DmpEvtRdcHeader : public TObject{
/*
 * DmpEvtRdcHeader
 *
 * Anywhere could use this singleton
 *
*/
public:
  DmpEvtRdcHeader();
  ~DmpEvtRdcHeader();

  enum DataErrorType{
    Good = 0,
    NotFind_0xeb = 1,
    NotFind_0x90 = 2,
    NotMatch_RunMode = 3,
    Wrong_DataLength = 4,
    NotMatch_Trigger = 5,
    Wrong_CRC = 6
  };
  void  SetErrorLog(DmpDetector::DmpEDetectorID id,const short &FeeID,const DataErrorType &type);
  void  SetTime(const short&,const short&);
  //void  GenerateStatus();
  void  SetTrigger(DmpDetector::DmpEDetectorID id,const short &v);
  void  SetRunMode(DmpDetector::DmpEDetectorID id,const short &v);
  void  Reset();
  const long& GetSecond() const {return fSec;}
  const short& GetMillisecond() const {return fMillisec;}
  std::vector<short> GetStatus() const {return fStatus;}
  short GetTrigger(DmpDetector::DmpEDetectorID id = DmpDetector::kWhole) const;
  short GetRunMode(DmpDetector::DmpEDetectorID) const;

private:
  long      fSec;           // second
  short     fMillisec;      // millisecond
  std::vector<short>    fTrigger;       // 4 subDet + satellite trigger
  std::vector<short>    fRunMode;
  std::vector<short>    fStatus;        // status for this event
  /*
   * fStatus[0] is for global check, check all subDet
   *    good event:         0
   *    triggers match?
   *    run mode match?
   *
   * fStatus[i] is for subDet
   *    not find 0xeb:      1 + last_Fee_ID*10
   *    not find 0x90:      2 + last_Fee_ID*10
   *    data length error:  3 + Fee_ID*10
   *    CRC error:          4 + Fee_ID*10
   *
   */
  short     fTime[8];       //! not save
  /*
   *    8 bytes from satellite
   *    fTime[0~5] = second
   *    fTime[6~7] = millisecond
   *
   */

  ClassDef(DmpEvtRdcHeader,1)
};

#endif

