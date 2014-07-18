/*
 *  $Id: DmpEvtRdcBgoBar.h, 2014-07-17 15:32:57 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#ifndef DmpEvtRdcBgoBar_H
#define DmpEvtRdcBgoBar_H

#include "TObject.h"

class DmpEvtRdcBgoBar : public TObject{
/*
 *  DmpEvtRdcBgoBar
 *
 *      this class is used to save output of Rdc for Bgo
 *
 *   one object mean one Bgo bar, a set of Adc (max = 2*3)
 *
 */
public:
  DmpEvtRdcBgoBar();
  ~DmpEvtRdcBgoBar();
  short GetLayerID() const {return fGlobalBarID/100;}
  short GetBarID() const {return fGlobalBarID%100;}   // in one layer
  short GetGlobalBarID() const {return fGlobalBarID;} // in whole layer
  std::vector<short> GetDynodeID() const {return fDynodeID;}
  void  SetGlobalBarID(const short &id) {fGlobalBarID = id;}  // in whole layer
  void  SetSignal(const short &GlobalFeeChannelID,const short &dynodeID,const int &value);
  int   GetSignal(const short &dynodeID) const;
  short GetFeeID(const short &dynodeID) const;
  short GetFeeChannelID(const short &dynodeID) const;
  short GetGlocalFeeChannelID(const short &dynodeID) const;

private:
  short   fGlobalBarID;         // unique sensitive detector(minimum detector unit) ID
   //*    Bgo:    fGlobalBarID = layerID*100 + barID. layerID = {0~13}, barID = {0~21}
  std::vector<short>    fGlobalFeeChannelID;  // Fee Channel ID
   //*    Bgo:    fGlobalFeeChannelID = FeeID*1000 + FeeChannelID. FeeID = 0x1{0,1,a,b,8,9...}, FeeChannelID = {0~78,156}
  std::vector<short>    fDynodeID;      // Dynode ID
   //*    Bgo:    fDynodeID = sideID*10 + dynodeID. sideID = {0,1}, dynodeID = {2,5,8}
  std::vector<int>      fADCCount;      // signal value (ADC)

  ClassDef(DmpEvtRdcBgoBar,1)
};

#endif

