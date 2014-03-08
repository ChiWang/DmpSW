/*
 *  $Id: DmpVDataManager.h, 2014-03-08 10:25:14 chi $
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

  virtual void BookBranch()=0;
  virtual void UseDefaultDataName()=0;        // this is for concrete class
  static void  SetInDataPath(std::string);
  static void  SetOutDataPath(std::string);
  static void  SetOutDataName(std::string); // control name in job option script
  void  SaveOutput();
  void  FillEvent();

protected:
  bool CreateDefaultName();

protected:
  static std::string   fInDataPath;    //
  static std::string   fOutDataPath;   //
  static std::string   fOutDataName;   //
  TTree         *fOutDataTree;  //

};

#endif

