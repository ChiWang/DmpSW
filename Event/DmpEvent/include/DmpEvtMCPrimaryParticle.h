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
  void SetEventID(const long &i){fEventID = i;}
  void SetPosition(const double &x, const double &y, const double &z) {fPosX = x; fPosY = y; fPosZ = z;}
  void SetPDGCode(const int &c) {fPDGCode = c;}
  void SetMass(const double &m) {fMass = m;}
  void SetCharge(const double &c) {fCharge = c;}
  void SetMomentum(const double &x, const double &y, const double &z) {fPx = x; fPy = y; fPz = z;}
  const long& GetEventID() const {return fEventID;}
  const double& GetPositionX() const {return fPosX;}
  const double& GetPositionY() const {return fPosY;}
  const double& GetPositionZ() const {return fPosZ;}
  const int& GetPDGcode() const {return fPDGCode;}
  const double& GetMass() const {return fMass;}
  const double& GetCharge() const {return fCharge;}
  const double& GetPx() const {return fPx;}
  const double& GetPy() const {return fPy;}
  const double& GetPz() const {return fPz;}
  double GetEnergy() const;

private:
  long      fEventID;       // event ID
  double    fPosX;          // X position of primary vertex
  double    fPosY;          // Y position
  double    fPosZ;          // Z position
  int       fPDGCode;       // PDG code of primary particle
  double    fMass;          // mass of primary particle
  double    fCharge;        // charge of primary particle
  double    fPx;            // momentum X axis of primary particle
  double    fPy;            // momentum Y axis of primary particle
  double    fPz;            // momentum Z axis of primary particle

  ClassDef(DmpEvtMCPrimaryParticle,1)
};

#endif


