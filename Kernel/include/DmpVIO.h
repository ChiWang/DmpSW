/*
 *  $Id: DmpVIO.h, 2014-04-08 10:31:52 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpVIO_H
#define DmpVIO_H

#include <string>

class TTree;

class DmpVIO{
/* 
 *  DmpVIO
 *
 *  All data manager classes inherite from this class
 *
 *  Example: DmpRdcDataManger.h or DmpSimDataManager.h
 *
 */
public:
  DmpVIO();
  virtual ~DmpVIO();

  virtual void BookBranch()=0;
  virtual void FillEvent();
  virtual void SaveOutput();  // save output, for one indata
  virtual bool InputData(const std::string &n) {fInData = n; return true;}

public:
  void SetOutDataPath(const std::string&);        // binding me
  void AppendDataNote(const std::string &t)   {fNote = t;}   // binding me
  std::string GetOutDataPath() const    {return fOutDataPath;}  // binding me
  std::string GetOutDataName() const    {return fOutDataName;}  // binding me

protected:
  void SetPackageID(const std::string &n) {fPgkID += n;}
  virtual void ResetEvent()=0;

private:
  void SetOutDataName();
  std::string TimeStamp();

protected:
  TTree         *fOutDataTree;  // create and delete in concrete data manager class

private:
  std::string   fInData;        // path + name. For one data
  std::string   fOutDataPath;   // for all output datas
  std::string   fOutDataName;   //
  std::string   fPgkID;         // package id, add this in out data name
  std::string   fNote;          // add note in the out data name
};

#endif

