/*
 *  $Id: DmpSimSvcBoot.h, 2014-04-14 11:35:37 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 12/04/2014
*/

#ifndef DmpSimSvcBoot_H
#define DmpSimSvcBoot_H

#include "DmpVSvc.h"

class G4RunManager;
class DmpSimDetector;
class G4PhysListFactory;
class G4VUserPhysicsList;

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
  void SetPsd(const std::string &type,const std::string &argv);
  void SetStk(const std::string &type,const std::string &argv);
  void SetBgo(const std::string &type,const std::string &argv);
  void SetNud(const std::string &type,const std::string &argv);
  bool Initialize();
  bool Finalize();

private:
  G4RunManager          *fRunMgr;
  DmpSimDetector        *fDetector;
  G4PhysListFactory     *fPhyFactory;
  G4VUserPhysicsList    *fPhyList;
  std::string           fPhyListName;       // default is QGSP_BIC

};

#endif

