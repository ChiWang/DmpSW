/*
 *  $Id: DmpSimSvcBoot.h, 2014-05-15 00:21:39 DAMPE $
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
 *  must set those things in JobOpt file:
 *      1. Set("Satellite/Gdml", "somePath")
 *      2. SetSubDet(DmpDetector::DmpEDetectorID,"Gdml","somePath")
 *
 */
public:
  DmpSimSvcBoot();
  ~DmpSimSvcBoot();
  void Set(const std::string &type,const std::string &argv);
  /*
   *    type = "Physics"
   *        argv = "QGSP_BIC" or "QGSP_BERT"
   *    type = "Satellite/Gdml"
   *        argv = any
   *
   */
  void SetPsd(const std::string &type,const std::string &argv){;}
  void SetStk(const std::string &type,const std::string &argv){;}
  void SetBgo(const std::string &type,const std::string &argv){;}
  void SetNud(const std::string &type,const std::string &argv){;}
  bool Initialize();
  bool Finalize();

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

