/*
 *  $Id: DmpAlgorithmManager.h, 2014-03-22 23:03:28 chi $
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
  static DmpAlgorithmManager* GetInstance(){
    static DmpAlgorithmManager instance;
    return &instance;
  }
// *
// *  TODO: how to manager and choose the right one?
// *
  ~DmpAlgorithmManager(){;}

private:
  DmpAlgorithmManager(){}

private:
  std::map<std::string,DmpVAlgorithm*>  fAlgMap;


};

#endif

