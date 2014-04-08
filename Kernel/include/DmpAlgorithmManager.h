/*
 *  $Id: DmpAlgorithmManager.h, 2014-04-08 12:42:07 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/03/2014
*/

#ifndef DmpAlgorithmManager_H
#define DmpAlgorithmManager_H

#include <list>
#include "DmpVAlg.h"

//class DmpVAlg;

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
  bool Initialize();
  bool Process();       // Process one event
  bool Finialize();
  void Append(DmpVAlg *aEle) {fElements.push_back(aEle);}
  void Replace(DmpVAlg*);
  void ListAllElements();

private:
  DmpAlgorithmManager();

private:
  std::list<DmpVAlg*>    fElements;
  std::list<DmpVAlg*>::iterator    fIterator;
};

//-------------------------------------------------------------------
extern DmpAlgorithmManager  *gDmpAlgMgr;

#endif

