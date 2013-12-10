/*=============================================================================
#       FileName :          DmpParticle.hh
#       Version  :          0.0.1
#       Author   :          Chi WANG    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-12-10   12:19:30
#------------------------------------------------------------------------------
#       Description  :
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-12-10   12:19:30
=============================================================================*/

#ifndef DmpParticle_H
#define DmpParticle_H
#include "TObject.h"

class DmpParticle : public TObject{

enum DmpEParticleID {
  kUnknown  = -99,
  kElectron = -1,
  kMuon     = 0,
  kProton   = 9,
  kCarbon   = 12,
};
  public:
    DmpParticle();
    ~DmpParticle();
    void    Reset();
    void    SetPID(DmpEParticelID pid)  {fPID = pid;}
    void    SetCharge(Short_t q)        {fCharge = q;}
    void    SetEnergy(Double_t e)       {fEnergy = e;}
    DmpEParticelID  GetPID() const      {return fPID;}
    Short_t  GetCharge() const  {return fCharge;}
    Double_t GetEnergy() const  {return fEnergy;}

  private:
    DmpEParticleID  fPID;
    Short_t         fCharge;
    Double_t        fEnergy;

  ClassDef(DmpParticle,1)

};

#endif

