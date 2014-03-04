/*
 *  $Id: DmpEvtSimPrimaryParticle.h, 2014-03-04 17:04:12 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpEvtSimPrimaryParticle_H
#define DmpEvtSimPrimaryParticle_H

#include "TObject.h"

class DmpEvtSimPrimaryParticle : public TObject{
/*
 * DmpEvtSimPrimaryParticle
 *
 * This class used (in Simulation DataManager) to store informations of user defined PrimaryGeneratorAction
 *
 */
public:
  DmpEvtSimPrimaryParticle();
  ~DmpEvtSimPrimaryParticle();
// *
// *  TODO: add data members to instore information of Primary Priticle Generator,
//          and add SetXXX() functions which will be used in Simulation/DmpSimPrimaryGeneratorAction::GeneratePrimaries()
// *
  //void SetXXX();

private:
  int       fType;
  double    fVertexRadius;
  int       fSpectrumType;
  double    fMaxEnergy;

  ClassDef(DmpEvtSimPrimaryParticle,1)
};

#endif

