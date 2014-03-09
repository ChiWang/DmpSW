/*
 *  $Id: DmpVDataManager.h, 2014-03-08 16:44:08 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpVDataManager_H
#define DmpVDataManager_H

#include <string>
#include "DmpCore.h"

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

  virtual bool OpenInputData(){}
  virtual void BookBranch()=0;
  virtual void CreateOutDataName()=0;           // this is for concrete class
  // control static functions in job option script
  static void  SetPhase(DmpEPhase);
  static DmpEPhase GetPhase();
  void  SetInDataPath(std::string);
  void  SetOutDataPath(std::string);
  void  SetOutDataName(std::string n)   {fOutDataName = n;}
  std::string GetInDataPath() const     {return fInDataPath;}
  std::string GetOutDataPath() const    {return fOutDataPath;}
  std::string GetOutDataName() const    {return fOutDataName;}
  void  SaveOutput();
  void  FillEvent();

protected:
  bool IsDefaultName();

protected:
  static DmpEPhase  gPhase;     // Phase of DAMPE
  std::string   fInDataPath;    //
  std::string   fOutDataPath;   //
  std::string   fOutDataName;   //
  TTree         *fOutDataTree;  //

};

#endif

