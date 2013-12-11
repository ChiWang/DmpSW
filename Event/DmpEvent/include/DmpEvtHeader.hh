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

class DmpEvtHeader : public TObject{
/*
 * DmpEvtHeader
 *
 * Information of event, refer to data member.
 *
 * Check package header(0xe225 0813??), if right, ++fPackageID. Then, read raw science data of event. If this event is valid (format right, trigger match, CRC right, longth right), ++fEventID, and then, fill this event. So, fEventID must be continuous, fPackageID may not.
 *
 *
 *
*/

enum DmpEParticleID {
  kUnknown  = -99,
  kElectron = -1,
  kMuon     = 0,
  kProton   = 9,
  kCarbon   = 12,
};

 public:
  DmpEvtHeader();
  ~DmpEvtHeader();
  void  Reset();
  Bool_t IsValidEvent();
  void  SetTime(Short_t time[],Int_t size);     // converte hex time to dec time and cal. time gap
  void  ShowTime() const;
  void    SetPID(DmpEParticelID pid){fPID = pid;}
  void    SetCharge(Short_t q)      {fCharge = q;}
  void    SetEnergy(Double_t e)     {fEnergy = e;}
  Long64_t   GetPackageID() const   {return fPackageID;}
  Long64_t   GetEventID() const     {return fEventID;}
  Long64_t   GetTimeGap() const     {return fTimeGap;}
  DmpEParticleID  GetPID() const    {return fPID;}
  Short_t  GetCharge() const  {return fCharge;}
  Double_t GetEnergy() const  {return fEnergy;}

 private:
    // recored information
  Long64_t      fPackageID;         // check package header, if right, +1
  Long64_t      fEventID;           // valid event count. continuous
  Long64_t      fSec;               // Time: sec + msec
  Short_t       fmSec;              //
  Long64_t      fTimeGap;           // unit:   msec

 private:
    // reconstructed information
  DmpEParticleID  fPID;             // particle ID
  Short_t         fCharge;          // reconstructed charge
  Double_t        fEnergy;          // reconstructed energy

  ClassDef(DmpEvtHeader,1)
};

#endif

