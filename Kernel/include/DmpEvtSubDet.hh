/*=====================================================================
 *   File:   DmpEvtSubDet.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:06:21
=====================================================================*/

#ifndef DmpEvtSubDet_H
#define DmpEvtSubDet_H

#include "TObject.h"

class DmpEvtHeader;

class DmpEvtSubDet : public TObject{
/*
 *  DmpEvtSubDet
 *
 *  abstruct class of event class, all concrete classes of sub-detector will use it.
 *
 *  not save Event header in any sub-det.
 *
 *  But, if one sub-detector wants to use information from event header, must SetEventHeader pointer into DmpAbsEvtSubDet by DmpAbsEvtSubDet::SetEventHeader(pinter), after creating EventHeader
 *
*/

 public:
  enum DmpERunMode {
    kMixed     = 0,       // only for Event Header, if sub-detectors setted different mode, run mode of Event Header is kMixed
    k0Compress = 1,       // zero compress
    kCompress  = 5,       // compress mode
    kCalPed    = 6,       // Calibrate pedestal
    kCalFEE    = 9,       // ADC Calibration
  };

  DmpEvtSubDet();
  virtual ~DmpEvtSubDet();
  virtual void Reset() = 0;
  virtual void PrintEvent() const=0;
  static void SetEventHeader(DmpEvtHeader *p) {fHeader = p;}
  static DmpEvtHeader*  GetEventHeader();
  void  SetMode(DmpERunMode m)  {fMode = m;}
  DmpERunMode GetMode() const   {return fMode;}

 protected:
  static DmpEvtHeader   *fHeader;       //! pointer to git event header
  DmpERunMode           fMode;          // run mode

  ClassDef(DmpEvtSubDet,1)
};

#endif


