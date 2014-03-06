/*
 *  $Id: DmpVDataManager.h, 2014-03-06 21:45:45 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpVDataManager_H
#define DmpVDataManager_H

#include <string>

class TTree;

class DmpVDataManager{
/*
 *  DmpVDataManager
 *
 *  All DataManager class inherite from this class
*/
 public:
  DmpVDataManager();
  virtual ~DmpVDataManager();

  virtual void  SetOutDataName(std::string)=0;
  virtual void  BookBranch()=0;
  void  SetInDataPath(std::string);
  void  SetOutDataPath(std::string);
  void  SaveOutput();

protected:
  std::string   fInDataPath;    //
  std::string   fOutDataPath;   //
  std::string   fOutDataName;   //
  TTree         *fOutDataTree;  //

};

#endif

