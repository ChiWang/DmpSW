/*
 *  $Id: DmpVDataManager.h, 2014-03-20 00:00:32 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpVDataManager_H
#define DmpVDataManager_H

#include <string>

class DmpVDataManager{
/* 
 *  DmpVDataManager
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
  DmpVDataManager();
  virtual ~DmpVDataManager();

  virtual void BookBranch()=0;
  virtual void FillEvent()=0;
  virtual void SetOutDataName()=0;
  virtual void SaveOutput()=0;
  void  SetInDataName(const std::string &n) {fInDataName = n;}
  std::string GetInDataName() const     {return fInDataName;}  // binding me
  void  SetOutDataPath(const std::string&);        // binding me
  std::string GetOutDataPath() const    {return fOutDataPath;}  // binding me
  std::string GetOutDataName() const    {return fOutDataName;}  // binding me
  void  SetNote(const std::string &t)   {fNote = t;}   // binding me

protected:
  std::string TimeStamp();

protected:
  std::string   fInDataName;    // path + name
  std::string   fOutDataPath;   //
  std::string   fOutDataName;   //
  std::string   fNote;          // add note in the out data name

};

#endif

