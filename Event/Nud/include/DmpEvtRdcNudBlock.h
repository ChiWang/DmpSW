/*
 *  $Id: DmpEvtRdcNudBlock.h, 2014-07-18 17:00:19 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/04/2014
*/

#ifndef DmpEvtRdcNudBlock_H
#define DmpEvtRdcNudBlock_H

#include "TObject.h"

class DmpEvtRdcNudBlock : public TObject{
/*
 *  DmpEvtRdcNudBlock
 *
 *      this class is used to save output of Rdc for Nud
 *
 */
public:
  DmpEvtRdcNudBlock();
  ~DmpEvtRdcNudBlock();
  short GetGlobalBlockID() const {return fGlobalBlockID;} // in whole layer
  void  SetGlobalBlockID(const short &id) {fGlobalBlockID = id;}  // in whole layer
  void  SetSignal(const short &GlobalFeeChannelID,const int &value);
  int   GetSignal() const {return fADCCount;}
  short GetGlocalFeeChannelID() const {return fGlobalFeeChannelID;}

private:
  short   fGlobalBlockID;       // unique sensitive detector(minimum detector unit) ID
   //*    Nud:    fGlobalBlockID = {0~3}
// *
// *  TODO: need fGlobalFeeChannelID?
// *
  short   fGlobalFeeChannelID;  // Fee channel ID
  int     fADCCount;            // signal value (ADC)

  ClassDef(DmpEvtRdcNudBlock,1)
};

#endif

