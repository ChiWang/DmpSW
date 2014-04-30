/*
 *  $Id: DmpEvtMCPrimaryParticle.h, 2014-03-04 17:04:12 chi $
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
  void SetPDGCode(const int &c) {fPDGCode = c;}
  const int& GetPDGcode() const {return fPDGCode;}
// *
// *  TODO: add data members to instore information of Primary Priticle Generator,
//          and add SetXXX() functions which will be used in Simulation/DmpMCPrimaryGeneratorAction::GeneratePrimaries()
// *

private:
  int       fType;
  double    fVertexRadius;
  int       fSpectrumType;
  double    fMaxEnergy;
  int       fPDGCode;       // PDG code of primary particle

  ClassDef(DmpEvtMCPrimaryParticle,1)
};

#endif


