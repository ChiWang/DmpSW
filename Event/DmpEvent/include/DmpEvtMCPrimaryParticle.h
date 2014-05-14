/*
 *  $Id: DmpEvtMCPrimaryParticle.h, 2014-05-13 15:34:37 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpEvtMCPrimaryParticle_H
#define DmpEvtMCPrimaryParticle_H

#include "TObject.h"

class DmpEvtMCPrimaryParticle : public TObject{
/*
 * DmpEvtMCPrimaryParticle
 *
 * This class used (in Simulation DataManager) to store informations of user defined PrimaryGeneratorAction
 *
 */
public:
  DmpEvtMCPrimaryParticle();
  ~DmpEvtMCPrimaryParticle();
  void SetEventID(const long &i) {fEventID = i;}
  void SetTime(const double &t) {fTime = t;}
  void SetPosition(const double &x, const double &y, const double &z) {fPosX = x; fPosY = y; fPosZ = z;}
  void SetDirection(const double &x, const double &y, const double &z) {fDirectionX = x; fDirectionY = y; fDirectionZ = z;}
  void SetKineticEnergy(const double &e) {fKineticE = e;}
  void SetPDGCode(const int &c) {fPDGCode = c;}
  void SetMass(const double &m) {fMass = m;}
  void SetCharge(const double &c) {fCharge = c;}
  void SetComponent(const int &lep, const int &bar) {fLeptonNo = lep; fBaryonNo = bar;}

  const long& EventID() const {return fEventID;}
  const double& Time() const {return fTime;}
  const double& PositionX() const {return fPosX;}
  const double& PositionY() const {return fPosY;}
  const double& PositionZ() const {return fPosZ;}
  const double& DirectionX() const {return fDirectionX;}
  const double& DirectionY() const {return fDirectionY;}
  const double& DirectionZ() const {return fDirectionZ;}
  const double& KineticEnergy() const {return fKineticE;}
  const int& PDGcode() const {return fPDGCode;}
  const double& Mass() const {return fMass;}
  const double& Charge() const {return fCharge;}
  const int& LeptonNumber() const {return fLeptonNo;}
  const int& BaryonNumber() const {return fBaryonNo;}

private:
  long      fEventID;       // event ID
  double    fTime;          //! nanosecond, always = 0
  double    fPosX;          // X position. mm
  double    fPosY;          // Y position. mm
  double    fPosZ;          // Z position. mm
  double    fDirectionX;    // momentum direction X
  double    fDirectionY;    // momentum direction Y
  double    fDirectionZ;    // momentum direction Z
  double    fKineticE;      // kinetic energy. MeV
  int       fPDGCode;       // PDG code
  double    fMass;          // mass. MeV
  double    fCharge;        // charge
  int       fLeptonNo;      // lepton number
  int       fBaryonNo;      // baryon number

  ClassDef(DmpEvtMCPrimaryParticle,1)
};

#endif


