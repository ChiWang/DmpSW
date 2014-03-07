/*
 *  $Id: DmpVDataManager.h, 2014-03-07 15:32:14 chi $
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
 *  in order to control pathes in run script, binded static functions in this class into boost python (in file ../src/DmpCoreBinding.cc)
 *
 *  In concrete data manager, should define:
 *      (1) input data name and pointer (Tree of fstream) to get input data
 *      (2) event class(es) as data members, then use fOutTree to book them into branch
 *
 */
 public:
  DmpVDataManager();
  virtual ~DmpVDataManager();

  virtual void  BookBranch()=0;
  virtual void  SetOutDataName(std::string)=0;
  static void  SetInDataPath(std::string);
  static void  SetOutDataPath(std::string);
  void  SaveOutput();
  void  FillEvent();

protected:
  static std::string   fInDataPath;    //
  static std::string   fOutDataPath;   //
  std::string   fOutDataName;   //
  TTree         *fOutDataTree;  //

};

#endif

