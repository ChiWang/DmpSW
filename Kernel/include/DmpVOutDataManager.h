/*
 *  $Id: DmpVOutDataManager.h, 2014-03-11 23:32:46 chi $
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
 *
 *  In concrete data manager, should define:
 *      (1) input data name and pointer (Tree of fstream) to get input data
 *      (2) event class(es) as data member, then use fOutTree to book them into branch
 *
 *  Example: DmpRdcDataManger.h or DmpSimDataManager.h
 *
 */
public:
  DmpVOutDataManager();
  virtual ~DmpVOutDataManager();

  virtual void BookBranch()=0;
  virtual void SetOutDataName(const std::string &n)   {fOutDataName = n;}   // binding me
  void  SetOutDataPath(std::string);        // binding me
  std::string GetOutDataPath() const    {return fOutDataPath;}  // binding me
  std::string GetOutDataName() const    {return fOutDataName;}  // binding me
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

