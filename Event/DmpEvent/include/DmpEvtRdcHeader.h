/*
 *  $Id: DmpEvtRdcHeader.h, 2014-04-27 22:31:42 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpEvtRdcHeader_H
#define DmpEvtRdcHeader_H

#include "TObject.h"

#include "DmpDetectorID.h"
#include "DmpRunMode.h"

//-------------------------------------------------------------------
class DmpRdcHeaderSubDet : public TObject{
public:
  enum FeeErrorType{
    k_good = 0,
    k_eb90 = 1,
    k_datalength = 2,
    k_CRC = 3,
  };
  DmpRdcHeaderSubDet();
  ~DmpRdcHeaderSubDet();
  void SetTrigger(const short &t) {fTrigger = t;}
  const short& Trigger() const {return fTrigger;}
  void SetRunMode(const short &m) {fRunMode = (DmpDetector::DmpERunMode)m;}
  DmpDetector::DmpERunMode RunMode() const {return fRunMode;}
  void SetErrorLog(const short &FeeID,const FeeErrorType &type) {fErrors.push_back(FeeID*10+type);}
  bool IsGoodEvent() const;
  std::vector<short> Errors() const {return fErrors;}
  void Reset();

private:
  short     fTrigger;                   // trigger
  DmpDetector::DmpERunMode  fRunMode;   // mode
  std::vector<short>        fErrors;    // all errors infor.
  /*
   * fErrors[0] is for global check
   *    good event:         0
   *    triggers not match: -1
   *    lost FEE:           -x0 (some one not find eb90. x = find_n_Fee - total_Fee)
   *
   * fErrors[i] is for a single Fee
   *    not find eb90:      1 + last_Fee_ID*10
   *    data length error:  2 + Fee_ID*10
   *    CRC error:          3 + Fee_ID*10
   *
   */

  ClassDef(DmpRdcHeaderSubDet,1)
};

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

  void  SetTime(const short&,const short&);
  void  PrintTime()const;       // only Rdc use it
  void  GenerateStatus();
  void  SetTrigger(const short &v) {fTrigger = v;}
  void  Reset();
  long  Second() const {return fSec;}
  short Millisecond() const {return fMillisec;}
  short Trigger() const;
  short Status() const {return fStatus;}
  DmpRdcHeaderSubDet* Detector(const DmpDetector::DmpEDetectorID &id) const;

private:
  long      fSec;           // second
  short     fMillisec;      // millisecond
  short     fTrigger;       // satellite trigger
  short     fStatus;        // status for this event
  /*
   * Error type:
   *    right:          all bits = 0
   *    trigger check:  > 0 trigger error
   *        Psd != Bgo: fStatus.bit[0] = 1
   *        Stk != Bgo: fStatus.bit[1] = 1
   *        Nud != Bgo: fStatus.bit[2] = 1
   *        Sat != Bgo: fStatus.bit[3] = 1
   */
  DmpRdcHeaderSubDet *fPsd; // header infor. of subDet
  DmpRdcHeaderSubDet *fStk; // header infor. of subDet
  DmpRdcHeaderSubDet *fBgo; // header infor. of subDet
  DmpRdcHeaderSubDet *fNud; // header infor. of subDet

private:    // variables below will not save into root file
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

