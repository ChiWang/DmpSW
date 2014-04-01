/*
 *  $Id: DmpAlgorithmManager.h, 2014-03-26 10:45:26 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/03/2014
*/

#ifndef DmpAlgorithmManager_H
#define DmpAlgorithmManager_H

#include "DmpVAlgorithm.h"      // not use 
#include "DmpElementManager.h"

class DmpAlgorithmManager : public DmpElementManager<DmpVAlgorithm>{
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
  bool Process();       // Process one event

private:
  DmpAlgorithmManager();

};

//-------------------------------------------------------------------
extern DmpAlgorithmManager  *gAlgMgr;

#endif

