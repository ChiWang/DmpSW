/*
 *  $Id: DmpSimSvcBoot.h, 2014-05-20 10:56:02 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 12/04/2014
*/

#ifndef DmpSimSvcBoot_H
#define DmpSimSvcBoot_H

#include "DmpVSvc.h"

class G4RunManager;
class G4PhysListFactory;
class DmpSimDetector;
class DmpSimPrimaryGeneratorAction;
class DmpSimRunAction;
class DmpSimEventAction;
class DmpSimTrackingAction;

class DmpSimSvcBoot : public DmpVSvc{
/*
 *  DmpSimSvcBoot
 *
 *      create it in JobOpt file, and boot simulation for DmpSW
 *
 */
public:
  DmpSimSvcBoot();
  ~DmpSimSvcBoot();
  bool Initialize();
  bool Finalize();
  void Set(const std::string &type,const std::string &argv);

private:
  G4RunManager          *fRunMgr;
  G4PhysListFactory     *fPhyFactory;
  std::string           fPhyListName;       // default is QGSP_BIC
  DmpSimDetector        *fDetector;
  DmpSimPrimaryGeneratorAction *fPriGen;
  DmpSimRunAction       *fRunAct;
  DmpSimEventAction     *fEvtAct;
  DmpSimTrackingAction  *fTrcAct;

};

#endif

