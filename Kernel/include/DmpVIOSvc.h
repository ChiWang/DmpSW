/*
 *  $Id: DmpVIOSvc.h, 2014-04-06 19:48:57 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpVIOSvc_H
#define DmpVIOSvc_H

#include "DmpVService.h"

class TTree;

class DmpVIOSvc : public DmpVService{
/* 
 *  DmpVIOSvc
 *
 *  All data manager classes inherite from this class
 *
 *  Example: DmpRdcDataManger.h or DmpSimDataManager.h
 *
 */
public:
  DmpVIOSvc(const std::string &n);
  virtual ~DmpVIOSvc();

  virtual void BookBranch()=0;
  virtual void FillEvent();
  virtual bool InputData(const std::string &n) {fInDataName = n; return true;}
  bool Finialize();     // save output, for one indata
  void SetOutDataPath(const std::string&);        // binding me
  void AppendDataNote(const std::string &t)   {fNote = t;}   // binding me
  std::string GetOutDataPath() const    {return fOutDataPath;}  // binding me
  std::string GetOutDataName() const    {return fOutDataName;}  // binding me

protected:
  void SetPackageID(const std::string &n) {fPgkID = n;}

private:
  void SetOutDataName();
  std::string TimeStamp();

protected:
  TTree         *fOutDataTree;  // create and delete in concrete data manager class

private:
  std::string   fInDataName;    // path + name. For one data
  std::string   fOutDataPath;   // for all output datas
  std::string   fOutDataName;   //
  std::string   fPgkID;         // package id, add this in out data name
  std::string   fNote;          // add note in the out data name
};

#endif


