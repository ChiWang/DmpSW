/*
 *  $Id: DmpVOutDataManager.h, 2014-03-11 19:50:34 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpVOutDataManager_H
#define DmpVOutDataManager_H

#include <string>

class TTree;

class DmpVOutDataManager{
/* 
 *  DmpVOutDataManager
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
  DmpVOutDataManager();
  virtual ~DmpVOutDataManager();

  virtual void BookBranch()=0;
  virtual void  SetOutDataName(std::string n)   {fOutDataName = n;}
  // control static functions in job option script
  void  SetOutDataPath(std::string);
  std::string GetOutDataPath() const    {return fOutDataPath;}
  std::string GetOutDataName() const    {return fOutDataName;}
  void  SaveOutput();
  void  FillEvent();

protected:
  std::string TimeStamp();

protected:
  std::string   fOutDataPath;   //
  std::string   fOutDataName;   //
  TTree         *fOutDataTree;  //

};

#endif

