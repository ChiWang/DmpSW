/*
 *  $Id: DmpEvtHeader.h, 2014-07-31 09:28:55 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include <map>
#include "TObject.h"

#include "DmpDetectorID.h"
#include "DmpRunMode.h"
#include "DmpDataError.h"


class DmpEvtHeader : public TObject{
/*
 * DmpEvtHeader
 *
*/
public:
  DmpEvtHeader();
  ~DmpEvtHeader();

  void  Reset();                // invoke it at the begin of Rdc::ProcessThisEvent
  void  SetTrigger(short v) {fTrigger = v;}     // trigger of satellite
  void  SetHexTime(const short &v) {fHexTime.push_back(v);}
  void  SetFeeErrorTag(DmpDetectorID::Type id,const short &FeeID,const DmpDataError::Type &type);
  void  SetFeeStatus(DmpDetectorID::Type id,const short &FeeID,short trigger,short runMode);
  bool  TriggersMatch(DmpDetectorID::Type id=DmpDetectorID::kWhole)const;
  bool  IsGoodEvent() const;
  short GetTrigger(DmpDetectorID::Type id = DmpDetectorID::kWhole) const;
  std::map<short,short> GetErrorTag(DmpDetectorID::Type id) const {return fErrorTag.find(id)->second;}
  std::map<short,short> GetRunMode(DmpDetectorID::Type id) const {return fFeeRunMode.find(id)->second;}
  void PrintTime(const std::string &argv = "hex") const;

private:
  short     fTrigger;       // trigger from satellite
  std::vector<short>    fHexTime;       // save me
  /*
   *    8 bytes from satellite
   *    fHexTime[0~5] = second
   *    fHexTime[6~7] = millisecond
   */
  std::map<short,std::map<short,short> >    fFeeTrigger;
  /*
   *    fFeeTrigger[key_0][key_1]
   *    key_0:  detector id
   *        4 subDet
   *    key_1:  fee id
   */
  std::map<short,std::map<short,short> >    fFeeRunMode;
  /*
   *    fFeeRunMode[key_0][key_1]
   *    key_0:  detector id
   *        4 subDet
   *    key_1:  fee id
   */
  std::map<short,std::map<short,short> >    fErrorTag;        // status for this event
  /*
   *    fErrorTag[key_0][key_1]
   *    key_0:  detector id
   *        4 subDet
   *    key_1:  fee id
   */

  ClassDef(DmpEvtHeader,1)
};

#endif

