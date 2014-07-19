/*
 *  $Id: DmpEvtRdcStkLadder.h, 2014-07-19 11:10:07 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#ifndef DmpEvtRdcStkLadder_H
#define DmpEvtRdcStkLadder_H

#include "TObject.h"

class DmpEvtRdcStkLadder : public TObject{
/*
 *  DmpEvtRdcStkLadder
 *
 *      this class is used to save output of Rdc for Stk
 *
 *   one object mean one Stk strip, a set of Adc (max = 2*2)
 *
 */
public:
  DmpEvtRdcStkLadder();
  ~DmpEvtRdcStkLadder();
  short GetLayerID() const {return fGlobalLadderID/100;}
  short GetBlockID() const {return (fGlobalLadderID%100)/10;}
  short GetLadderID() const {return fGlobalLadderID%10;}   // in one layer
  short GetGlobalLadderID() const {return fGlobalLadderID;} // in whole layer
  std::vector<short> GetDynodeID() const {return fStripID;}
  void  SetGlobalLadderID(const short &id) {fGlobalLadderID = id;}  // in whole layer
  void  SetSignal(const int &GlobalFeeChannelID,const short &stripID,const int &value);
  int   GetSignal(const short &stripID) const;
  int   GetFeeID(const short &stripID) const;
  int   GetFeeChannelID(const short &stripID) const;
  int   GetGlocalFeeChannelID(const short &stripID) const;

private:
  short   fGlobalLadderID;         // unique sensitive detector(minimum detector unit) ID
   //*    Stk:    fGlobalLadderID = layerID*100 + blockID*10 + ladderID. layerID = {0~11}, blockID = {0~3}, ladderID = {0~3}
// *  TODO: check Fee ID and Note
  std::vector<int>      fGlobalFeeChannelID;  // Fee Channel ID
   //*    Stk:    fGlobalFeeChannelID = FeeID*10000 + FeeChannelID. FeeID = 0x1{*},(7 Fee), FeeChannelID = {0~9215}
  std::vector<short>    fStripID;       // Strip ID
   //*    Stk:    fStripID = {0~384}
  std::vector<int>      fADCCount;      // signal value (ADC)

  ClassDef(DmpEvtRdcStkLadder,1)
};

#endif

