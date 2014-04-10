/*
 *  $Id: DmpAlgorithmManager.h, 2014-04-10 13:58:58 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/03/2014
*/

#ifndef DmpAlgorithmManager_H
#define DmpAlgorithmManager_H

#include <list>
#include "DmpVAlg.h"

class DmpAlgorithmManager{
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
  void Append(DmpVAlg*);
  void Replace(DmpVAlg*);
  void ListAllElements();
  bool Initialize();
  bool Process();       // Process one event
  bool Finalize();

private:
  DmpAlgorithmManager();

private:
  std::list<DmpVAlg*>    fElements;
  std::list<DmpVAlg*>::iterator    fIterator;
};

//-------------------------------------------------------------------
extern DmpAlgorithmManager  *gDmpAlgMgr;

#endif

