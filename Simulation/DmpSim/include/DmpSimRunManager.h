/*
 *  $Id: DmpSimRunManager.h, 2014-06-10 15:59:12 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 12/04/2014
*/

#ifndef DmpSimRunManager_H
#define DmpSimRunManager_H

#include "G4RunManager.hh"

class DmpSimRunManager : public G4RunManager{
/*
 *  DmpSimRunManager
 *
 *      create it in JobOpt file, and boot simulation for DmpSW
 *
 */
public:
  DmpSimRunManager();
  ~DmpSimRunManager();
  bool SimOneEvent(const int &id);

};

#endif

