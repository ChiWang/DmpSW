/*
 *  $Id: DmpEvtRdcHeader.h, 2014-05-29 21:41:45 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpEvtRdcHeader_H
#define DmpEvtRdcHeader_H


#include <map>
#include <vector>
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
    //NotMatch_RunMode = 3,
    Wrong_DataLength = 4,
    NotMatch_Trigger = 5,
    Wrong_CRC = 6
  };
  void  SetErrorLog(DmpDetectorID::Type id,const short &FeeID,const DataErrorType &type);
  void  SetTime(const short&,const short&);
  void  SetTrigger(DmpDetectorID::Type id,short v)  {fTrigger.insert(std::make_pair(id,v));}
  void  SetRunMode(DmpDetectorID::Type id,short v);
  void  Reset();
  bool  IsGoodEvent() const;
  const long& GetSecond() const {return fSec;}
  const short& GetMillisecond() const {return fMillisec;}
  std::map<short,short> GetStatus() const {return fStatus;}
  short GetTrigger(DmpDetectorID::Type id = DmpDetectorID::kWhole) const;
  int GetRunMode(DmpDetectorID::Type id) const {return fRunMode.find(id)->second;}

private:
  long      fSec;           // second
  short     fMillisec;      // millisecond
  std::map<short,short>     fTrigger;       // 4 subDet + satellite trigger
  std::map<short,int>       fRunMode;
  std::map<short,short>     fStatus;        // status for this event
  /*
   * fStatus[DmpDetector::kWhole] is for global check, check all subDet
   *    good event:         0
   *    triggers match?
   *    run mode match?
   *
   * fStatus[key] is for Fee of subDet
   *    key = subDet ID * 100 + Fee ID
   *    value = DataErrorType
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

