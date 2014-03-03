/*
 *  $Id: DmpEvtSimPrimaryParticle.h, 2014-03-02 23:08:14 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#ifndef DmpEvtSimParimaryParticle_H
#define DmpEvtSimParimaryParticle_H

#include "TObject.h"

class DmpEvtSimParimaryParticle : public TObject{
/*
 * DmpEvtSimParimaryParticle
 *
 * This class used (in Simulation DataManager) to store informations of user defined PrimaryGeneratorAction
 *
 */
public:
  DmpEvtSimParimaryParticle();
  ~DmpEvtSimParimaryParticle();

private:
  int       fType;
  double    fVertexRadius;
  int       fSpectrumType;
  double    fMaxEnergy;

  ClassDef(DmpEvtSimParimaryParticle,1)
};

#endif

