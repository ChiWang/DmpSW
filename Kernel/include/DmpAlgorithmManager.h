/*
 *  $Id: DmpAlgorithmManager.h, 2014-04-10 20:18:04 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/03/2014
*/

#ifndef DmpAlgorithmManager_H
#define DmpAlgorithmManager_H

#include "DmpVAlg.h"
#include "DmpElementManager.h"

class DmpAlgorithmManager : public DmpElementManager<DmpVAlg>{
/*
 * DmpAlgorithmManager
 *
 * manage all algorithmes of DAMPE software
 *
 */
public:
  static DmpAlgorithmManager* GetInstance(){
    static DmpAlgorithmManager instance;
    return &instance;
  }
  ~DmpAlgorithmManager();
  bool Process();       // Process one event

private:
  DmpAlgorithmManager();

};

//-------------------------------------------------------------------
extern DmpAlgorithmManager  *gDmpAlgMgr;

#endif

