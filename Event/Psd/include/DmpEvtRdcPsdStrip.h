/*
 *  $Id: DmpEvtRdcPsdStrip.h, 2014-07-19 10:27:13 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#ifndef DmpEvtRdcPsdStrip_H
#define DmpEvtRdcPsdStrip_H

#include "TObject.h"

class DmpEvtRdcPsdStrip : public TObject{
/*
 *  DmpEvtRdcPsdStrip
 *
 *      this class is used to save output of Rdc for Psd
 *
 *   one object mean one Psd strip, a set of Adc (max = 2*2)
 *
 */
public:
  DmpEvtRdcPsdStrip();
  ~DmpEvtRdcPsdStrip();
  short GetLayerID() const {return fGlobalStripID/100;}
  short GetStripID() const {return fGlobalStripID%100;}   // in one layer
  short GetGlobalStripID() const {return fGlobalStripID;} // in whole layer
  std::vector<short> GetDynodeID() const {return fDynodeID;}
  void  SetGlobalStripID(const short &id) {fGlobalStripID = id;}  // in whole layer
  void  SetSignal(const short &GlobalFeeChannelID,const short &dynodeID,const int &value);
  int   GetSignal(const short &dynodeID) const;
  short GetFeeID(const short &dynodeID) const;
  short GetFeeChannelID(const short &dynodeID) const;
  short GetGlocalFeeChannelID(const short &dynodeID) const;

private:
  short   fGlobalStripID;         // unique sensitive detector(minimum detector unit) ID
   //*    Psd:    fGlobalStripID = layerID*100 + barID. layerID = {0~1}, barID = {0~40}
// *  TODO: check Fee ID and Note
  std::vector<short>    fGlobalFeeChannelID;  // Fee Channel ID
   //*    Psd:    fGlobalFeeChannelID = FeeID*1000 + FeeChannelID. FeeID = 0x1{0,1,a,b,8,9...}, FeeChannelID = {0~78,156}
  std::vector<short>    fDynodeID;      // Dynode ID
// *  TODO: check Note
   //*    Psd:    fDynodeID = sideID*10 + dynodeID. sideID = {0,1}, dynodeID = {2,5}
  std::vector<int>      fADCCount;      // signal value (ADC)

  ClassDef(DmpEvtRdcPsdStrip,1)
};

#endif

