/*
 *  $Id: DmpAlgorithmManager.h, 2014-03-26 10:45:26 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/03/2014
*/

#ifndef DmpAlgorithmManager_H
#define DmpAlgorithmManager_H

#include "DmpVElementManager.h"

class DmpVAlgorithm;

class DmpAlgorithmManager : public DmpVElementManager<DmpVAlgorithm>{
/*
 * DmpAlgorithmManager
 *
 * manage all algorithmes of DAMPE software
 *
 */
public:
// *
// *  TODO: how to manager and choose the right one?
// *
  static DmpAlgorithmManager* GetInstance(){
    static DmpAlgorithmManager instance;
    return &instance;
  }
  ~DmpAlgorithmManager();
// *
// *  TODO:  delete Append... ListAll... at here
// *
  void AppendAlgorithm(DmpVAlgorithm*);
  bool Process();       // Process one event
  void ListAllAlgorithm();

private:
  DmpAlgorithmManager();

};

//-------------------------------------------------------------------
extern DmpAlgorithmManager  *gAlgMgr;

#endif

