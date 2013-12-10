/*=============================================================================
#       FileName :          DmpEvtHeader.hh
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-03   21:58:16
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-11-12   23:18:24
=============================================================================*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include "TObject.h"

class DmpEvtAbsSubDet;
class DmpParticle;

class DmpEvtHeader : public TObject{
/*
  DmpEvtHeader

  Information of event, refer to data member.

  All classes of Sub-detector could use members of this class, since used friend class.

  Check package header(0xe225 0813??), if right, ++fPackageID. Then, read raw science data of event. If this event is valid (format right, trigger match, CRC right, longth right), ++fEventID, and then, fill this event. So, fEventID must be continuous, fPackageID may not.

  There're 2 objects of DmpParticle. fBeam is for test beam, fPartcile record our reconstructed results.

*/

 friend class DmpEvtAbsSubDet;

 public:
  DmpEvtHeader();
  virtual ~DmpEvtHeader();
  void  Reset();
  Bool_t IsValidEvent();
  void  SetTime(Short_t time[],Int_t size);     // converte hex time to dec time and cal. time gap
  void  ShowTime() const;
  Long64_t   GetPackageID() const   {return fPackageID;}
  Long64_t   GetEventID() const     {return fEventID;}
  Long64_t   GetTimeGap() const     {return fTimeGap;}
  DmpParticle*  GetBeam() const     {return fBeam;}
  DmpParticle*  GetParticle() const {return fParticle;}

 private:
  Long64_t      fPackageID;         // check package header, if right, +1
  Long64_t      fEventID;           // valid event count. continuous
  Long64_t      fSec;               // Time: sec + msec
  Short_t       fmSec;              //
  Long64_t      fTimeGap;           // unit:   msec
  DmpParticle   *fBeam;             // beam information
  DmpParticle   *fParticle;         // information of reconstruction

  ClassDef(DmpEvtHeader,1)
};

#endif


