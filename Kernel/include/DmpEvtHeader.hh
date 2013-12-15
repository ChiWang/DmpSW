/*=====================================================================
 *   File:   DmpEvtHeader.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  15/12/2013   21:52:29
=====================================================================*/

#ifndef DmpEvtHeader_H
#define DmpEvtHeader_H

#include "TObject.h"

class DmpEvtHeader : public TObject{
/*
 * DmpEvtHeader
 *
 * Information of event, refer to data member.
 *
 * Check package header(0xe225 0813), if right, ++fPackageID, then
 * read raw science data of event. If this event is valid (format right, trigger match, CRC right, longth right), ++fEvtID, and then,
 * fill this event. So, fEvtID must be continuous, fPackageID may not.
 *
 * default set fTimeGap=100mSec for the first event
 *
*/

 public:
  enum DmpEParticleID {
    kUnknown  = -100,
    kElectron = -1,
    kMuon     = 0,
    kProton   = 9,
    kCarbon   = 12,
  };

  DmpEvtHeader();
  ~DmpEvtHeader();
  void  Reset();
  void  SetTime(Short_t time[],Int_t size);     // converte hex time to dec time and cal. time gap
  void  ShowTime(Short_t mode=1) const;         // mode = {0|1} 0: raw hex time; 1: normal time(date,time)
  void  CountPackage()              {++fPackageID;}
  void  CountEvent()                {++fEvtID;}
  void  SetPID(DmpEParticleID pid)  {fPID = pid;}
  void  SetCharge(Short_t q)        {fCharge = q;}
  void  SetEnergy(Double_t e)       {fEnergy = e;}
  Long64_t  GetPackageID() const    {return fPackageID;}
  Long64_t  GetEventID() const      {return fEvtID;}
  Long64_t  GetTimeGap() const      {return fTimeGap;}
  DmpEParticleID    GetPID() const  {return fPID;}
  Short_t   GetCharge() const       {return fCharge;}
  Double_t  GetEnergy() const       {return fEnergy;}

 private:
    // recored information
  Long64_t  fPackageID;         // check package header, if right, +1
  Long64_t  fEvtID;             // valid event count. continuous
  Long64_t  fSec;               // Time: sec + msec
  Short_t   fmSec;              //
  Long64_t  fTimeGap;           // unit:   msec

 private:
    // reconstructed information
  DmpEParticleID    fPID;       // particle ID
  Short_t   fCharge;            // reconstructed charge
  Double_t  fEnergy;            // reconstructed energy

 private:
  Short_t   *fTime;             //! pointer to store data of hex time

  ClassDef(DmpEvtHeader,1)
};

#endif

