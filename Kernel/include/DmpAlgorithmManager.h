/*
 *  $Id: DmpAlgorithmManager.h, 2014-03-25 13:39:33 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/03/2014
*/

#ifndef DmpAlgorithmManager_H
#define DmpAlgorithmManager_H

#include <string>
#include <map>

class DmpVAlgorithm;

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
  void AppendAlgorithm(DmpVAlgorithm*);
  bool Initialize();
  bool Process();       // Process one event
  bool Finialize();
  void ListAllAlgorithm();

private:
  DmpAlgorithmManager();

private:
  std::map<std::string,DmpVAlgorithm*>  fAlgMap;

};

//-------------------------------------------------------------------
extern DmpAlgorithmManager  *gAlgMgr;

#endif

