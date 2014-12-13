/*
 *  $Id: DmpEvtHeader.h, 2014-08-05 13:59:29 DAMPE $
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
  void  SetPackageID(short v) {fPackageID = v;}     // trigger of satellite
  void  SetHexTime(const short &v) {fHexTime.push_back(v);}
  void  AddFeeErrorTag(DmpDetectorID::Type id,const short &FeeID,const DmpDataError::Type &type);
  void  SetTrigger(DmpDetectorID::Type id,std::map<short,short> triggers)  {fFeeTrigger.insert(std::make_pair(id,triggers));}
  void  SetRunMode(DmpDetectorID::Type id,std::map<short,short> modes)  {fFeeRunMode.insert(std::make_pair(id,modes));}
  short GetTrigger(DmpDetectorID::Type id = DmpDetectorID::kWhole) const;   // if not match, return -1
  std::map<short,short> GetErrorTag(DmpDetectorID::Type id) const {return fFeeErrorTag.find(id)->second;}
  std::map<short,short> GetRunMode(DmpDetectorID::Type id) const {return fFeeRunMode.find(id)->second;}
  bool  TriggersMatch(DmpDetectorID::Type id=DmpDetectorID::kWhole)const;
  bool  RunModesMatch(DmpDetectorID::Type)const;
  bool  IsGoodEvent() const;
  void  PrintTime(const std::string &argv = "hex") const;

private:
  short     fPackageID;       // trigger from satellite
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
  std::map<short,std::map<short,short> >    fFeeErrorTag;        // status for this event
  /*
   *    fFeeErrorTag[key_0][key_1]
   *    key_0:  detector id
   *        4 subDet
   *    key_1:  fee id
   */

  ClassDef(DmpEvtHeader,1)
};

#endif

