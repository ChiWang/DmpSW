/*
 *  $Id: DmpSimAlgRunManager.h, 2014-05-26 20:26:24 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 12/04/2014
*/

#ifndef DmpSimAlgRunManager_H
#define DmpSimAlgRunManager_H

#include "G4RunManager.hh"
#include "DmpVAlg.h"

class G4PhysListFactory;

class DmpSimAlgRunManager : public DmpVAlg, public G4RunManager{
/*
 *  DmpSimAlgRunManager
 *
 *      create it in JobOpt file, and boot simulation for DmpSW
 *
 */
public:
  DmpSimAlgRunManager();
  ~DmpSimAlgRunManager();
  void Set(const std::string &type,const std::string &argv);
  bool Initialise();
  bool ProcessThisEvent();
  bool Finalize();

private:
  std::string           fMacFile;
  G4PhysListFactory     *fPhyFactory;
  std::string           fPhyListName;   // default is QGSP_BIC
  long                  fEventID;

private:
  bool      fBeamOnCondition;

};

#endif

