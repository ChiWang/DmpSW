/*
 *  $Id: DmpVDataManager.h, 2014-03-22 13:54:38 chi $
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

  virtual void Initialize()=0;   // prepare for the next data file
  virtual void BookBranch()=0;
  void  FillEvent();
  void  SaveOutput();
  void  SetOutDataPath(const std::string&);        // binding me
  void  AppendDataNote(const std::string &t)   {fNote = t;}   // binding me
  std::string GetOutDataPath() const    {return fOutDataPath;}  // binding me
  std::string GetOutDataName() const    {return fOutDataName;}  // binding me
  void  SetInDataName(const std::string &n) {fInDataName = n;}
  std::string GetInDataName() const     {return fInDataName;}

private:
  void SetOutDataName();
  std::string TimeStamp();

protected:
  // for all input datas
  std::string   fPgkID;         // package id, add this in out data name
  // for one data
  TTree         *fOutDataTree;  // create and delete in concrete data manager class

//protected:
private:
  // for all input datas
  std::string   fOutDataPath;   //
  // for one data
  std::string   fInDataName;    // path + name
  std::string   fOutDataName;   //
  std::string   fNote;          // add note in the out data name

};

#endif


