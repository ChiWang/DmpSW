/*
 *  $Id: DmpEvtRdcMSD.h, 2014-04-29 22:31:58 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#ifndef DmpEvtRdcMSD_H
#define DmpEvtRdcMSD_H

#include "TObject.h"

class DmpEvtRdcMSD : public TObject{
/*
 *  DmpEvtRdcMSD
 *
 *      this class is used to save output of Rdc for all subDet
 *
 *   one object mean:
 *  Psd: one strip, a set of Adc (max = 2*2)
 *  Bgo: one bar, a set of Adc (max = 2*3)
 *  Nud: one block, a set of Adc (max = 1*1??)
 *  Stk: one ladder, a set of Adc (max = 1*384)
 *
 */
public:
  DmpEvtRdcMSD();
  ~DmpEvtRdcMSD();
  short GetSDID() const {return fSDID;}
  void  SetSDID(const short &id) {fSDID = id;}
  void  SetSignal(const int &value,const short &signalID); 
  int   GetSignal(const short &signalID) const;

private:
  short   fSDID;          // unique sensitive detector(minimum detector unit) ID
// *
// *  TODO:  need to confirm notes about Psd and Nud
// *
  /*
   *    Psd:    fSDID = layerID*100 + stripID. layerID = {0~3}, stripID = {0~23}
   *    Stk:    fSDID = layerID*100 + blockID*10 +ladderID.  layerID = {0~11}, blockID = {0~3}, ladderID = {0~3}
   *    Bgo:    fSDID = layerID*100 + barID. layerID = {0~13}, barID = {0~21}
   *    Nud:    fSDID = ?
   */
  std::vector<short>    fSignalID;      // signal ID
  /*
   *    Psd:    fSignalID = sideID*10 + dynodeID. sideID = {0,1}, dynodeID = {3,7???}
   *    Stk:    fSignalID = stripID. stripID = {0~383}
   *    Bgo:    fSignalID = sideID*10 + dynodeID. sideID = {0,1}, dynodeID = {2,5,8}
   *    Nud:    fSignalID = ??
   */
  std::vector<int>      fSignalValue;   // signal value (ADC)

  ClassDef(DmpEvtRdcMSD,1)
};

#endif

